//
// Created by Ivano on 18/08/2018.
//

#ifndef AES_ARITHMETICS_H
#define AES_ARITHMETICS_H

#include <cstdint>

#define MUL_POLYNOMIAL 0x11B


static const uint8_t ROTATION_WORD[] = {0x00, 0x00, 0x00, 0x01};

inline uint8_t XTIME(uint8_t n1) {
    return (uint8_t) (((n1 << 0x1) & 0x100) ? (n1 << 0x1) ^ MUL_POLYNOMIAL : n1 << 0x1);
}

inline uint8_t BIT_SUM(uint8_t n1, uint8_t n2) {
    return n1 ^ n2;
}

inline uint8_t BIT_MUL(uint8_t n1, uint8_t n2) {
    uint8_t pow = 1;
    uint8_t times = n2;
    uint8_t res = 0;

    // Get n2 as a polynomial composed of sums of powers of two.
    // To do so loop through all of times bits and get every bit that is equal to 1

    while (times != 0) {
        if ((times & 0x1)) {
            uint8_t intermediate = n1;
            for (uint8_t a = 0x1; a < pow; a <<= 0x1) {
                intermediate = XTIME(intermediate);
            }
            res = BIT_SUM(res, intermediate);
        }
        pow <<= 0x1;
        times >>= 0x1;
    }
    return res;
}

inline void WORD_SUM(uint8_t *w1, uint8_t *w2, uint8_t *res) { for (uint8_t a = 0; a < 4; a++) res[a] = w1[a] ^ w2[a]; }

inline void WORD_MUL(const uint8_t *w1,const uint8_t *w2, uint8_t *res) {
    res[0] = BIT_MUL(w1[0], w2[0]) ^ BIT_MUL(w1[3], w2[1]) ^ BIT_MUL(w1[2], w2[2]) ^ BIT_MUL(w1[1], w2[3]);
    res[1] = BIT_MUL(w1[1], w2[0]) ^ BIT_MUL(w1[0], w2[1]) ^ BIT_MUL(w1[3], w2[2]) ^ BIT_MUL(w1[2], w2[3]);
    res[2] = BIT_MUL(w1[2], w2[0]) ^ BIT_MUL(w1[1], w2[1]) ^ BIT_MUL(w1[0], w2[2]) ^ BIT_MUL(w1[3], w2[3]);
    res[3] = BIT_MUL(w1[3], w2[0]) ^ BIT_MUL(w1[2], w2[1]) ^ BIT_MUL(w1[1], w2[2]) ^ BIT_MUL(w1[0], w2[3]);
}


inline void ROTATE_WORD(const uint8_t* word, uint8_t* res){
    WORD_MUL(word, ROTATION_WORD, res);
}


#endif //AES_ARITHMETICS_H
