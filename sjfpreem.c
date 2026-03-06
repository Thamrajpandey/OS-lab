#include <stdio.h>

struct Process {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int rt;     // Remaining Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
};

int main() {

    int n, i, current_time = 0, completed = 0, shortest;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);

        p[i].rt = p[i].bt; // Remaining time initially equals burst time
    }

    // SJF Preemptive Scheduling
    while(completed < n) {

        shortest = -1;

        for(i = 0; i < n; i++) {
            if(p[i].at <= current_time && p[i].rt > 0) {

                if(shortest == -1 || p[i].rt < p[shortest].rt) {
                    shortest = i;
                }
            }
        }

        if(shortest == -1) {
            current_time++;
        }
        else {

            // Execute for 1 unit time
            p[shortest].rt--;

            current_time++;

            // If process finishes
            if(p[shortest].rt == 0) {

                completed++;

                p[shortest].ct = current_time;

                p[shortest].tat = p[shortest].ct - p[shortest].at;

                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }
    }

    // Output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    float avg_tat = 0, avg_wt = 0;

    for(i = 0; i < n; i++) {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nAverage Turnaround Time = %.2f", avg_tat);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);

    return 0;
}
