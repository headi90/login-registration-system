#include "md5PasswordHasher.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string Md5PasswordHasher::hash(const std::string& input)
{
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    md = EVP_get_digestbyname("md5");
    if (!md) {
        std::cerr << "Unknown message digest %s\n";
        return "";
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    std::stringstream md5SS;
    for (size_t i = 0; i < md_len; i++)
        md5SS << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(md_value[i]);

    return md5SS.str();
}
