//
// Created by Ivano on 14/08/2018.
//

#ifndef AES_STATE_H
#define AES_STATE_H

#include <cstdint>

#define STATE_DIM 4*4
#define ROWS 4
#define COLUMNS 4

class State{
private:
    uint8_t stateArray[STATE_DIM];
public:
    State(uint8_t* array);
    uint8_t getElement(uint8_t index) const;
    uint8_t getCell(uint8_t row, uint8_t column) const;
};

#endif //AES_STATE_H
