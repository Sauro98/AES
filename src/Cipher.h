//
// Created by Ivano on 15/08/2018.
//

#ifndef AES_CIPHER_H
#define AES_CIPHER_H

#include <cstdint>
#include <iostream>
#include "State.h"

#endif //AES_CIPHER_H

class Cipher{
    State s;
public:
    Cipher(uint8_t* input, const std::string& key) : s(input, key){
    }

    void crypt(){
        s.addRoundKey();
        for(uint8_t round = 1; round < s.key.rounds -1; round++){
            s.subBytes();
            s.shiftRows();
            s.mixColumns();
            s.addRoundKey();
        }
        s.subBytes();
        s.shiftRows();
        s.addRoundKey();
    }

    void printState(){
        std::string encr;
        for(uint8_t a = 0; a < 16; a++){
            std::cout<<std::hex<<(uint16_t)s.getElement(a)<<" ";
            encr += s.getElement(a);
        }
        std::cout<<std::endl;

        std::cout<<encr<<std::endl;
    }
};
