#include <stdio.h>

#define MAX 10

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int find_lcm(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}

int main() {
    printf("USN:1BF24CS318 \n");
    int n;
    int C[MAX], P[MAX];
    int remaining[MAX] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
    }

    printf("Enter time periods:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &P[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (P[i] > P[j]) {
                int temp;
                temp = P[i]; P[i] = P[j]; P[j] = temp;
                temp = C[i]; C[i] = C[j]; C[j] = temp;
            }
        }
    }

    int hyperperiod = find_lcm(P, n);
    printf("\nLCM  = %d\n", hyperperiod);
    printf("USN:1BF24CS318");
    printf("\nScheduling Timeline:\n");

    for (int t = 0; t < hyperperiod; t++) {
        for (int i = 0; i < n; i++) {
            if (t % P[i] == 0) {
                remaining[i] = C[i];
            }
        }

        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                selected = i;
                break;
            }
        }

        if (selected != -1) {
            printf("%d ms: Process %d running\n", t, selected + 1);
            remaining[selected]--;
        } else {
            printf("%d ms: CPU is idle\n", t);
        }
    }

    return 0;
}
