#include <encry_decry.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


unsigned char ciphertext[128];



int encrypt_openssl(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
 *  *    * and IV size appropriate for your cipher
 *   *       * In this example we are using 256 bit AES (i.e. a 256 bit key). The
 *    *          * IV size for *most* modes is the same as the block size. For AES this
 *     *             * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
 *  *    * EVP_EncryptUpdate can be called multiple times if necessary
 *   *       */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
 *  *    * this stage.
 *   *       */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}


int decrypt_openssl(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
 *  *    * and IV size appropriate for your cipher
 *   *       * In this example we are using 256 bit AES (i.e. a 256 bit key). The
 *    *          * IV size for *most* modes is the same as the block size. For AES this
 *     *             * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
 *  *    * EVP_DecryptUpdate can be called multiple times if necessary
 *   *       */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
 *  *    * this stage.
 *   *       */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}


//openssl hadle error
void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}


int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext)
{
   /* A 256 bit key */
  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";
  //using openssl
  
  //get the encrypted DB_NAME
   char cipher[256] = ""; 
   int textlen = strlen(getenv("DB_NAME"));
   strncpy(cipher, getenv("DB_NAME"), textlen);
   unsigned char *plaintext2 = (unsigned char *)cipher;//encrypted DB_NAME
   unsigned char ciphertext2[128];
   int ciphertext_len = encrypt_openssl (plaintext2, strlen ((char *)plaintext), key, iv,
                            ciphertext2);
   //output encrypted DB_NAME to file
   char path_db[256] = "";
   int path_db_len = strlen(getenv("WS_DATA_PATH"));
   strncpy(path_db, getenv("WS_DATA_PATH"), path_db_len);
   strcat(path_db, "/DB_NAME_ENCRY.txt");
   freopen(path_db, "w", stdout);
   BIO_dump_fp (stdout, (const char *)ciphertext2, ciphertext_len);
   return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext)
{
  /* A 256 bit key */
  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";
  //using openssl
  //get encrypted dbname from environment variable, the variable was setted by read from DB_NAME_ENCRY file
   unsigned char ciphertext2[256] = "";
   int textlen = strlen(getenv("DB_NAME_ENCRY"));
   strncpy(ciphertext2, (unsigned char*)getenv("DB_NAME_ENCRY"), textlen);

    /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];
  int ciphertext_len2 = encrypt("", 0,"");
  int decryptedtext_len;
   /* Decrypt the ciphertext */
  decryptedtext_len = decrypt_openssl(ciphertext2, ciphertext_len2, key, iv,
    decryptedtext);
  
  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  //printf("@decryptedtext@");
  printf("%s\n", decryptedtext);
  return decryptedtext_len;
}



