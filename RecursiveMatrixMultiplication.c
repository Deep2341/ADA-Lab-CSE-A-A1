#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

void multiplyRecursive(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 1)
        C[0][0] = A[0][0] * B[0][0];
    else {
        int mid = n / 2;
        int i, j;

        int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
        int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
        int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
        int temp1[MAX][MAX], temp2[MAX][MAX];

        for (i = 0; i < mid; i++)
            for (j = 0; j < mid; j++) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + mid];
                A21[i][j] = A[i + mid][j];
                A22[i][j] = A[i + mid][j + mid];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + mid];
                B21[i][j] = B[i + mid][j];
                B22[i][j] = B[i + mid][j + mid];
            }

        // C11 = A11*B11 + A12*B21
        multiplyRecursive(mid, A11, B11, temp1);
        multiplyRecursive(mid, A12, B21, temp2);
        for (i = 0; i < mid; i++)
            for (j = 0; j < mid; j++)
                C11[i][j] = temp1[i][j] + temp2[i][j];

        // C12 = A11*B12 + A12*B22
        multiplyRecursive(mid, A11, B12, temp1);
        multiplyRecursive(mid, A12, B22, temp2);
        for (i = 0; i < mid; i++)
            for (j = 0; j < mid; j++)
                C12[i][j] = temp1[i][j] + temp2[i][j];

        // C21 = A21*B11 + A22*B21
        multiplyRecursive(mid, A21, B11, temp1);
        multiplyRecursive(mid, A22, B21, temp2);
        for (i = 0; i < mid; i++)
            for (j = 0; j < mid; j++)
                C21[i][j] = temp1[i][j] + temp2[i][j];

        // C22 = A21*B12 + A22*B22
        multiplyRecursive(mid, A21, B12, temp1);
        multiplyRecursive(mid, A22, B22, temp2);
        for (i = 0; i < mid; i++)
            for (j = 0; j < mid; j++)
                C22[i][j] = temp1[i][j] + temp2[i][j];

        // Combine into C
        for (i = 0; i < mid; i++)
            for (j = 0; j < mid; j++) {
                C[i][j] = C11[i][j];
                C[i][j + mid] = C12[i][j];
                C[i + mid][j] = C21[i][j];
                C[i + mid][j + mid] = C22[i][j];
            }
    }
}

int main() {
    int n;
    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    srand(time(0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    clock_t start = clock();
    multiplyRecursive(n, A, B, C);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Recursive Multiplication Time: %f seconds\n", time_taken);

    return 0;
}
