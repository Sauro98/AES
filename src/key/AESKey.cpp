//
// Created by Ivano on 16/08/2018.
//

#include <iostream>
#include "AESKey.h"
#include "../cipher/SBox.h"
#include "InvalidKeyLengthException.h"
#include "../cipher/State.h"

AESKey::AESKey(const fast_uint8 *_key, const uint16_t length) {
    if (length == BYTES_FOR_128) {
        rounds = AES_128_ROUNDS;
    } else if (length == BYTES_FOR_192) {
        rounds = AES_192_ROUNDS;
    } else if (length == BYTES_FOR_256) {
        rounds = AES_256_ROUNDS;
    } else {
        std::stringstream ss;
        ss << "The length of the key should be ";
        ss << BYTES_FOR_128 << ", " << BYTES_FOR_192 << " or " << BYTES_FOR_256 << " characters long. ";
        ss << "Yours was " << length << " characters long";
        throw InvalidKeyLenghtException(ss.str());
    }
    expandKey(_key, static_cast<fast_uint8>(length / 4));
}

void AESKey::expandKey(const fast_uint8 * const original, fast_uint8 keyWords) {
    auto * expanded = new fast_uint8[(rounds + 1) * WORDS_NUMBER * BYTES_IN_WORD];

    fast_uint8 pow = 0x01;
    for (uint16_t index = 0; index < (keyWords * BYTES_IN_WORD); index++)
        expanded[index] = original[index];

    for (auto index = static_cast<uint16_t>(keyWords * BYTES_IN_WORD);
         index < (rounds + 1) * WORDS_NUMBER * BYTES_IN_WORD; index += BYTES_IN_WORD) {

        fast_uint8 *currWord = &expanded[index];

        for (fast_uint8 a = 0; a < BYTES_IN_WORD; a++)
            currWord[a] = expanded[index - BYTES_IN_WORD + a];

        if ((index / BYTES_IN_WORD) % keyWords == 0) {
            AESArithmetics::ROTATE_WORD(currWord);
            SUB_WORD(currWord);
            ROTATE_WITH_POW(currWord, pow);
        } else if (keyWords == AES_256_WORDS && (index / BYTES_IN_WORD) % keyWords == 4) {
            SUB_WORD(currWord);
        }

        AESArithmetics::WORD_SUM(currWord, &expanded[index - (keyWords * BYTES_IN_WORD)], currWord);
    }


    key = expanded;
    auto * eqKey = new fast_uint8[(rounds + 1) * WORDS_NUMBER * BYTES_IN_WORD];
    for(size_t a = 0;  a < (rounds + 1) * WORDS_NUMBER * BYTES_IN_WORD; a++){
        eqKey[a] = expanded[a];
    }


    for(uint16_t index = 1; index < rounds; index++){
        fast_uint8* arr = &eqKey[KEY_ROUND_INDEX(index)];
        State::invMixColumns(arr);
    }
    eqInvKey = eqKey;
}

