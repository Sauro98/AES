//
// Created by Ivano on 14/08/2018.
//

#include "State.h"

State::State(uint8_t *array) {
    for (uint8_t r = 0; r < ROWS; r++) {
        for (uint8_t c = 0; c < COLUMNS; c++) {
            stateArray[COLUMNS * r + c] = array[r + COLUMNS * c];
        }
    }

}

uint8_t State::getElement(uint8_t index) const {
    if (index >= 0 || index < STATE_DIM)
        return stateArray[index];
    return 255; //TODO:: not elegant
}

uint8_t State::getCell(uint8_t row, uint8_t column) const {
    if(row < ROWS && row >=0 && column < COLUMNS && column >= 0)
        return stateArray[COLUMNS * row + column];
    return 255; //TODO:: not elegant
}


