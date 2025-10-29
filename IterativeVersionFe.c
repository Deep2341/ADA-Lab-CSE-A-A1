#include <stdio.h>
#include <time.h>

long long fib_iterative(int n) {
    if (n <= 1)
        return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();
    long long result = fib_iterative(n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", time_taken);
    return 0;
}
