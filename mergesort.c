#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
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
        mergeSort(arr, 0, n - 1);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, time_taken);
        free(arr);
    }
    return 0;
}
