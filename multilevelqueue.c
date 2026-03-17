#include <stdio.h>

#define MAX 50

struct process {
    int pid, at, bt, rt;
    int ct, tat, wt;
    int queue; // 1 = System (RR), 2 = User (FCFS)
};

int main() {
    struct process p[MAX];
    int n, i, time = 0, completed = 0;
    int tq = 2; // Time Quantum for Queue 1

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        p[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Queue (1-System RR, 2-User FCFS): ");
        scanf("%d", &p[i].queue);

        p[i].rt = p[i].bt; // remaining time
    }

    // Execution
    while (completed < n) {

        int executed = 0;

        // 🔴 Queue 1 → Round Robin
        for (i = 0; i < n; i++) {
            if (p[i].queue == 1 && p[i].rt > 0 && p[i].at <= time) {

                executed = 1;

                if (p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    completed++;
                }
            }
        }

        // 🔵 Queue 2 → FCFS (only if Queue 1 empty)
        if (!executed) {
            for (i = 0; i < n; i++) {
                if (p[i].queue == 2 && p[i].rt > 0 && p[i].at <= time) {

                    executed = 1;

                    time += p[i].rt;
                    p[i].rt = 0;

                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;

                    completed++;
                }
            }
        }

        // If no process executed → CPU idle
        if (!executed) {
            time++;
        }
    }

    // Output
    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tQ\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].queue,
               p[i].ct, p[i].tat, p[i].wt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage WT = %.2f\n", total_wt / n);

    return 0;
}