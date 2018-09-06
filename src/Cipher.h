//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_CIPHER_H
#define AES_CIPHER_H

#include <cstdint>
#include <iostream>
#include "State.h"

#endif //AES_CIPHER_H

class Cipher {
    AESKey key;
public:
    Cipher(const uint8_t *_key, const uint8_t _key_length) : key(_key, _key_length) {}

    void crypt(uint8_t *input) const;

    void decrypt(uint8_t *input) const;
};
