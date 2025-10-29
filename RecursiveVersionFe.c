#include <stdio.h>
#include <time.h>

long long fib_recursive(int n) {
    if (n <= 1)
        return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main() {
    int n;
    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();
    long long result = fib_recursive(n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", time_taken);
    return 0;
}
