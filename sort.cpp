#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Генератор случайных чисел
class Random {
public:
    Random() : gen(std::random_device()()) {}

    int operator() (int min, int max) {
        return std::uniform_int_distribution<>(min, max)(gen);
    }

private:
    std::mt19937 gen;
};

// Генерация случайных чисел
void generateRandomNumbers(std::vector<int>& vec, int size) {
    Random rand;
    for (int i = 0; i < size; ++i) {
        vec.push_back(rand(0, 10000));
    }
}

// Сортировка пузырьком
void bubbleSort(std::vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (vec[j] > vec[j+1]) {
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
}

// Быстрая сортировка
void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int pivot = vec[high];
        int i = low - 1;
        for (int j = low; j <= high-1; ++j) {
            if (vec[j] < pivot) {
                ++i;
                std::swap(vec[i], vec[j]);
            }
        }
        std::swap(vec[i + 1], vec[high]);
        int pi = i + 1;
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main() {
    const int size = 10000;
    std::vector<int> numbers;

    // Генерируем случайные числа
    generateRandomNumbers(numbers, size);

    // Копируем массив для каждого типа сортировки
    std::vector<int> numbers_bubble = numbers;
    std::vector<int> numbers_quick = numbers;

    // Запускаем сортировку пузырьком и замеряем время
    auto start_bubble = std::chrono::steady_clock::now();
    bubbleSort(numbers_bubble);
    auto end_bubble = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_bubble = end_bubble - start_bubble;

    // Запускаем быструю сортировку и замеряем время
    auto start_quick = std::chrono::steady_clock::now();
    quickSort(numbers_quick, 0, size - 1);
    auto end_quick = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_quick = end_quick - start_quick;

    // Выводим время и название наиболее быстрой сортировки
    if (elapsed_bubble < elapsed_quick) {
        std::cout << "Время сортировки пузырьком: " << elapsed_bubble.count() << " секунд" << std::endl;
        std::cout << "Пузырьковая сортировка быстрее" << std::endl;
    } else {
        std::cout << "Время быстрой сортировки: " << elapsed_quick.count() << " секунд" << std::endl;
        std::cout << "Быстрая сортировка быстрее" << std::endl;
    }

    return 0;
}
