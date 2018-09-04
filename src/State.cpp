//
// Created by Ivano on 14/08/2018.
//

#include "State.h"

State::State(uint8_t *array, const std::string &_key) : key(reinterpret_cast<const uint8_t *>(_key.c_str()),
                                                            (uint16_t) _key.length()) {
    for (uint8_t r = 0; r < ROWS; r++) {
        for (uint8_t c = 0; c < COLUMNS; c++) {
            stateArray[COLUMNS * r + c] = array[r + COLUMNS * c];
        }
    }
}

uint8_t State::getElement(uint8_t index) const {
    return stateArray[index];
}

uint8_t State::getCell(uint8_t row, uint8_t column) const {
    return stateArray[STATE_AT(row, column)];
}

void State::setCell(uint8_t row, uint8_t column, uint8_t newValue) {
    stateArray[COLUMNS * row + column] = newValue;
}

void State::shiftRows() {
    ARR_SWAP(stateArray, STATE_AT(1, 0), STATE_AT(1, 1)); // -> 11 10 12 13
    ARR_SWAP(stateArray, STATE_AT(1, 1), STATE_AT(1, 2)); // -> 11 12 10 13
    ARR_SWAP(stateArray, STATE_AT(1, 2), STATE_AT(1, 3)); // -> 11 12 13 10
    ARR_SWAP(stateArray, STATE_AT(2, 0), STATE_AT(2, 2)); // -> 22 21 20 23
    ARR_SWAP(stateArray, STATE_AT(2, 1), STATE_AT(2, 3)); // -> 22 23 20 21
    ARR_SWAP(stateArray, STATE_AT(3, 3), STATE_AT(3, 2)); // -> 30 31 33 32
    ARR_SWAP(stateArray, STATE_AT(3, 2), STATE_AT(3, 1)); // -> 30 33 31 32
    ARR_SWAP(stateArray, STATE_AT(3, 1), STATE_AT(3, 0)); // -> 33 30 31 32
}

void State::invShiftRows() {
    ARR_SWAP(stateArray, STATE_AT(1, 3), STATE_AT(1, 2)); // -> 10 11 13 12
    ARR_SWAP(stateArray, STATE_AT(1, 2), STATE_AT(1, 1)); // -> 10 13 11 12
    ARR_SWAP(stateArray, STATE_AT(1, 1), STATE_AT(1, 0)); // -> 13 10 11 12
    ARR_SWAP(stateArray, STATE_AT(2, 0), STATE_AT(2, 2)); // -> 22 21 20 23
    ARR_SWAP(stateArray, STATE_AT(2, 1), STATE_AT(2, 3)); // -> 22 23 20 21
    ARR_SWAP(stateArray, STATE_AT(3, 0), STATE_AT(3, 1)); // -> 31 30 32 33
    ARR_SWAP(stateArray, STATE_AT(3, 1), STATE_AT(3, 2)); // -> 31 32 30 33
    ARR_SWAP(stateArray, STATE_AT(3, 2), STATE_AT(3, 3)); // -> 31 32 33 30
}

void State::mixColumns() {
    uint8_t s0c;
    uint8_t s1c;
    uint8_t s2c;
    uint8_t s3c;
    for (uint8_t c = 0; c < COLUMNS; c++) {
        s0c = stateArray[STATE_AT(0, c)];
        s1c = stateArray[STATE_AT(1, c)];
        s2c = stateArray[STATE_AT(2, c)];
        s3c = stateArray[STATE_AT(3, c)];
        stateArray[STATE_AT(0, c)] = BIT_MUL(0x02, s0c) ^ BIT_MUL(0x03, s1c) ^ s2c ^ s3c;
        stateArray[STATE_AT(1, c)] = s0c ^ BIT_MUL(0x02, s1c) ^ BIT_MUL(0x03, s2c) ^ s3c;
        stateArray[STATE_AT(2, c)] = s0c ^ s1c ^ BIT_MUL(0x02, s2c) ^ BIT_MUL(0x03, s3c);
        stateArray[STATE_AT(3, c)] = BIT_MUL(0x03, s0c) ^ s1c ^ s2c ^ BIT_MUL(0x02, s3c);
    }
}

void State::invMixColumns() {
    uint8_t s0c;
    uint8_t s1c;
    uint8_t s2c;
    uint8_t s3c;
    for (uint8_t c = 0; c < COLUMNS; c++) {
        s0c = stateArray[STATE_AT(0, c)];
        s1c = stateArray[STATE_AT(1, c)];
        s2c = stateArray[STATE_AT(2, c)];
        s3c = stateArray[STATE_AT(3, c)];
        stateArray[STATE_AT(0, c)] = BIT_MUL(0x0e, s0c) ^ BIT_MUL(0x0b, s1c) ^ BIT_MUL(0x0d, s2c) ^ BIT_MUL(0x09, s3c);
        stateArray[STATE_AT(1, c)] = BIT_MUL(0x09, s0c) ^ BIT_MUL(0x0e, s1c) ^ BIT_MUL(0x0b, s2c) ^ BIT_MUL(0x0d, s3c);
        stateArray[STATE_AT(2, c)] = BIT_MUL(0x0d, s0c) ^ BIT_MUL(0x09, s1c) ^ BIT_MUL(0x0e, s2c) ^ BIT_MUL(0x0b, s3c);
        stateArray[STATE_AT(3, c)] = BIT_MUL(0x0b, s0c) ^ BIT_MUL(0x0d, s1c) ^ BIT_MUL(0x09, s2c) ^ BIT_MUL(0x0e, s3c);
    }
}


void State::addRoundKey() {
    uint8_t *keyArr = key.getRoundKey();
    for (uint8_t column = 0; column < COLUMNS; column++) {
        for (uint8_t row = 0; row < ROWS; row++) {
            stateArray[STATE_AT(row, column)] = stateArray[STATE_AT(row, column)] ^ keyArr[ROWS * column + row];
        }
    }
}

void State::subBytes() {
    SUB_BYTES(stateArray, stateArray);
}

void State::invSubBytes() {
    INV_SUB_BYTES(stateArray, stateArray);
}




