//
// Created by Ivano on 14/08/2018.
//

#include <gtest/gtest.h>
#include "../src/State.h"

TEST(State, constructor) {
    uint8_t orig[] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t exp[] = {0x32, 0x88, 0x31, 0xe0,
                     0x43, 0x5a, 0x31, 0x37,
                     0xf6, 0x30, 0x98, 0x07,
                     0xa8, 0x8d, 0xa2, 0x34};
    State state(orig);
    for (uint8_t a = 0; a < 4; a++){
        for (uint8_t b = 0; b < 4; b++){
            EXPECT_EQ(state.getCell(a,b), exp[4*a + b]);
        }
    }

}

TEST(State, getCell) {
    uint8_t orig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    State state(orig);
    EXPECT_EQ(state.getCell(0, 0), 0);
    EXPECT_EQ(state.getCell(0, 1), 4);
    EXPECT_EQ(state.getCell(0, 2), 8);
    EXPECT_EQ(state.getCell(0, 3), 12);

    EXPECT_EQ(state.getCell(1, 0), 1);
    EXPECT_EQ(state.getCell(1, 1), 5);
    EXPECT_EQ(state.getCell(1, 2), 9);
    EXPECT_EQ(state.getCell(1, 3), 13);

    EXPECT_EQ(state.getCell(2, 0), 2);
    EXPECT_EQ(state.getCell(2, 1), 6);
    EXPECT_EQ(state.getCell(2, 2), 10);
    EXPECT_EQ(state.getCell(2, 3), 14);

    EXPECT_EQ(state.getCell(3, 0), 3);
    EXPECT_EQ(state.getCell(3, 1), 7);
    EXPECT_EQ(state.getCell(3, 2), 11);
    EXPECT_EQ(state.getCell(3, 3), 15);
}

TEST(State, BIT_SUM) {
    uint8_t v1 = 1;
    uint8_t v2 = 2;
    EXPECT_EQ(BIT_SUM(v1, v2), 3);

    v1 = 1;
    v2 = 3;
    EXPECT_EQ(BIT_SUM(v1, v2), 2);

    v1 = 3;
    v2 = 3;
    EXPECT_EQ(BIT_SUM(v1, v2), 0);
}

TEST(State, BIT_MUL) {
    uint8_t v1 = 0x57;
    uint8_t v2 = XTIME(v1);
    EXPECT_EQ(v2, 0xAE);
    v2 = XTIME(v2);
    EXPECT_EQ(v2, 0x47);
    v2 = XTIME(v2);
    EXPECT_EQ(v2, 0x8E);
    v2 = XTIME(v2);
    EXPECT_EQ(v2, 0x07);

    v1 = 0x57;
    v2 = 0x13;
    EXPECT_EQ(BIT_MUL(v1, v2), 0xFE);

    v1 = 0x57;
    v2 = 0x83;
    EXPECT_EQ(BIT_MUL(v1, v2), 0xC1);
}

TEST(State, WORD_SUM) {
    uint8_t w1[] = {0x1, 0x2, 0x3, 0x4};
    uint8_t w2[] = {0x4, 0x3, 0x3, 0x2};
    uint8_t exp[] = {0x5, 0x1, 0x0, 0x6};
    uint8_t res[4];
    WORD_SUM(w1, w2, res);
    for (uint8_t a = 0; a < 4; a++)
        EXPECT_EQ(res[a], exp[a]);
}

TEST(State, WORD_MUL) {
    uint8_t ax[] = {0x02, 0x01, 0x01, 0x03};
    uint8_t ax1[] = {0x0E, 0x09, 0x0D, 0x0B};
    uint8_t res[4];
    WORD_MUL(ax, ax1, res);
    EXPECT_EQ(res[0], 0x01);
    EXPECT_EQ(res[1], 0x00);
    EXPECT_EQ(res[2], 0x00);
    EXPECT_EQ(res[3], 0x00);

    uint8_t rot[] = {0x00, 0x00, 0x00, 0x01};
    uint8_t arr[] = {0x01, 0x02, 0x03, 0x04};
    WORD_MUL(arr, rot, res);
    EXPECT_EQ(res[0], 0x02);
    EXPECT_EQ(res[1], 0x03);
    EXPECT_EQ(res[2], 0x04);
    EXPECT_EQ(res[3], 0x01);

}

TEST(State, shiftRows) {
    uint8_t orig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    State state(orig);
    state.shiftRows();
    uint8_t exp[] = {0, 4, 8, 12,
                     5, 9, 13, 1,
                     10, 14, 2, 6,
                     15, 3, 7, 11};
    uint8_t expinv[] = {0, 4, 8, 12,
                        1, 5, 9, 13,
                        2, 6, 10, 14,
                        3, 7, 11, 15};
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
        EXPECT_EQ(state.getCell(a,b), exp[4*a + b]);
    state.invShiftRows();

    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(state.getCell(a,b), expinv[4*a + b]);

}

TEST(State, mixColumns) {
    uint8_t orig[] = {0x63, 0x53, 0xe0, 0x8c,
                      0x09, 0x60, 0xe1, 0x04,
                      0xcd, 0x70, 0xb7, 0x51,
                      0xba, 0xca, 0xd0, 0xe7};
    uint8_t exp[] = {0x5f, 0x57, 0xf7, 0x1d,
                     0x72, 0xf5, 0xbe, 0xb9,
                     0x64, 0xbc, 0x3b, 0xf9,
                     0x15, 0x92, 0x29, 0x1a};
    State state(orig);
    state.mixColumns();
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(state.getCell(a,b), exp[4*a + b]);
    state.invMixColumns();
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(state.getCell(a,b), orig[4*b + a]);

}

TEST(State, SUB_BYTES) {
    uint8_t orig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    State state(orig);
    state.subBytes();
    state.invSubBytes();

    uint8_t exp[] = {0, 4, 8, 12,
                     1, 5, 9, 13,
                     2, 6, 10, 14,
                     3, 7, 11, 15};
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(state.getCell(a,b), exp[4*a + b]);
}