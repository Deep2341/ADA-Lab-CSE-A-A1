#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n, key, pos;
    FILE *fp;
    fp = fopen("binary_search_time.csv", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "n,Time(seconds)\n");

    srand(time(NULL));

    // Repeat for increasing values of n
    for (n = 1000; n <= 100000; n += 5000) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Generate random sorted array
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (n * 10);

        qsort(arr, n, sizeof(int), compare); // Sort before binary search

        key = arr[n - 1]; // Worst case: last element

        clock_t start = clock();
        pos = binarySearch(arr, n, key);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        fprintf(fp, "%d,%f\n", n, time_taken);

        printf("n = %d\tTime = %f sec\n", n, time_taken);
        free(arr);
    }

    fclose(fp);
    printf("\nResults saved to 'binary_search_time.csv'\n");
    printf("You can plot Time (Y-axis) vs n (X-axis) using Excel or Python.\n");

    return 0;
}
