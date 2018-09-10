//
// Created by Ivano on 14/08/2018.
//

#include "State.h"

void State::shiftRows(fast_uint8 *const state) {
    AESArithmetics::SHIFT_RIGHT_THREE_TIMES(state, 1);
    AESArithmetics::SHIFT_LEFT_TWO_TIMES(state, 2);
    AESArithmetics::SHIFT_LEFT_THREE_TIMES(state,3);
}

void State::invShiftRows(fast_uint8 *const state) {
    AESArithmetics::SHIFT_LEFT_THREE_TIMES(state,1);
    AESArithmetics::SHIFT_LEFT_TWO_TIMES(state,2);
    AESArithmetics::SHIFT_RIGHT_THREE_TIMES(state, 3);
}

void State::mixColumns(fast_uint8 *const state) {
    fast_uint8 s0c, s1c, s2c, s3c;
    for (fast_uint8 c = 0; c < COLUMNS; c++) {
        s0c = state[STATE_AT(0, c)];
        s1c = state[STATE_AT(1, c)];
        s2c = state[STATE_AT(2, c)];
        s3c = state[STATE_AT(3, c)];
        state[STATE_AT(0, c)] = BMUL(s0c, 2) ^ BMUL(s1c, 3) ^ s2c ^ s3c;
        state[STATE_AT(1, c)] = s0c ^ BMUL(s1c, 2) ^ BMUL(s2c, 3) ^ s3c;
        state[STATE_AT(2, c)] = s0c ^ s1c ^ BMUL(s2c, 2) ^ BMUL(s3c, 3);
        state[STATE_AT(3, c)] = BMUL(s0c, 3) ^ s1c ^ s2c ^ BMUL(s3c, 2);
    }
}

void State::invMixColumns(fast_uint8 *const state) {
    fast_uint8 s0c, s1c, s2c, s3c;
    for (fast_uint8 c = 0; c < COLUMNS; c++) {
        s0c = state[STATE_AT(0, c)];
        s1c = state[STATE_AT(1, c)];
        s2c = state[STATE_AT(2, c)];
        s3c = state[STATE_AT(3, c)];
        state[STATE_AT(0, c)] = BMUL(s0c, E) ^ BMUL(s1c, B) ^ BMUL(s2c, D) ^ BMUL(s3c, 9);
        state[STATE_AT(1, c)] = BMUL(s0c, 9) ^ BMUL(s1c, E) ^ BMUL(s2c, B) ^ BMUL(s3c, D);
        state[STATE_AT(2, c)] = BMUL(s0c, D) ^ BMUL(s1c, 9) ^ BMUL(s2c, E) ^ BMUL(s3c, B);
        state[STATE_AT(3, c)] = BMUL(s0c, B) ^ BMUL(s1c, D) ^ BMUL(s2c, 9) ^ BMUL(s3c, E);
    }
}


void State::addRoundKey(fast_uint8 *const state, const fast_uint8 *const key) {
    for (fast_uint8 column = 0; column < COLUMNS; column++) {
        for (fast_uint8 row = 0; row < ROWS; row++) {
            state[STATE_AT(row, column)] ^= key[STATE_AT(row, column)];
        }
    }
}






