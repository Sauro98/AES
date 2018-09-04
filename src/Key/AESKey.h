//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_VIRTUALKEY_H
#define AES_VIRTUALKEY_H


#include <cstdint>
#include "../Arithmetics.h"
#include <sstream>

#define AES_128_ROUNDS 10
#define AES_192_ROUNDS 12
#define AES_256_ROUNDS 14

#define AES_128_WORDS 4U
#define AES_192_WORDS 6U
#define AES_256_WORDS 8U

#define BYTES_IN_WORD 4U
#define WORDS_NUMBER 4U

#define BYTES_FOR_128 128/8
#define BYTES_FOR_192 192/8
#define BYTES_FOR_256 256/8

inline uint8_t RCON_POW(uint8_t pow) {
    if (pow == 0)
        return 0x01;
    if (pow == 1)
        return 0x02;
    uint8_t toReturn = 0x02;
    for (uint8_t a = 1; a < pow; a++)
        toReturn = BIT_MUL(toReturn, 0x02);
    return toReturn;
}

class AESKey {

    uint8_t keyWords;
    uint8_t round;
public:
    uint8_t rounds;
    uint8_t *key;

    AESKey(const uint8_t *_key, uint16_t length);

    bool hasNextRound() {
        return round < rounds - 1;
    }

    uint8_t *getRoundKey() {
        round++;
        return &key[(round - 1) * BYTES_IN_WORD];
    }

    void expandKey(const uint8_t *original);
};

#endif //AES_VIRTUALKEY_H
