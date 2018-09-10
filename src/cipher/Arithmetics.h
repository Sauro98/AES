//
// Created by Ivano on 18/08/2018.
//

#ifndef AES_ARITHMETICS_H
#define AES_ARITHMETICS_H

#include <cstdint>


#define ROWS 4
#define COLUMNS 4

#define STATE_AT(x, y) static_cast<fast_uint8>(((x) + (y)*COLUMNS ))

#define MUL_POLYNOMIAL 0x11B
#define BYTES_IN_WORD 4U
#define STATE_DIM (16)
#define BIT_SUM(n1, n2) (n1 ^ n2)

#define OVERFLOW_IF_SHIFT(val) ((val) >= 0x80)

#define fast_uint8 uint_fast8_t

namespace AESArithmetics {

    inline fast_uint8 XTIME(const fast_uint8 val) {
        fast_uint8 toReturn = val;
        toReturn <<= 1;
        if (OVERFLOW_IF_SHIFT(val))
            toReturn ^= MUL_POLYNOMIAL;
        return toReturn;
    }

    inline fast_uint8 BIT_MUL(const fast_uint8 n1, const fast_uint8 n2) {
        fast_uint8 res = 0;
        fast_uint8 times = n2;
        fast_uint8 xTimeValue = n1;
        // Get n2 as a polynomial composed of sums of powers of two.
        // To do so loop through all of times bits and get every bit that is equal to 1
        while (times > 0) {
            if (times & 1) res ^= xTimeValue;
            xTimeValue = XTIME(xTimeValue);
            times >>= 1;
        }
        return res;
    }

    inline void WORD_SUM(const fast_uint8 *const w1, const fast_uint8 *const w2, fast_uint8 *const res) {
        for (fast_uint8 a = 0; a < 4; a++) res[a] = w1[a] ^ w2[a];
    }

    inline void ROTATE_WORD(fast_uint8 *const word) {
        fast_uint8 tmp = word[0];
        word[0] = word[1];
        word[1] = word[2];
        word[2] = word[3];
        word[3] = tmp;
    }

    inline void SHIFT_LEFT_THREE_TIMES(fast_uint8 *const state, const fast_uint8 row) {
        fast_uint8 temp = state[STATE_AT(row, 0)];
        state[STATE_AT(row, 0)] = state[STATE_AT(row, 3)];
        state[STATE_AT(row, 3)] = state[STATE_AT(row, 2)];
        state[STATE_AT(row, 2)] = state[STATE_AT(row, 1)];
        state[STATE_AT(row, 1)] = temp;

    }

    inline void SHIFT_LEFT_TWO_TIMES(fast_uint8 *const state, const fast_uint8 row) {
        fast_uint8 temp1 = state[STATE_AT(row, 2)];
        fast_uint8 temp2 = state[STATE_AT(row, 3)];
        state[STATE_AT(row, 2)] = state[STATE_AT(row, 0)];
        state[STATE_AT(row, 3)] = state[STATE_AT(row, 1)];
        state[STATE_AT(row, 0)] = temp1;
        state[STATE_AT(row, 1)] = temp2;
    }

    inline void SHIFT_RIGHT_THREE_TIMES(fast_uint8 *const state, const fast_uint8 row) {
        fast_uint8 temp = state[STATE_AT(row, 0)];
        state[STATE_AT(row, 0)] = state[STATE_AT(row, 1)];
        state[STATE_AT(row, 1)] = state[STATE_AT(row, 2)];
        state[STATE_AT(row, 2)] = state[STATE_AT(row, 3)];
        state[STATE_AT(row, 3)] = temp;
    }
}
#endif //AES_ARITHMETICS_H
