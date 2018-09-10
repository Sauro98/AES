//
// Created by Ivano on 15/08/2018.
//

#include <gtest/gtest.h>
#include "../src/cipher/SBox.h"

TEST(SBOX, subByte) {
    uint8_t v1 = 0x53;
    EXPECT_EQ(SUB_BYTE(v1), 0xED);
    v1 = 0x35;
    EXPECT_EQ(SUB_BYTE(v1), 0x96);
}

TEST(SBOX, subWord) {
    uint8_t word[] = {0xa1, 0x3c, 0x4f, 0x12};
    SUB_WORD(word);
    EXPECT_EQ(word[0], 0x32);
    EXPECT_EQ(word[1], 0xeb);
    EXPECT_EQ(word[2], 0x84);
    EXPECT_EQ(word[3], 0xc9);
}

TEST(SBOX, rotateWord) {
    uint8_t orig[] = {0x04, 0x01, 0x02, 0x03};
    AESArithmetics::ROTATE_WORD(orig);
    EXPECT_EQ(orig[0], 0x01);
    EXPECT_EQ(orig[1], 0x02);
    EXPECT_EQ(orig[2], 0x03);
    EXPECT_EQ(orig[3], 0x04);
}