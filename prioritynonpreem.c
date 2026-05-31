#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int tat;
    int wt;
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[20];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter Arrival Time and Burst Time for process %d: ",
               p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);

        printf("Enter priority for process %d: ", p[i].pid);
        scanf("%d", &p[i].priority);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].priority < p[j].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\nProcess\tAT\tBT\tPriority\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].priority,
               p[i].wt,
               p[i].tat);
    }

    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", avgWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);

    printf("USN:1BF24CS318");

    return 0;
}