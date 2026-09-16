#include "Benchmark.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstdio>

static void insertionSortInt(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }
}

static void bubbleSortInt(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool huboIntercambio = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                huboIntercambio = true;
            }
        }
        if (!huboIntercambio) break;
    }
}

static void mezclarInt(int arr[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;
    int* izq = new int[n1];
    int* der = new int[n2];

    for (int i = 0; i < n1; i++) izq[i] = arr[inicio + i];
    for (int j = 0; j < n2; j++) der[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (izq[i] <= der[j]) arr[k++] = izq[i++];
        else arr[k++] = der[j++];
    }
    while (i < n1) arr[k++] = izq[i++];
    while (j < n2) arr[k++] = der[j++];

    delete[] izq;
    delete[] der;
}

static void mergeSortInt(int arr[], int inicio, int fin) {
    if (inicio >= fin) return;
    int medio = (inicio + fin) / 2;
    mergeSortInt(arr, inicio, medio);
    mergeSortInt(arr, medio + 1, fin);
    mezclarInt(arr, inicio, medio, fin);
}

void ejecutarBenchmark() {
    int tamanios[4] = { 10, 100, 1000, 10000 };
    srand(static_cast<unsigned int>(time(nullptr)));

    printf("\n=== BENCHMARK DE ORDENAMIENTO ===\n");
    printf("%-10s %-15s %-15s %-15s\n", "n", "Insercion(ms)", "Burbuja(ms)", "Merge(ms)");

    for (int t = 0; t < 4; t++) {
        int n = tamanios[t];

        int* original = new int[n];
        for (int i = 0; i < n; i++) original[i] = rand() % 100000;

        int* copia1 = new int[n];
        int* copia2 = new int[n];
        int* copia3 = new int[n];
        for (int i = 0; i < n; i++) {
            copia1[i] = original[i];
            copia2[i] = original[i];
            copia3[i] = original[i];
        }

        auto t1inicio = std::chrono::high_resolution_clock::now();
        insertionSortInt(copia1, n);
        auto t1fin = std::chrono::high_resolution_clock::now();
        double msInsercion = std::chrono::duration<double, std::milli>(t1fin - t1inicio).count();

        auto t2inicio = std::chrono::high_resolution_clock::now();
        bubbleSortInt(copia2, n);
        auto t2fin = std::chrono::high_resolution_clock::now();
        double msBurbuja = std::chrono::duration<double, std::milli>(t2fin - t2inicio).count();

        auto t3inicio = std::chrono::high_resolution_clock::now();
        mergeSortInt(copia3, 0, n - 1);
        auto t3fin = std::chrono::high_resolution_clock::now();
        double msMerge = std::chrono::duration<double, std::milli>(t3fin - t3inicio).count();

        printf("%-10d %-15.4f %-15.4f %-15.4f\n", n, msInsercion, msBurbuja, msMerge);

        delete[] original;
        delete[] copia1;
        delete[] copia2;
        delete[] copia3;
    }

    printf("=================================\n\n");
}