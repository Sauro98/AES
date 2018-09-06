//
// Created by Ivano on 14/08/2018.
//

#ifndef AES_STATE_H
#define AES_STATE_H

#include <cstdint>
#include "../Key/AESKey.h"

#include <cstring>
#include <iostream>
#include <iomanip>
#include "SBox.h"

inline void ARR_SWAP(uint8_t *const arr, uint8_t pos1, uint8_t pos2) {
    uint8_t tmp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = tmp;
}

namespace State {
    void shiftRows(uint8_t *state);

    void invShiftRows(uint8_t *state);

    void mixColumns(uint8_t *state);

    void invMixColumns(uint8_t *state);

    void addRoundKey(uint8_t *state, const uint8_t *key);

    inline void subBytes(uint8_t *const state) { SELF_SUB_BYTES(state); };

    inline void invSubBytes(uint8_t *const state) { SELF_INV_SUB_BYTES(state); };
};


#endif //AES_STATE_H
