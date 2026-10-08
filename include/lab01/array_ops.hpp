#pragma once

#include <cstddef>

namespace lab01 {

int* ArrayCreate(std::size_t size);
void ArrayDelete(int*& array);

int* ArrayResize(int* array, std::size_t size, std::size_t new_size);
int* ArrayInsert(int* array, std::size_t& size, std::size_t position, int value);
int* ArrayRemove(int* array, std::size_t& size, std::size_t position);

void ArrayPrint(const int* array, std::size_t size);
void InsertionSort(int* array, std::size_t size);
void ArrayRotateLeft(int* array, std::size_t size, std::size_t shift);
bool ArrayBinarySearch(
    const int* array,
    std::size_t size,
    int target,
    std::size_t& out_index);

}  // namespace lab01
