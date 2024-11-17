#include <gtest/gtest.h>
#include "boolvector.h"

TEST(BoolVectorTest, ConstructorWithLength) {
    BoolVector bv(10);
    EXPECT_EQ(bv.weight(), 0);
}

TEST(BoolVectorTest, ConstructorWithLengthAndValue) {
    BoolVector bv(10, true);
    EXPECT_EQ(bv.weight(), 10);

    BoolVector bv2(10, false);
    EXPECT_EQ(bv2.weight(), 0);
}

TEST(BoolVectorTest, ConstructorFromString) {
    BoolVector bv("10101");
    EXPECT_EQ(bv.weight(), 3);
    EXPECT_TRUE(bv.bitValue(0));
    EXPECT_FALSE(bv.bitValue(1));
    EXPECT_TRUE(bv.bitValue(2));
}

TEST(BoolVectorTest, CopyConstructor) {
    BoolVector bv1(10, true);
    BoolVector bv2(bv1);
    EXPECT_EQ(bv2.weight(), 10);
}
