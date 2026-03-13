#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int main() {
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    int process_id[MAX], arrival_time[MAX], burst_time[MAX];
    int remaining_time[MAX], completion_time[MAX];
    int waiting_time[MAX], turnaround_time[MAX];
    bool completed[MAX];

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process P%d\n", i + 1);
        process_id[i] = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        remaining_time[i] = burst_time[i];
        completed[i] = false;
    }

    int current_time = 0, completed_count = 0;
    float totalWT = 0, totalTAT = 0;

    // Round Robin scheduling loop
    while (completed_count < n) {
        bool idle = true;
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                idle = false;
                if (remaining_time[i] > time_quantum) {
                    remaining_time[i] -= time_quantum;
                    current_time += time_quantum;
                } else {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                    completion_time[i] = current_time;

                    turnaround_time[i] = completion_time[i] - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];

                    totalWT += waiting_time[i];
                    totalTAT += turnaround_time[i];

                    completed[i] = true;
                    completed_count++;
                }
            }
        }
        if (idle) {
            current_time++; // CPU idle
        }
    }

    // Output results
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process_id[i], arrival_time[i], burst_time[i],
               completion_time[i], turnaround_time[i], waiting_time[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("USN:1BF24CS318");

    return 0;
}
