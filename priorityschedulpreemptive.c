#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int Process_ID[n], Arrival_Time[n], Burst_Time[n], Priority[n];
    int Remaining_Time[n], Completion_Time[n], Turnaround_Time[n], Waiting_Time[n];
    bool Finished[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process P%d\n", i + 1);
        Process_ID[i] = i + 1; // auto assign PID
        printf("Arrival Time: ");
        scanf("%d", &Arrival_Time[i]);
        printf("Burst Time: ");
        scanf("%d", &Burst_Time[i]);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &Priority[i]);
        Remaining_Time[i] = Burst_Time[i];
        Finished[i] = false;
    }

    int Current_Time = 0, Completed = 0;
    float totalTAT = 0, totalWT = 0;

    // Scheduling loop
    while (Completed < n) {
        int Highest_Priority = 999999;
        int Selected_Process = -1;

        // Find process with highest priority among arrived and not finished
        for (int i = 0; i < n; i++) {
            if (Arrival_Time[i] <= Current_Time && Remaining_Time[i] > 0) {
                if (Priority[i] < Highest_Priority) {
                    Highest_Priority = Priority[i];
                    Selected_Process = i;
                }
            }
        }

        if (Selected_Process == -1) {
            Current_Time++; // idle time
        } else {
            Remaining_Time[Selected_Process]--;
            Current_Time++;

            if (Remaining_Time[Selected_Process] == 0) {
                Completion_Time[Selected_Process] = Current_Time;
                Turnaround_Time[Selected_Process] =
                    Completion_Time[Selected_Process] - Arrival_Time[Selected_Process];
                Waiting_Time[Selected_Process] =
                    Turnaround_Time[Selected_Process] - Burst_Time[Selected_Process];

                Finished[Selected_Process] = true;
                Completed++;

                totalTAT += Turnaround_Time[Selected_Process];
                totalWT += Waiting_Time[Selected_Process];
            }
        }
    }

    // Output results
    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               Process_ID[i], Arrival_Time[i], Burst_Time[i],
               Priority[i], Completion_Time[i],
               Turnaround_Time[i], Waiting_Time[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("USN:1BF24CS318");

    return 0;
}
