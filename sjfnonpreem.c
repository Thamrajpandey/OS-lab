#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int completion;
    int turnaround;
    int waiting;
    int finished;
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[20];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].finished = 0;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int current_time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = 999999;

        for (int i = 0; i < n; i++) {
            if (!p[i].finished && p[i].arrival <= current_time) {
                if (p[i].burst < min_burst) {
                    min_burst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            p[idx].completion = current_time + p[idx].burst;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            current_time = p[idx].completion;
            p[idx].finished = 1;
            completed++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }

    printf("1BF24CS318");

    return 0;
}