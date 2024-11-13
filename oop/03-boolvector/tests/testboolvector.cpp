#include <gtest/gtest.h>
#include "boolvector.h"

TEST(BoolVectorTest, ConstructorWithLengthAndValueTrue) {
    BoolVector bv(10, true);
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(bv.bitValue(i));
    }
}
