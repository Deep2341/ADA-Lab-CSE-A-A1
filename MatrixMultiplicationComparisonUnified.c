#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX 512  // you can increase for larger tests (e.g., 1024)

// Utility functions for matrix operations
void addMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// ==================== (1) ITERATIVE METHOD ====================
void multiplyIterative(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// ==================== (2) RECURSIVE METHOD ====================
void multiplyRecursive(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];

    // Divide matrices
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++) {
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
    multiplyRecursive(mid, A11, B11, T1);
    multiplyRecursive(mid, A12, B21, T2);
    addMatrix(mid, T1, T2, C11);

    // C12 = A11*B12 + A12*B22
    multiplyRecursive(mid, A11, B12, T1);
    multiplyRecursive(mid, A12, B22, T2);
    addMatrix(mid, T1, T2, C12);

    // C21 = A21*B11 + A22*B21
    multiplyRecursive(mid, A21, B11, T1);
    multiplyRecursive(mid, A22, B21, T2);
    addMatrix(mid, T1, T2, C21);

    // C22 = A21*B12 + A22*B22
    multiplyRecursive(mid, A21, B12, T1);
    multiplyRecursive(mid, A22, B22, T2);
    addMatrix(mid, T1, T2, C22);

    // Combine results
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
}

// ==================== (3) STRASSEN’S METHOD ====================
void strassen(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX];
    int M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];

    // Divide matrices
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }

    // M1 = (A11 + A22)*(B11 + B22)
    addMatrix(mid, A11, A22, T1);
    addMatrix(mid, B11, B22, T2);
    strassen(mid, T1, T2, M1);

    // M2 = (A21 + A22)*B11
    addMatrix(mid, A21, A22, T1);
    strassen(mid, T1, B11, M2);

    // M3 = A11*(B12 - B22)
    subMatrix(mid, B12, B22, T2);
    strassen(mid, A11, T2, M3);

    // M4 = A22*(B21 - B11)
    subMatrix(mid, B21, B11, T2);
    strassen(mid, A22, T2, M4);

    // M5 = (A11 + A12)*B22
    addMatrix(mid, A11, A12, T1);
    strassen(mid, T1, B22, M5);

    // M6 = (A21 - A11)*(B11 + B12)
    subMatrix(mid, A21, A11, T1);
    addMatrix(mid, B11, B12, T2);
    strassen(mid, T1, T2, M6);

    // M7 = (A12 - A22)*(B21 + B22)
    subMatrix(mid, A12, A22, T1);
    addMatrix(mid, B21, B22, T2);
    strassen(mid, T1, T2, M7);

    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];

    // Compute final submatrices
    addMatrix(mid, M1, M4, T1);
    subMatrix(mid, T1, M5, T2);
    addMatrix(mid, T2, M7, C11);

    addMatrix(mid, M3, M5, C12);
    addMatrix(mid, M2, M4, C21);

    subMatrix(mid, M1, M2, T1);
    addMatrix(mid, T1, M3, T2);
    addMatrix(mid, T2, M6, C22);

    // Combine results
    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
}

// ==================== MAIN PROGRAM ====================
int main() {
    srand(time(0));

    printf("Matrix Multiplication Comparison\n");
    printf("---------------------------------\n");
    printf("Size\tIterative(s)\tRecursive(s)\tStrassen(s)\n");

    for (int exp = 2; exp <= 8; exp++) { // test 2^2=4 up to 2^8=256
        int n = pow(2, exp);
        int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

        // Generate random matrices
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }

        clock_t start, end;

        // Iterative
        start = clock();
        multiplyIterative(n, A, B, C);
        end = clock();
        double t_iter = (double)(end - start) / CLOCKS_PER_SEC;

        // Recursive
        start = clock();
        multiplyRecursive(n, A, B, C);
        end = clock();
        double t_recur = (double)(end - start) / CLOCKS_PER_SEC;

        // Strassen
        start = clock();
        strassen(n, A, B, C);
        end = clock();
        double t_strassen = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t%.6f\t%.6f\n", n, t_iter, t_recur, t_strassen);
    }

    return 0;
}
