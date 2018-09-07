//
// Created by Ivano on 14/08/2018.
//

#ifndef AES_STATE_H
#define AES_STATE_H

#include <cstdint>

#include <cstring>
#include <iostream>
#include <iomanip>
#include "SBox.h"

#define STATE_AT_ROW_XTIME(row, xtime) (s##row##c##xtime)
#define SRCX(row, xtime) STATE_AT_ROW_XTIME(row, xtime)

#define DECL_MIX_VARS_ROW(row) \
    uint8_t SRCX(row, 1), SRCX(row, 2), SRCX(row,3);

#define DECL_INV_MIX_VARS_ROW(row) \
    uint8_t SRCX(row,1), SRCX(row,2), SRCX(row,3),SRCX(row,9), SRCX(row,B), SRCX(row,D), SRCX(row,E);

#define DECL_MIX_VARS \
    DECL_MIX_VARS_ROW(0)\
    DECL_MIX_VARS_ROW(1)\
    DECL_MIX_VARS_ROW(2)\
    DECL_MIX_VARS_ROW(3)

#define DECL_INV_MIX_VARS \
    DECL_INV_MIX_VARS_ROW(0)\
    DECL_INV_MIX_VARS_ROW(1)\
    DECL_INV_MIX_VARS_ROW(2)\
    DECL_INV_MIX_VARS_ROW(3)

#define INIT_MIX_VARS_ROW(state, c, row) \
    SRCX(row,1) = state[STATE_AT(row, c)]; SRCX(row,2) = XTIME(SRCX(row,1)); SRCX(row,3) = BIT_MUL_03(SRCX(row, 1), SRCX(row, 2));

#define INIT_INV_MIX_VARS_ROW(state,c,row) \
    SRCX(row,1) = state[STATE_AT(row, c)]; SRCX(row,2) = XTIME(SRCX(row,1)); SRCX(row,3) = XTIME(SRCX(row,2));\
    SRCX(row,9) = BIT_MUL_09(SRCX(row,1), SRCX(row,3)); SRCX(row,B) = BIT_MUL_0B(SRCX(row, 9), SRCX(row,2));\
    SRCX(row,D) = BIT_MUL_0D(SRCX(row,3), SRCX(row,9)); SRCX(row,E) = BIT_MUL_0E(SRCX(row, 1), SRCX(row,2), SRCX(row, D));

#define INIT_MIX_VARS(state, c) \
    INIT_MIX_VARS_ROW(state,c,0)\
    INIT_MIX_VARS_ROW(state,c,1)\
    INIT_MIX_VARS_ROW(state,c,2)\
    INIT_MIX_VARS_ROW(state,c,3)

#define INIT_INV_MIX_VARS(state, c) \
    INIT_INV_MIX_VARS_ROW(state,c,0)\
    INIT_INV_MIX_VARS_ROW(state,c,1)\
    INIT_INV_MIX_VARS_ROW(state,c,2)\
    INIT_INV_MIX_VARS_ROW(state,c,3)

#define MIX_SOLVE_ROW_0 SRCX(0, 2) ^ SRCX(1, 3) ^ SRCX(2, 1) ^ SRCX(3, 1)
#define MIX_SOLVE_ROW_1 SRCX(0, 1) ^ SRCX(1, 2) ^ SRCX(2, 3) ^ SRCX(3, 1)
#define MIX_SOLVE_ROW_2 SRCX(0, 1) ^ SRCX(1, 1) ^ SRCX(2, 2) ^ SRCX(3, 3)
#define MIX_SOLVE_ROW_3 SRCX(0, 3) ^ SRCX(1, 1) ^ SRCX(2, 1) ^ SRCX(3, 2)

#define INV_MIX_SOLVE_ROW_0 SRCX(0, E) ^ SRCX(1, B) ^ SRCX(2, D) ^ SRCX(3, 9)
#define INV_MIX_SOLVE_ROW_1 SRCX(0, 9) ^ SRCX(1, E) ^ SRCX(2, B) ^ SRCX(3, D)
#define INV_MIX_SOLVE_ROW_2 SRCX(0, D) ^ SRCX(1, 9) ^ SRCX(2, E) ^ SRCX(3, B)
#define INV_MIX_SOLVE_ROW_3 SRCX(0, B) ^ SRCX(1, D) ^ SRCX(2, 9) ^ SRCX(3, E)

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
