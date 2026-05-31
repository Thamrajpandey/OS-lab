#include <stdio.h>

#define MAX 20

typedef struct {
    int id;
    int arrival;
    int burst;
    int deadline;
    int completed;
} Process;

void edfScheduling(Process p[], int n) {
    int time = 0, completed = 0;

    printf("\n--- Earliest Deadline First Scheduling ---\n");

    while (completed < n) {
        int idx = -1;
        int minDeadline = 9999;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= time) {
                if (p[i].deadline < minDeadline) {
                    minDeadline = p[i].deadline;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            printf("Time %d -> %d : Process P%d\n",
                   time,
                   time + p[idx].burst,
                   p[idx].id);

            time += p[idx].burst;
            p[idx].completed = 1;
            completed++;
        } else {
            time++;
        }
    }
}

int main() {
    int n;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        p[i].id = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline: ");
        scanf("%d", &p[i].deadline);

        p[i].completed = 0;
    }

    edfScheduling(p, n);

    printf("USN:1BF24CS318");

    return 0;
}