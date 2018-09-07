//
// Created by Ivano on 18/08/2018.
//

#ifndef AES_ARITHMETICS_H
#define AES_ARITHMETICS_H

#include <cstdint>


#define ROWS 4
#define COLUMNS 4

#define STATE_AT(x, y) static_cast<uint8_t>(((x) + (y)*COLUMNS ))

#define MUL_POLYNOMIAL 0x11B
#define BYTES_IN_WORD 4U
#define STATE_DIM (16)
#define BIT_SUM(n1, n2) (n1 ^ n2)

#define OVERFLOW_IF_SHIFT(val) ((val) >= 0x80)

inline uint8_t XTIME(const uint8_t val) {
    uint8_t toReturn = val;
    toReturn <<= 1;
    if (OVERFLOW_IF_SHIFT(val))
        toReturn ^= MUL_POLYNOMIAL;
    return toReturn;
}

inline uint8_t BIT_MUL(const uint8_t n1, const uint8_t n2) {
    uint8_t res = 0;
    uint8_t times = n2;
    uint8_t xTimeValue = n1;
    // Get n2 as a polynomial composed of sums of powers of two.
    // To do so loop through all of times bits and get every bit that is equal to 1
    while (times > 0) {
        if (times & 1) res ^= xTimeValue;
        xTimeValue = XTIME(xTimeValue);
        times >>= 1;
    }
    return res;
}

inline void WORD_SUM(const uint8_t *const w1, const uint8_t *const w2, uint8_t *const res) {
    for (uint8_t a = 0; a < 4; a++) res[a] = w1[a] ^ w2[a];
}

inline void ROTATE_WORD(uint8_t *const word) {
    uint8_t tmp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = tmp;
}

inline void SHIFT_LEFT_THREE_TIMES(uint8_t * const state,const uint8_t row) {
    uint8_t temp = state[STATE_AT(row,0)];
    state[STATE_AT(row,0)] =  state[STATE_AT(row,3)];
    state[STATE_AT(row,3)] = state[STATE_AT(row,2)];
    state[STATE_AT(row,2)] = state[STATE_AT(row,1)];
    state[STATE_AT(row,1)] = temp;

}

inline void SHIFT_LEFT_TWO_TIMES(uint8_t * const state,const  uint8_t row) {
    uint8_t temp1 = state[STATE_AT(row,2)];
    uint8_t temp2 = state[STATE_AT(row,3)];
    state[STATE_AT(row,2)] = state[STATE_AT(row, 0)];
    state[STATE_AT(row,3)] = state[STATE_AT(row, 1)];
    state[STATE_AT(row,0)] = temp1;
    state[STATE_AT(row,1)] = temp2;
}

inline void SHIFT_RIGHT_THREE_TIMES(uint8_t * const state,const uint8_t row) {
    uint8_t temp = state[STATE_AT(row,0)];
    state[STATE_AT(row,0)] = state[STATE_AT(row, 1)];
    state[STATE_AT(row,1)] = state[STATE_AT(row, 2)];
    state[STATE_AT(row,2)] = state[STATE_AT(row, 3)];
    state[STATE_AT(row,3)] = temp;
}

#endif //AES_ARITHMETICS_H
