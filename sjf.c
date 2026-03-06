#include <stdio.h>

struct Process {
    int pid;
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
    int finished;
};

int main() {

    int n, i, current_time = 0, completed = 0, shortest;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].finished = 0;

        printf("Enter Arrival Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].at);

        printf("Enter Burst Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    // SJF Scheduling
    while(completed < n) {

        shortest = -1;

        for(i = 0; i < n; i++) {
            if(p[i].at <= current_time && p[i].finished == 0) {

                if(shortest == -1 || p[i].bt < p[shortest].bt) {
                    shortest = i;
                }
            }
        }

        if(shortest == -1) {
            current_time++;
        }
        else {

            p[shortest].ct = current_time + p[shortest].bt;

            p[shortest].tat = p[shortest].ct - p[shortest].at;

            p[shortest].wt = p[shortest].tat - p[shortest].bt;

            current_time = p[shortest].ct;

            p[shortest].finished = 1;

            completed++;
        }
    }

    // Output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    return 0;
    }
