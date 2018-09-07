//
// Created by Ivano on 14/08/2018.
//

#include <gtest/gtest.h>
#include "../src/cipher/State.h"


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

TEST(State, xtime) {
    uint16_t v1 = 0x57;
    v1 = XTIME(v1);
    EXPECT_EQ(v1, 0xAE);
    v1 = XTIME(v1);
    EXPECT_EQ(v1, 0x47);
    v1 = XTIME(v1);
    EXPECT_EQ(v1, 0x8E);
    v1 = XTIME(v1);
    EXPECT_EQ(v1, 0x07);
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

TEST(State, shiftRows) {
    uint8_t orig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    State::shiftRows(orig);
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
        EXPECT_EQ(orig[STATE_AT(a,b)], exp[4*a + b]);
    State::invShiftRows(orig);

    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(orig[STATE_AT(a,b)], expinv[4*a + b]);

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
    State::mixColumns(orig);
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(orig[STATE_AT(a,b)], exp[4*a + b]);
    State::invMixColumns(orig);
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(orig[STATE_AT(a,b)], orig[4*b + a]);

}

TEST(State, subBytes) {
    uint8_t orig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    State::subBytes(orig);
    State::invSubBytes(orig);

    uint8_t exp[] = {0, 4, 8, 12,
                     1, 5, 9, 13,
                     2, 6, 10, 14,
                     3, 7, 11, 15};
    for (uint8_t a = 0; a < 4; a++)
        for(uint8_t b = 0; b < 4; b++)
            EXPECT_EQ(orig[STATE_AT(a,b)], exp[4*a + b]);
}