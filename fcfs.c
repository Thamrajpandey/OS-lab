
#include <stdio.h>

int main() {
    int n, i, j;
    int arrival[20], burst[20];
    int completion[20], turnaround[20], waiting[20];
    int process[20];
    int current_time = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter total number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        process[i] = i + 1;

        printf("Process [%d]\n", i + 1);

        printf("Arrival time: ");
        scanf("%d", &arrival[i]);

        printf("Burst time: ");
        scanf("%d", &burst[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(arrival[i] > arrival[j]) {

                int temp;

                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    for(i = 0; i < n; i++) {

        if(current_time < arrival[i]) {
            current_time = arrival[i];
        }

        completion[i] = current_time + burst[i];
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        current_time = completion[i];

        avg_tat += turnaround[i];
        avg_wt += waiting[i];
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nProcess Arrival Time Burst Time Completion Time Turnaround Time Waiting Time\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               completion[i],
               turnaround[i],
               waiting[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}
