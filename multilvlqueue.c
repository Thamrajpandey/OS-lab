#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
    char type[10];
} Process;

int main() {
    Process SQ[MAX], UQ[MAX], all[MAX];

    int n, i, sq_count = 0, uq_count = 0;
    int time = 0, completed = 0;
    int TQ;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum for System Queue: ");
    scanf("%d", &TQ);

    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);

        all[i].pid = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &all[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &all[i].burst);

        all[i].remaining = all[i].burst;

        printf("Type (System/User): ");
        scanf("%s", all[i].type);

        if (strcmp(all[i].type, "System") == 0)
            SQ[sq_count++] = all[i];
        else
            UQ[uq_count++] = all[i];
    }

    for (i = 0; i < uq_count - 1; i++) {
        for (int j = i + 1; j < uq_count; j++) {
            if (UQ[i].arrival > UQ[j].arrival) {
                Process temp = UQ[i];
                UQ[i] = UQ[j];
                UQ[j] = temp;
            }
        }
    }

    while (completed < n) {
        int executed = 0;

        for (i = 0; i < sq_count; i++) {
            if (SQ[i].remaining > 0 &&
                SQ[i].arrival <= time) {

                executed = 1;

                if (SQ[i].remaining > TQ) {
                    time += TQ;
                    SQ[i].remaining -= TQ;
                } else {
                    time += SQ[i].remaining;

                    SQ[i].remaining = 0;
                    SQ[i].completion = time;
                    SQ[i].turnaround =
                        SQ[i].completion - SQ[i].arrival;

                    SQ[i].waiting =
                        SQ[i].turnaround - SQ[i].burst;

                    all[SQ[i].pid - 1] = SQ[i];
                    completed++;
                }
            }
        }

        if (!executed) {
            for (i = 0; i < uq_count; i++) {
                if (UQ[i].remaining > 0 &&
                    UQ[i].arrival <= time) {

                    executed = 1;

                    time += UQ[i].remaining;
                    UQ[i].remaining = 0;

                    UQ[i].completion = time;
                    UQ[i].turnaround =
                        UQ[i].completion - UQ[i].arrival;

                    UQ[i].waiting =
                        UQ[i].turnaround - UQ[i].burst;

                    all[UQ[i].pid - 1] = UQ[i];

                    completed++;
                    break;
                }
            }
        }

        if (!executed)
            time++;
    }

    float total_wt = 0, total_tat = 0;

    printf("\nPID\tType\tAT\tBT\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               all[i].pid,
               all[i].type,
               all[i].arrival,
               all[i].burst,
               all[i].completion,
               all[i].turnaround,
               all[i].waiting);

        total_wt += all[i].waiting;
        total_tat += all[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f",
           total_wt / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           total_tat / n);

    printf("USN:1BF24CS318");

    return 0;
}