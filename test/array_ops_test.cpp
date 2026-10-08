#include "lab01/array_ops.hpp"

#include <gtest/gtest.h>

namespace lab01 {
namespace {

void ExpectArrayEquals(const int* actual, const int* expected, const std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(actual[i], expected[i]) << "index " << i;
    }
}

TEST(ArrayTest, CreateResizeAndRelease) {
    int* values = ArrayCreate(2);
    ASSERT_NE(values, nullptr);
    values[0] = 4;
    values[1] = 8;

    values = ArrayResize(values, 2, 3);
    ASSERT_NE(values, nullptr);
    const int expected[] = {4, 8, 0};
    ExpectArrayEquals(values, expected, 2);

    ArrayDelete(values);
    EXPECT_EQ(values, nullptr);
    EXPECT_EQ(ArrayCreate(0), nullptr);
}

TEST(ArrayTest, InsertAndRemoveKeepElementsInOrder) {
    std::size_t size = 3;
    int* values = ArrayCreate(size);
    ASSERT_NE(values, nullptr);
    values[0] = 1;
    values[1] = 3;
    values[2] = 4;

    values = ArrayInsert(values, size, 1, 2);
    ASSERT_EQ(size, 4U);
    const int after_insert[] = {1, 2, 3, 4};
    ExpectArrayEquals(values, after_insert, size);

    values = ArrayRemove(values, size, 2);
    ASSERT_EQ(size, 3U);
    const int after_remove[] = {1, 2, 4};
    ExpectArrayEquals(values, after_remove, size);
    ArrayDelete(values);
}

TEST(ArrayTest_Fail, InvalidPositionsLeaveArrayUntouched) {
    std::size_t size = 2;
    int* values = ArrayCreate(size);
    ASSERT_NE(values, nullptr);
    values[0] = 5;
    values[1] = 6;

    EXPECT_EQ(ArrayInsert(values, size, 3, 7), values);
    EXPECT_EQ(ArrayRemove(values, size, size), values);
    EXPECT_EQ(size, 2U);
    const int expected[] = {5, 6};
    ExpectArrayEquals(values, expected, size);
    ArrayDelete(values);
}

TEST(ArrayTest, SortAndRotate) {
    int* values = ArrayCreate(5);
    ASSERT_NE(values, nullptr);
    const int input[] = {4, 2, 5, 1, 3};
    for (std::size_t i = 0; i < 5; ++i) {
        values[i] = input[i];
    }

    InsertionSort(values, 5);
    const int sorted[] = {1, 2, 3, 4, 5};
    ExpectArrayEquals(values, sorted, 5);

    ArrayRotateLeft(values, 5, 7);
    const int rotated[] = {3, 4, 5, 1, 2};
    ExpectArrayEquals(values, rotated, 5);
    ArrayDelete(values);
}

TEST(ArraySearchTest, FindsValueAndItsPosition) {
    const int values[] = {1, 2, 3, 4, 5};
    std::size_t index{};

    ASSERT_TRUE(ArrayBinarySearch(values, 5, 4, index));
    EXPECT_EQ(index, 3U);
}

TEST(ArraySearchTest_Fail, MissingValueReturnsFalse) {
    const int values[] = {1, 2, 3, 4, 5};
    std::size_t index = 123;

    EXPECT_FALSE(ArrayBinarySearch(values, 5, 7, index));
    EXPECT_EQ(index, 123U);
    EXPECT_FALSE(ArrayBinarySearch(nullptr, 0, 7, index));
}

}  // namespace
}  // namespace lab01
