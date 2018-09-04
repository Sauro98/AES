//
// Created by Ivano on 14/08/2018.
//

#ifndef AES_STATE_H
#define AES_STATE_H

#include <cstdint>
#include "Key/AESKey.h"

#include <cstring>
#include <iostream>
#include "SBox.h"

#define STATE_DIM 4*4
#define ROWS 4
#define COLUMNS 4

#define STATE_AT(x, y) ( (x)*COLUMNS + (y))

inline void ARR_SWAP(uint8_t* arr, uint8_t pos1, uint8_t pos2){
    uint8_t tmp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = tmp;
}

class State {
private:
    uint8_t stateArray[STATE_DIM];

public:
    AESKey key;
    State(uint8_t *array, const std::string& _key);

    uint8_t getElement(uint8_t index) const;

    uint8_t getCell(uint8_t row, uint8_t column) const;

    void setCell(uint8_t row, uint8_t columns, uint8_t newValue);
    void printState(){
        for(int a = 0; a < 4; a++)
            for(int b = 0; b<4; b++)
                std::cout<<std::hex<<(uint16_t)stateArray[STATE_AT(a,b)];
        std::cout<<std::endl;
    }

    void shiftRows();
    void invShiftRows();

    void mixColumns();
    void invMixColumns();

    void addRoundKey();

    void subBytes();
    void invSubBytes();
};


#endif //AES_STATE_H
