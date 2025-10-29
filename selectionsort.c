#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min]) min = j;
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int n_values[] = {1000, 5000, 10000};
    int len = sizeof(n_values) / sizeof(n_values[0]);
    srand(time(NULL));

    printf("n\tTime (seconds)\n");
    for (int i = 0; i < len; i++) {
        int n = n_values[i];
        int *arr = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr[j] = rand() % 100000;

        clock_t start = clock();
        selectionSort(arr, n);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%d\t%f\n", n, time_taken);
        free(arr);
    }
    return 0;
}
