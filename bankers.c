#include <stdio.h>

#define MAX 10

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX];

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Demand Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[MAX] = {0};
    int safeSeq[MAX];
    int work[MAX];

    for(i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m) {

                    for(k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            break;
        }
    }

    if(count == n) {
        printf("\nSystem is in a safe state.\n");

        printf("Safe sequence is: ");

        for(i = 0; i < n; i++) {
            printf("P%d", safeSeq[i]);

            if(i != n - 1)
                printf(" -> ");
        }
    }
    else {
        printf("\nSystem is NOT in a safe state.\n");
    }

    printf("\nUSN:1BF24CS318");

    return 0;
}