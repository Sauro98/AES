//
// Created by Ivano on 14/08/2018.
//

#include "State.h"

void State::shiftRows(uint8_t *const state) {
    SHIFT_RIGHT_THREE_TIMES(state, 1);
    SHIFT_LEFT_TWO_TIMES(state, 2);
    SHIFT_LEFT_THREE_TIMES(state,3);
}

void State::invShiftRows(uint8_t *const state) {
    SHIFT_LEFT_THREE_TIMES(state,1);
    SHIFT_LEFT_TWO_TIMES(state,2);
    SHIFT_RIGHT_THREE_TIMES(state, 3);
}

void State::mixColumns(uint8_t *const state) {
    uint8_t s0c, s1c, s2c, s3c;
    for (uint8_t c = 0; c < COLUMNS; c++) {
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

void State::invMixColumns(uint8_t *const state) {
    uint8_t s0c, s1c, s2c, s3c;
    for (uint8_t c = 0; c < COLUMNS; c++) {
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


void State::addRoundKey(uint8_t *const state, const uint8_t *const key) {
    for (uint8_t column = 0; column < COLUMNS; column++) {
        for (uint8_t row = 0; row < ROWS; row++) {
            state[STATE_AT(row, column)] ^= key[STATE_AT(row, column)];
        }
    }
}






