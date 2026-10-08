#include "lab01/array_ops.hpp"

#include <cstddef>
#include <iostream>
#include <limits>

namespace {

bool ReadInt(int& x) {
    if (std::cin >> x) {
        return true;
    }
    std::cerr << "Ошибка ввода\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}

void PrintMenu() {
    constexpr const char* commands_text =
        "1. Создать массив\t\t 2. Напечатать элемент ( найти бинарным поиском )\n"
        "3. Вставить элемент\t\t 4. Удалить элемент\n"
        "5. Изменить размер\t\t 6. Печать\n"
        "7. Сортировка вставками и сдвиг\n"
        "0. Выход";

    std::cout << commands_text << '\n';
}

} //

int main() {
    int* array{nullptr};
    std::size_t array_size{0};

    while (true) {
        PrintMenu();
        int command{};

        std::cout << "> ";

        if (!ReadInt(command)) {
            continue;
        }

        switch (command) {
            case 1: {
                int size_input{};
                std::cout << "введите размер массива: ";

                if (!ReadInt(size_input) || size_input < 0) {
                    std::cerr << "размер должен быть неотрицательным целым числом\n";
                    break;
                }

                lab01::ArrayDelete(array);
                array_size = static_cast<std::size_t>(size_input);
                array = lab01::ArrayCreate(array_size);

                for (std::size_t i = 0; i < array_size; ++i) {
                    std::cout << "Введите элемент [" << i << "]: ";
                    if (!ReadInt(array[i])) {
                        array[i] = 0;
                        std::cerr << "Установлено значение 0.\n";
                    }
                }

                std::cout << "Массив создан, размер: " << array_size << "\n";
                break;
            }

            case 2: {
                std::size_t index{};
                int target;
                std::cout << "Введи искомое значение: ";
                if (!ReadInt(target)) {
                    break;
                }

                lab01::InsertionSort(array, array_size);
                if (!lab01::ArrayBinarySearch(array, array_size, target, index)) {
                    std::cout << "Элемент не найден\n";
                    break;
                }
                std::cout << "Элемент найден на позиции " << index << "\n";
                break;
            }

            case 3: {
                int value{};
                int position_input{};
                std::cout << "Введи вставляемое значение: ";
                if (!ReadInt(value)) {
                    break;
                }
                std::cout << "Введи позицию вставки: ";
                if (!ReadInt(position_input)) {
                    break;
                }
                if (position_input < 0 || static_cast<std::size_t>(position_input) > array_size)
                {
                    std::cerr << "Позиция должна быть от 0 до " << array_size << "\n";
                    break;
                }

                const std::size_t pos = static_cast<std::size_t>(position_input);
                array = lab01::ArrayInsert(array, array_size, pos, value);
                std::cout << "Элемент " << value
                          << " успешно вставлен на позицию " << pos << "\n";
                break;
            }

            case 4: {
                int element{};
                std::cout << "Введи удаляемый элемент: ";
                if (!ReadInt(element)) {
                    break;
                }
                std::size_t index{};
                lab01::InsertionSort(array, array_size);
                if (!lab01::ArrayBinarySearch(array, array_size, element, index)) {
                    std::cout << "Элемент не найден\n";
                    break;
                }

                array = lab01::ArrayRemove(array, array_size, index);
                std::cout << "Элемент " << element << " успешно удалён\n";
                break;
            }

            case 5: {
                int new_size_int{};
                std::cout << "Введи новый размер: ";
                if (!ReadInt(new_size_int) || new_size_int < 0) {
                    std::cerr << "Размер должен быть неотрицательным целым числом.\n";
                    break;
                }

                const std::size_t old_size = array_size;
                const std::size_t new_size = static_cast<std::size_t>(new_size_int);
                array = lab01::ArrayResize(array, old_size, new_size);
                array_size = new_size;
                std::cout << "Размер успешно изменён на " << new_size << "\n";
                break;
            }

            case 6: {
                lab01::ArrayPrint(array, array_size);
                std::cout << '\n';
                break;
            }

            case 7: {
                int k_input{};
                lab01::InsertionSort(array, array_size);
                std::cout << "Массив отсортирован: ";
                lab01::ArrayPrint(array, array_size);
                std::cout << '\n';

                std::cout << "Введи величину сдвига k: ";
                if (!ReadInt(k_input) || k_input < 0) {
                    std::cerr << "k должен быть неотрицательным целым числом.\n";
                    break;
                }

                lab01::ArrayRotateLeft(
                    array,
                    array_size,
                    static_cast<std::size_t>(k_input)
                );
                std::cout << "Массив после сдвига: ";
                lab01::ArrayPrint(array, array_size);
                std::cout << '\n';
                break;
            }

            case 0:
                lab01::ArrayDelete(array);
                return 0;

            default:
                std::cerr << "неизвестная команда\n";
                break;
        }
    }
}
// 67