//
// Created by Ivano on 14/08/2018.
//

#include <gtest/gtest.h>
#include "../../src/State.h"

TEST(State, constructor) {
    uint8_t orig[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8_t exp[] = {0, 4, 8, 12,
                     1, 5, 9, 13,
                     2, 6, 10, 14,
                     3, 7, 11, 15};
    State state(orig);
    for (uint8_t a = 0; a < STATE_DIM; a++)
        EXPECT_EQ(state.getElement(a), exp[a]);
}
