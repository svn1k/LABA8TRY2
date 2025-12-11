#include "sort.h"
#include <cstring>
#include <algorithm>

using namespace std;

// ========== ФУНКЦИИ СРАВНЕНИЯ ==========

// 1. По убыванию продолжительности
int compareByDurationDesc(PhoneCall* a, PhoneCall* b) {
    int aSeconds = a->duration.hours * 3600 + a->duration.minutes * 60 + a->duration.seconds;
    int bSeconds = b->duration.hours * 3600 + b->duration.minutes * 60 + b->duration.seconds;
    return bSeconds - aSeconds; // убывание: b - a
}

// 2. По номеру (возрастание), при равных номерах - по стоимости (убывание)
int compareByNumberAndCost(PhoneCall* a, PhoneCall* b) {
    // Сравнение номеров
    int cmp = strcmp(a->number, b->number);
    if (cmp != 0) return cmp; // возрастание номеров

    // Номера равны → сравнение по убыванию стоимости
    if (b->costPerMinute > a->costPerMinute) return 1;
    if (b->costPerMinute < a->costPerMinute) return -1;
    return 0;
}

// ========== ПИРАМИДАЛЬНАЯ СОРТИРОВКА (Heap sort) ==========

void heapify(PhoneCall* array[], int n, int i, int (*compare)(PhoneCall*, PhoneCall*)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(array[left], array[largest]) < 0)
        largest = left;

    if (right < n && compare(array[right], array[largest]) < 0)
        largest = right;

    if (largest != i) {
        swap(array[i], array[largest]);
        heapify(array, n, largest, compare);
    }
}

void heapSort(PhoneCall* array[], int size, int (*compare)(PhoneCall*, PhoneCall*)) {
    // Построение кучи
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i, compare);

    // Извлечение элементов из кучи
    for (int i = size - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heapify(array, i, 0, compare);
    }
}

// ========== БЫСТРАЯ СОРТИРОВКА (Quick sort) ==========

int partition(PhoneCall* array[], int low, int high, int (*compare)(PhoneCall*, PhoneCall*)) {
    PhoneCall* pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(array[j], pivot) < 0) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}

void quickSortRecursive(PhoneCall* array[], int low, int high, int (*compare)(PhoneCall*, PhoneCall*)) {
    if (low < high) {
        int pi = partition(array, low, high, compare);
        quickSortRecursive(array, low, pi - 1, compare);
        quickSortRecursive(array, pi + 1, high, compare);
    }
}

void quickSort(PhoneCall* array[], int size, int (*compare)(PhoneCall*, PhoneCall*)) {
    quickSortRecursive(array, 0, size - 1, compare);
}
