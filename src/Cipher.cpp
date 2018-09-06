//
// Created by Ivano on 06/09/2018.
//

#include "Cipher.h"

void Cipher::crypt(uint8_t *input) const  {
    State s(input);
    s.addRoundKey(key, 0);
    for (uint8_t round = 1; round < key.rounds; round++) {
        s.subBytes();
        s.shiftRows();
        s.mixColumns();
        s.addRoundKey(key, round);
    }
    s.subBytes();
    s.shiftRows();
    s.addRoundKey(key, key.rounds);
}

void Cipher::decrypt(uint8_t *input) const  {
    State s(input);
    s.addRoundKey(key, key.rounds);
    for (auto round = static_cast<uint8_t>(key.rounds - 1); round > 0; round--) {
        s.invShiftRows();
        s.invSubBytes();
        s.addRoundKey(key, round);
        s.invMixColumns();
    }
    s.invShiftRows();
    s.invSubBytes();
    s.addRoundKey(key, 0);
}