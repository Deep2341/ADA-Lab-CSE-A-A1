#include <stdio.h>
#include <time.h>

long long fib_bottomup(int n) {
    if (n <= 1)
        return n;
    long long dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

int main() {
    int n;
    clock_t start, end;
    double time_taken;

    printf("Enter n: ");
    scanf("%d", &n);

    start = clock();
    long long result = fib_bottomup(n);
    end = clock();

    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Time taken = %f seconds\n", time_taken);
    return 0;
}
