#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

int main() {
    int n, key, pos;
    FILE *fp;
    fp = fopen("linear_search_time.csv", "w"); // Output file for graph plotting
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "n,Time(seconds)\n");

    // Test for increasing values of n
    for (n = 1000; n <= 100000; n += 5000) {
        int *arr = (int *)malloc(n * sizeof(int));

        // Generate random numbers
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;

        key = arr[n - 1]; // Worst case (last element)

        clock_t start = clock();
        pos = linearSearch(arr, n, key);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        fprintf(fp, "%d,%f\n", n, time_taken);

        printf("n = %d\tTime = %f sec\n", n, time_taken);
        free(arr);
    }

    fclose(fp);
    printf("\nResults saved to 'linear_search_time.csv'\n");
    printf("You can plot Time (Y-axis) vs n (X-axis) using Excel or Python.\n");
    return 0;
}
