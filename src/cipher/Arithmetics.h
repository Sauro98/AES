//
// Created by Ivano on 18/08/2018.
//

#ifndef AES_ARITHMETICS_H
#define AES_ARITHMETICS_H

#include <cstdint>


#define ROWS 4
#define COLUMNS 4

#define STATE_AT(x, y) ((x) + (y)*COLUMNS )

#define MUL_POLYNOMIAL 0x11B
#define BYTES_IN_WORD 4U
#define STATE_DIM (16)
#define BIT_SUM(n1, n2) (n1 ^ n2)

#define OVERFLOW_IF_SHIFT(val) ((val) >= 0x80)

#define BIT_MUL_02 XTIME

inline uint8_t XTIME(uint8_t val){
    uint8_t toReturn = val;
    toReturn <<= 1;
    if(OVERFLOW_IF_SHIFT(val))
        toReturn ^= MUL_POLYNOMIAL;
    return toReturn;
}

inline uint8_t BIT_MUL_03(uint8_t val, uint8_t xtimeVal){
    return xtimeVal^val;
}

inline uint8_t BIT_MUL_09(uint8_t val, uint8_t xtime3Val){
    return XTIME(xtime3Val) ^ val;
}

inline uint8_t BIT_MUL_0B(uint8_t xtimeVal, uint8_t bitMul09){
    return bitMul09 ^ xtimeVal;
}

inline uint8_t BIT_MUL_0D(uint8_t xtime3Val, uint8_t bitMul09){
    return xtime3Val^bitMul09;
}
inline uint8_t BIT_MUL_0E(uint8_t val, uint8_t xTimeVal, uint8_t bitMul0D){
    return bitMul0D ^ xTimeVal ^ val;
}

inline uint8_t BIT_MUL(const uint8_t n1, const uint8_t n2) {
    uint8_t res = 0;
    uint8_t times = n2;
    uint8_t xTimeValue = n1;
    // Get n2 as a polynomial composed of sums of powers of two.
    // To do so loop through all of times bits and get every bit that is equal to 1
    while (times > 0) {
        if (times & 1) res ^= xTimeValue;
        xTimeValue =  XTIME(xTimeValue);
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


#endif //AES_ARITHMETICS_H
