//
// Created by Ivano on 14/08/2018.
//

#ifndef AES_STATE_H
#define AES_STATE_H

#include <cstdint>
#include "BitMulConstants.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include "SBox.h"

namespace State {
    void shiftRows(fast_uint8 *state);

    void invShiftRows(fast_uint8 *state);

    void mixColumns(fast_uint8 *state);

    void invMixColumns(fast_uint8 *state);

    void addRoundKey(fast_uint8 *state, const fast_uint8 *key);

    inline void subBytes(fast_uint8 *const state) { SELF_SUB_BYTES(state); };

    inline void invSubBytes(fast_uint8 *const state) { SELF_INV_SUB_BYTES(state); };
};


#endif //AES_STATE_H
