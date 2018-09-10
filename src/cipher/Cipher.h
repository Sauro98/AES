//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_CIPHER_H
#define AES_CIPHER_H

#include <cstdint>
#include <iostream>
#include "State.h"
#include "../key/AESKey.h"
#include <fstream>
#include <sstream>

class Cipher {
    AESKey key;
public:
    Cipher(const fast_uint8 *_key, const fast_uint8 _key_length) : key(_key, _key_length) {}

    void crypt(fast_uint8 *input) const;

    void decrypt(fast_uint8 *input) const;

    std::unique_ptr<fast_uint8[]> cryptFile(const char* filename) const;
    std::unique_ptr<fast_uint8[]> decryptFile(const char* filename) const;

private:
    fast_uint8* readFile(const char* fileName, size_t* lenght) const;
    void writeToFile(const char* fileName, const fast_uint8* content, size_t length) const;
};

#endif //AES_CIPHER_H
