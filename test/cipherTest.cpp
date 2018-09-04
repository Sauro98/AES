//
// Created by Ivano on 18/08/2018.
//

#include <gtest/gtest.h>
#include "../src/Cipher.h"

static const std::string key128 = "0123456789abcdef";

TEST(Cipher, crypt){
    uint8_t orig[] = "0123456789abcdef";
    Cipher cipher(orig, key128);
    cipher.printState();
}
