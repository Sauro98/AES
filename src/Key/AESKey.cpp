//
// Created by Ivano on 16/08/2018.
//

#include <iostream>
#include "AESKey.h"
#include "../SBox.h"
#include "InvalidKeyLengthException.h"

AESKey::AESKey(const uint8_t *_key, const uint16_t length) {

    if (length == BYTES_FOR_128) {
        rounds = AES_128_ROUNDS;
        keyWords = AES_128_WORDS;
    } else if (length == BYTES_FOR_192) {
        rounds = AES_192_ROUNDS;
        keyWords = AES_192_WORDS;
    } else if (length == BYTES_FOR_256) {
        rounds = AES_256_ROUNDS;
        keyWords = AES_256_WORDS;
    } else {
        std::stringstream ss;
        ss << "The length of the key should be ";
        ss << BYTES_FOR_128 << ", " << BYTES_FOR_192 << " or " << BYTES_FOR_256 << " characters long. ";
        ss << "Yours was " << length << " characters long";
        throw InvalidKeyLenghtException(ss.str());
    }
    expandKey(_key);
    round = 0;
}

//TODO:: pow should not be calculated every time, yust shifted
void AESKey::expandKey(const uint8_t *original) {
    auto expanded = new uint8_t[(rounds + 1) * WORDS_NUMBER * BYTES_IN_WORD];
    uint32_t index = 0;
    uint8_t pow = 0;
    for (; index < (keyWords * BYTES_IN_WORD); index++)
        expanded[index] = original[index];
    index = (keyWords * BYTES_IN_WORD);
    for (; index < (rounds + 1) * WORDS_NUMBER * BYTES_IN_WORD; index += BYTES_IN_WORD) {
        uint8_t temp[4];
        for(uint8_t a = 0; a < 4; a++)
            temp[a] = expanded[index -  BYTES_IN_WORD + a];
        if ((index/BYTES_IN_WORD) % keyWords == 0) {
            uint8_t res[4];
            ROTATE_WORD(temp, res);
            SUB_WORD(res, temp);
            uint8_t rot[4] = {0x00, 0x00, 0x00, 0x00};
            rot[0] = RCON_POW(pow++);
            WORD_SUM(temp, rot, temp);
        } else if (keyWords == AES_256_WORDS && index % keyWords == 4) {
            SUB_WORD(temp, temp);
        }
        for (int a = 0; a < 4; a++)
            expanded[index + a] =
                    temp[a] ^ expanded[index + a - (keyWords * BYTES_IN_WORD)];
    }
    key = expanded;
}

