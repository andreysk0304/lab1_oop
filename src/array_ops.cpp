#include "lab01/array_ops.hpp"

#include <algorithm>
#include <iostream>

namespace lab01 {

int* ArrayCreate(const std::size_t size) {
    if (size == 0) {
        return nullptr;
    }
    return new int[size];
}

void ArrayDelete(int*& array) {
    delete[] array;
    array = nullptr;
}

int* ArrayResize(int* array, const std::size_t size, const std::size_t new_size) {
    if (new_size == 0) {
        delete[] array;
        return nullptr;
    }

    int* new_array = new int[new_size]{};
    const std::size_t copy_size = std::min(size, new_size);
    if (copy_size > 0) {
        std::copy_n(array, copy_size, new_array);
    }
    delete[] array;
    return new_array;
}

int* ArrayInsert(int* array, std::size_t& size, const std::size_t position, const int value) {
    if (position > size) {
        return array;
    }

    int* new_array = new int[size + 1];
    for (std::size_t i = 0; i < position; ++i) {
        new_array[i] = array[i];
    }
    new_array[position] = value;
    for (std::size_t i = position; i < size; ++i) {
        new_array[i + 1] = array[i];
    }
    ++size;
    delete[] array;
    return new_array;
}

int* ArrayRemove(int* array, std::size_t& size, const std::size_t position) {
    if (position >= size) {
        return array;
    }

    int* new_array = size == 1 ? nullptr : new int[size - 1];
    for (std::size_t i = 0; i < position; ++i) {
        new_array[i] = array[i];
    }
    for (std::size_t i = position + 1; i < size; ++i) {
        new_array[i - 1] = array[i];
    }
    delete[] array;
    --size;
    return new_array;
}

void ArrayPrint(const int* array, const std::size_t size) {
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }
}

void InsertionSort(int* array, const std::size_t size) {
    for (std::size_t i = 1; i < size; ++i) {
        const int value = array[i];
        std::size_t position = i;
        while (position > 0 && array[position - 1] > value) {
            array[position] = array[position - 1];
            --position;
        }
        array[position] = value;
    }
}

void ArrayRotateLeft(int* array, const std::size_t size, std::size_t shift) {
    if (size == 0) {
        return;
    }

    shift %= size;
    std::rotate(array, array + shift, array + size);
}

bool ArrayBinarySearch(
    const int* array,
    const std::size_t size,
    const int target,
    std::size_t& out_index) {
    std::size_t left{};
    std::size_t right = size;

    while (left < right) {
        const std::size_t middle = left + (right - left) / 2;
        if (array[middle] == target) {
            out_index = middle;
            return true;
        }
        if (array[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return false;
}

}  // namespace lab01
