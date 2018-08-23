#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#define KEY "helloworldisnice"
#define IV  "vectordefinegood"
int n = 0;
/***get the file path of encrypted text file***/
FILE * get_file_pointer(int should_encrypt, char * env_var){
    // First encrypt the file
    char path_base[256] = "";
    char path_cipher[256] = "";
    int path_base_len = strlen(getenv(env_var));
    strncpy(path_base, getenv(env_var), path_base_len);
    strncpy(path_cipher, path_base, path_base_len);
    strcat(path_cipher, "/dbname_encryp.txt");
    if(should_encrypt){   
        return fopen(path_cipher, "wb");
    }
    else{
        return fopen(path_cipher, "rb");
    } 
}
/***only write to file when in encrypt mode***/
void write_msg(int should_encrypt, unsigned char *cipher_buf, int size, int out_len, FILE *ofp)
{
    if(should_encrypt){
         fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);
    }
    else{
        fprintf(ofp, "i=%d,%s, out_len=%s", n++, cipher_buf, out_len);
    }
    //fwrite(cipher_buf, sizeof(unsigned char), out_len, ofp);
}

void assign_fp(int should_encrypt, FILE **ifp, FILE **ofp){
   if(should_encrypt){
       *ifp = stdin;
       *ofp = get_file_pointer(should_encrypt, "WS_DATA_PATH");
   }
   else{
       *ofp = stdout;
       *ifp = get_file_pointer(should_encrypt, "WS_DATA_PATH");
    }   
   
}

/**
 * Encrypt or decrypt, depending on flag 'should_encrypt'
 */
//there is problem in out_len, return string should be the join of all cipher_buf
unsigned char* en_de_crypt(int should_encrypt) {

    const unsigned BUFSIZE=4096;
    unsigned char *read_buf = malloc(BUFSIZE);
    unsigned char *cipher_buf;
    unsigned blocksize;
    int out_len;
    FILE *ifp2, *ofp2;
    assign_fp(should_encrypt, &ifp2, &ofp2);
    EVP_CIPHER_CTX ctx;
    EVP_CipherInit(&ctx, EVP_aes_256_cbc(), KEY, IV, should_encrypt);
    blocksize = EVP_CIPHER_CTX_block_size(&ctx);
    cipher_buf = malloc(BUFSIZE + blocksize);

    while (1) {
        int numRead = fread(read_buf, sizeof(unsigned char), BUFSIZE, ifp2);
        EVP_CipherUpdate(&ctx, cipher_buf, &out_len, (unsigned char *)read_buf, numRead);
        write_msg(should_encrypt, cipher_buf, sizeof(unsigned char), out_len, ofp2);
        if (numRead < BUFSIZE) { // EOF
            break;
        }
    }

    // Now cipher the final block and write it out.

    EVP_CipherFinal(&ctx, cipher_buf, &out_len);
    write_msg(should_encrypt, cipher_buf, sizeof(unsigned char), out_len, ofp2);
    // Free memory
    //free(cipher_buf);
    free(read_buf);
    return strdup(cipher_buf);
}

int main(int argc, char *argv[]) {

    en_de_crypt(TRUE);

    //Decrypt file now
    /****bug when input string is too long
    *****/
    printf("%s", en_de_crypt(FALSE));
    return 0;
}
