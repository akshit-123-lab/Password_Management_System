#include "utils.h"
#include <openssl/evp.h>
#include <cstdlib>
#include <ctime>

std::string hashPassword(const std::string& password) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, password.c_str(), password.size());
    EVP_DigestFinal_ex(ctx, hash, &hash_len);
    EVP_MD_CTX_free(ctx);
    return std::string((char*)hash, hash_len);
}

std::string generateRandomPassword(int length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@$!%*?&";
    std::string password;
    std::srand(std::time(nullptr));
    for (int i = 0; i < length; ++i) {
        password += characters[std::rand() % characters.size()];
    }
    return password;
}
