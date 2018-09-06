//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_CIPHER_H
#define AES_CIPHER_H

#include <cstdint>
#include <iostream>
#include "State.h"
#include <fstream>
#include <sstream>

class Cipher {
    AESKey key;
public:
    Cipher(const uint8_t *_key, const uint8_t _key_length) : key(_key, _key_length) {}

    void crypt(uint8_t *input) const;

    void decrypt(uint8_t *input) const;

    std::unique_ptr<uint8_t[]> cryptFile(const char* filename) const;
    std::unique_ptr<uint8_t[]> decryptFile(const char* filename) const;

private:
    uint8_t* readFile(const char* fileName, size_t* lenght) const;
    void writeToFile(const char* fileName, const uint8_t* content, size_t length) const;
};

#endif //AES_CIPHER_H
