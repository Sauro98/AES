//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_KEY_H
#define AES_KEY_H


#include <cstdint>
#include "../Arithmetics.h"
#include <sstream>

#define AES_128_ROUNDS (10)
#define AES_192_ROUNDS (12)
#define AES_256_ROUNDS (14)

#define BYTES_FOR_128 (128/8)
#define BYTES_FOR_192 (192/8)
#define BYTES_FOR_256 (256/8)

#define AES_256_WORDS (BYTES_FOR_256/4)

#define BYTES_IN_WORD 4U
#define WORDS_NUMBER 4U

#define KEY_ROUND_COLUMN_INDEX(round, column) (BYTES_IN_WORD * ( (round) * WORDS_NUMBER + (column)))

class AESKey {
    const uint8_t *key;
public:
    uint8_t rounds;

    AESKey(const uint8_t *_key, uint16_t length);

    ~AESKey() { delete[](key); }

    const uint8_t *getKeyWordAt(uint8_t index) {
        return &key[index * BYTES_IN_WORD];
    }

    const uint8_t *getKeyFor(uint8_t round, uint8_t column) const {
        return &key[KEY_ROUND_COLUMN_INDEX(round, column)];
    }

    void expandKey(const uint8_t *original, uint8_t keyWords);
};

#endif //AES_KEY_H
