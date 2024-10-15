#include "gtest/gtest.h"
#include "array.h"

TEST(ArrayTest, ConstructorWithSize) {
    Array<int> arr(5);
    EXPECT_EQ(arr.getSize(), 5);
    for (int i = 0; i < arr.getSize(); ++i) {
        EXPECT_EQ(arr[i], 0); 
    }
}


TEST(ArrayTest, CopyConstructor) {
    Array<int> original(3);
    original.insert(0, 10);
    original.insert(1, 20);
    original.insert(2, 30);

    Array<int> copy(original);
    EXPECT_EQ(copy.getSize(), original.getSize());
    for (int i = 0; i < copy.getSize(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
}


TEST(ArrayTest, MoveConstructor) {
    Array<int> moved(Array<int>(3, 9));
    EXPECT_EQ(moved.getSize(), 3);

    for (int i = 0; i < moved.getSize(); ++i)
        EXPECT_EQ(moved[i], 9);
}


TEST(ArrayTest, Insert) {
    Array<int> arr(3);
    arr.insert(0, 10);
    arr.insert(1, 20);
    arr.insert(2, 30);

    EXPECT_EQ(arr.getSize(), 6); 
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}


TEST(ArrayTest, RemoveByIndex) {
    Array<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    ASSERT_TRUE(arr.removeByIndex(1));
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);  
}


TEST(ArrayTest, RemoveByValue) {
    Array<int> arr(4);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 20;
    arr[3] = 30;

    ASSERT_TRUE(arr.removeByValue(20));
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}


TEST(ArrayTest, RemoveAllByValue) {
    Array<int> arr(4);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 20;
    arr[3] = 30;

    ASSERT_TRUE(arr.removeAllByValue(20));
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}


TEST(ArrayTest, FindMaxMinNumber) {
    Array<int> arr(3);
    arr.insert(0, -10);
    arr.insert(1, 50);
    arr.insert(2, 30);

    EXPECT_EQ(arr.findMaxNumber(), 50);
    EXPECT_EQ(arr.findMinNumber(), -10);
}
