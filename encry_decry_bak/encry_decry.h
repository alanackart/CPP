#ifndef ENCRY_DECRY_H
#define ENCRY_DECRY_H

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext);

#endif
