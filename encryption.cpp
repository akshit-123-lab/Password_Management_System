#include "encryption.h"
#include <openssl/evp.h>
#include <openssl/rand.h>

void generateKeyIV(unsigned char* key, unsigned char* iv) {
    RAND_bytes(key, KEY_SIZE);
    RAND_bytes(iv, IV_SIZE);
}

std::string encryptPassword(const std::string& password, unsigned char* key, unsigned char* iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    int len;
    int ciphertext_len;
    unsigned char ciphertext[password.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc())];
    
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)password.c_str(), password.size());
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return std::string((char*)ciphertext, ciphertext_len);
}

std::string decryptPassword(const std::string& encrypted, unsigned char* key, unsigned char* iv) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    int len;
    int plaintext_len;
    unsigned char plaintext[encrypted.size()];

    EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)encrypted.c_str(), encrypted.size());
    plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return std::string((char*)plaintext, plaintext_len);
}
