// Algorithm Fractional_Knapsack(w[], p[], n, W):
// 1. Compute profit/weight ratio for each item: ratio[i] = p[i] / w[i]
// 2. Sort items in descending order of ratio[i]
// 3. Initialize: total_profit = 0, remaining_capacity = W
// 4. For i = 1 to n:
//       if w[i] <= remaining_capacity:
//           total_profit = total_profit + p[i]
//           remaining_capacity = remaining_capacity - w[i]
//       else:
//           total_profit = total_profit + ratio[i] * remaining_capacity
//           break
// 5. Return total_profit
#include <stdio.h>

void fractionalKnapsack(int n, float weight[], float profit[], float capacity) {
    float ratio[20], temp, total = 0, x[20];
    int i, j;

    for (i = 0; i < n; i++)
        ratio[i] = profit[i] / weight[i];

    // Sorting items by ratio
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;

                temp = profit[i];
                profit[i] = profit[j];
                profit[j] = temp;
            }
        }
    }

    float remaining = capacity;
    for (i = 0; i < n; i++)
        x[i] = 0.0;

    for (i = 0; i < n; i++) {
        if (weight[i] > remaining)
            break;
        else {
            x[i] = 1.0;
            total += profit[i];
            remaining -= weight[i];
        }
    }

    if (i < n)
        x[i] = remaining / weight[i];

    total += x[i] * profit[i];
    printf("\nMaximum Profit: %.2f\n", total);
}

int main() {
    int n, i;
    float weight[20], profit[20], capacity;
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weight and profit of each item:\n");
    for (i = 0; i < n; i++)
        scanf("%f%f", &weight[i], &profit[i]);

    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);

    fractionalKnapsack(n, weight, profit, capacity);
    return 0;
}
