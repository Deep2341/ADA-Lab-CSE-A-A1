#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n_values[] = {1000, 5000, 10000, 20000, 30000};
    int len = sizeof(n_values) / sizeof(n_values[0]);
    srand(time(NULL));

    printf("n\tTime (seconds)\n");
    for (int i = 0; i < len; i++) {
        int n = n_values[i];
        int *arr = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr[j] = rand() % 100000;

        clock_t start = clock();
        quickSort(arr, 0, n - 1);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, time_taken);
        free(arr);
    }
    return 0;
}
