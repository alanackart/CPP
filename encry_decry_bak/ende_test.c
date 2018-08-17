#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define N_ARGUS 2

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
 *    * and IV size appropriate for your cipher
 *       * In this example we are using 256 bit AES (i.e. a 256 bit key). The
 *          * IV size for *most* modes is the same as the block size. For AES this
 *             * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
 *    * EVP_EncryptUpdate can be called multiple times if necessary
 *       */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
 *    * this stage.
 *       */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
 *    * and IV size appropriate for your cipher
 *       * In this example we are using 256 bit AES (i.e. a 256 bit key). The
 *          * IV size for *most* modes is the same as the block size. For AES this
 *             * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
 *    * EVP_DecryptUpdate can be called multiple times if necessary
 *       */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
 *    * this stage.
 *       */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}


void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int main (int argc, char *argv[])
{
 FILE* fp;
 char path[256] = "";
 int path_len = strlen(getenv("WS_LOG_PATH"));
 strncpy(path, getenv("WS_LOG_PATH"), path_len);
 //printf("path is %s\n", path);
 strcat(path, "/encry_decry.log\n");
 //printf("now path is %s\n", path);
 fp = fopen(path, "w");
  /* Set up the key and iv. Do I need to say to not hard code these in a
 *    * real application? :-)
 *       */
  //handle arguments error
  if(argc != N_ARGUS)
  {
	fprintf(fp, "argc number is incorrect\n");
	return 0;
  }
//  if(setenv("ciphertext", "fis@fis", 1) != 0)//set u
//  {
     //printf("set unsuccessful,  %d\n", errno);
//  }
  char cipher[256] = "";
 int textlen = strlen(getenv(argv[1]));
  strncpy(cipher, getenv(argv[1]), textlen);
  //strncpy(cipher, argv[1], strlen(argv[1]));
  //printf("cipher is %s\n", cipher); 

  /* A 256 bit key */
  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";

  /* Message to be encrypted */
  // unsigned char *plaintext =
  //              (unsigned char *)"The quick brown fox jumps over the lazy dog";
  int len = strlen(cipher);
  //printf("len of cipher is %d\n", len);
 // strncpy(plaintext, cipher, len);
  unsigned char *plaintext = (unsigned char *)cipher;
 // plaintext[strlen(cipher)] = '\n';
  /* Buffer for ciphertext. Ensure the buffer is long enough for the
 *    * ciphertext which may be longer than the plaintext, dependant on the

q
q
 *       * algorithm and mode
 *          */
  unsigned char ciphertext[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

  int decryptedtext_len, ciphertext_len;
  /* Encrypt the plaintext */
  ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,
                            ciphertext);

  /* Do something useful with the ciphertext here */
 // printf("Ciphertext is:\n");
 char path_db[256] = "";
 int path_db_len = strlen(getenv("WS_DATA_PATH"));
 strncpy(path_db, getenv("WS_DATA_PATH"), path_db_len);
 strcat(path_db, "/DB_NAME_ENCRY.txt");
  freopen(path_db, "w", stdout);
  BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
  
  /* Decrypt the ciphertext */
  decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
    decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  //printf("@decryptedtext@");
  // printf("%s\n", decryptedtext);

  return 0;
}
