//
// Created by Ivano on 14/08/2018.
//

#include "State.h"

void State::shiftRows(uint8_t *const state) {
    ARR_SWAP(state, STATE_AT(1, 0), STATE_AT(1, 1)); // -> 11 10 12 13
    ARR_SWAP(state, STATE_AT(1, 1), STATE_AT(1, 2)); // -> 11 12 10 13
    ARR_SWAP(state, STATE_AT(1, 2), STATE_AT(1, 3)); // -> 11 12 13 10
    ARR_SWAP(state, STATE_AT(2, 0), STATE_AT(2, 2)); // -> 22 21 20 23
    ARR_SWAP(state, STATE_AT(2, 1), STATE_AT(2, 3)); // -> 22 23 20 21
    ARR_SWAP(state, STATE_AT(3, 3), STATE_AT(3, 2)); // -> 30 31 33 32
    ARR_SWAP(state, STATE_AT(3, 2), STATE_AT(3, 1)); // -> 30 33 31 32
    ARR_SWAP(state, STATE_AT(3, 1), STATE_AT(3, 0)); // -> 33 30 31 32
}

void State::invShiftRows(uint8_t *const state) {
    ARR_SWAP(state, STATE_AT(1, 3), STATE_AT(1, 2)); // -> 10 11 13 12
    ARR_SWAP(state, STATE_AT(1, 2), STATE_AT(1, 1)); // -> 10 13 11 12
    ARR_SWAP(state, STATE_AT(1, 1), STATE_AT(1, 0)); // -> 13 10 11 12
    ARR_SWAP(state, STATE_AT(2, 0), STATE_AT(2, 2)); // -> 22 21 20 23
    ARR_SWAP(state, STATE_AT(2, 1), STATE_AT(2, 3)); // -> 22 23 20 21
    ARR_SWAP(state, STATE_AT(3, 0), STATE_AT(3, 1)); // -> 31 30 32 33
    ARR_SWAP(state, STATE_AT(3, 1), STATE_AT(3, 2)); // -> 31 32 30 33
    ARR_SWAP(state, STATE_AT(3, 2), STATE_AT(3, 3)); // -> 31 32 33 30
}

void State::mixColumns(uint8_t *const state) {
    uint8_t s0c;
    uint8_t s1c;
    uint8_t s2c;
    uint8_t s3c;
    for (uint8_t c = 0; c < COLUMNS; c++) {
        s0c = state[STATE_AT(0, c)];
        s1c = state[STATE_AT(1, c)];
        s2c = state[STATE_AT(2, c)];
        s3c = state[STATE_AT(3, c)];
        state[STATE_AT(0, c)] = BIT_MUL_02(s0c) ^ BIT_MUL_03(s1c) ^ s2c ^ s3c;
        state[STATE_AT(1, c)] = s0c ^ BIT_MUL_02(s1c) ^ BIT_MUL_03(s2c) ^ s3c;
        state[STATE_AT(2, c)] = s0c ^ s1c ^ BIT_MUL_02(s2c) ^ BIT_MUL_03(s3c);
        state[STATE_AT(3, c)] = BIT_MUL_03(s0c) ^ s1c ^ s2c ^ BIT_MUL_02(s3c);
    }
}

void State::invMixColumns(uint8_t *const state) {
    uint8_t s0c;
    uint8_t s1c;
    uint8_t s2c;
    uint8_t s3c;
    for (uint8_t c = 0; c < COLUMNS; c++) {
        s0c = state[STATE_AT(0, c)];
        s1c = state[STATE_AT(1, c)];
        s2c = state[STATE_AT(2, c)];
        s3c = state[STATE_AT(3, c)];
        state[STATE_AT(0, c)] = BIT_MUL_0E(s0c) ^ BIT_MUL_0B(s1c) ^ BIT_MUL_0D(s2c) ^ BIT_MUL_09(s3c);
        state[STATE_AT(1, c)] = BIT_MUL_09(s0c) ^ BIT_MUL_0E(s1c) ^ BIT_MUL_0B(s2c) ^ BIT_MUL_0D(s3c);
        state[STATE_AT(2, c)] = BIT_MUL_0D(s0c) ^ BIT_MUL_09(s1c) ^ BIT_MUL_0E(s2c) ^ BIT_MUL_0B(s3c);
        state[STATE_AT(3, c)] = BIT_MUL_0B(s0c) ^ BIT_MUL_0D(s1c) ^ BIT_MUL_09(s2c) ^ BIT_MUL_0E(s3c);
    }
}


void State::addRoundKey(uint8_t *const state, const uint8_t *const key) {
    for (uint8_t column = 0; column < COLUMNS; column++) {
        for (uint8_t row = 0; row < ROWS; row++) {
            state[STATE_AT(row, column)] ^=  key[STATE_AT(row, column)];
        }
    }
}






