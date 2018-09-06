//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_KEY_H
#define AES_KEY_H


#include <cstdint>
#include "../cipher/Arithmetics.h"
#include <sstream>

#define AES_128_ROUNDS (10)
#define AES_192_ROUNDS (12)
#define AES_256_ROUNDS (14)

#define BYTES_FOR_128 (128/8)
#define BYTES_FOR_192 (192/8)
#define BYTES_FOR_256 (256/8)

#define AES_256_WORDS (BYTES_FOR_256/4)

#define WORDS_NUMBER 4U

#define KEY_ROUND_INDEX(round) (BYTES_IN_WORD * ( (round) * WORDS_NUMBER))


#define NEXT_POW(pow) pow = BIT_MUL(pow, 0x02);
#define CREATE_POW_ROT_WORD(pow) uint8_t aes_pow_rot_word[4] = {0x00, 0x00, 0x00, 0x00};\
                             aes_pow_rot_word[0] = pow;\
                             NEXT_POW(pow);
#define POW_ROT_WORD aes_pow_rot_word
#define ROTATE_WITH_POW(word, pow) CREATE_POW_ROT_WORD(pow);\
                          WORD_SUM(word, POW_ROT_WORD, word);

class AESKey {
    const uint8_t *key;
    const uint8_t *eqInvKey;
public:
    uint8_t rounds;

    AESKey(const uint8_t *_key, uint16_t length);

    ~AESKey() { delete[](key); }

    const uint8_t *getKeyWordAt(uint8_t index) {
        return &key[index * BYTES_IN_WORD];
    }

    const uint8_t *getKeyForRound(uint8_t round) const {
        return &key[KEY_ROUND_INDEX(round)];
    }

    const uint8_t *getEqInvKeyForRound(uint8_t round) const {
        return &eqInvKey[KEY_ROUND_INDEX(round)];
    }

    void expandKey(const uint8_t *original, uint8_t keyWords);
};

#endif //AES_KEY_H
