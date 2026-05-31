#include <stdio.h>

#define MAX 20

typedef struct {
    int id;
    int weight;
} Process;

void proportionalScheduling(Process p[], int n, int total_time) {
    int total_weight = 0;

    printf("\n--- Proportional Scheduling ---\n");

    for (int i = 0; i < n; i++) {
        total_weight += p[i].weight;
    }

    for (int i = 0; i < n; i++) {
        float cpu_share =
            ((float)p[i].weight / total_weight) * total_time;

        printf("Process P%d gets CPU time = %.2f units\n",
               p[i].id,
               cpu_share);
    }
}

int main() {
    int n, total_time;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        p[i].id = i + 1;

        printf("Enter weight: ");
        scanf("%d", &p[i].weight);
    }

    printf("\nEnter total CPU time: ");
    scanf("%d", &total_time);

    proportionalScheduling(p, n, total_time);

    printf("\nUSN:1BF24CS318");

    return 0;
}