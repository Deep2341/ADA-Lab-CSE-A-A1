#include <stdio.h>
#include <time.h>

#define MAX 1000
long long dp[MAX];

long long fib_topdown(int n) {
    if (n <= 1)
        return n;
    if (dp[n] != -1)
        return dp[n];
    dp[n] = fib_topdown(n - 1) + fib_topdown(n - 2);
    return dp[n];
}

int main() {
    int n;
    clock_t start, end;
    double time_taken;

    for (int i = 0; i < MAX; i++)
        dp[i] = -1;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();
    long long result = fib_topdown(n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", time_taken);
    return 0;
}
