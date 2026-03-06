#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, i, j, choice;
    int p[20], AT[20], BT[20], CT[20], TAT[20], WT[20], RT[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &AT[i]);
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &BT[i]);
        p[i] = i+1;
        RT[i] = BT[i]; // remaining time for preemptive
    }

    printf("\nChoose Scheduling Type:\n");
    printf("1. Non-preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: {
            // Non-preemptive SJF
            int time = 0, completed[20] = {0}, count = 0;
            while(count < n) {
                int idx = -1, min_bt = 9999;
                for(i = 0; i < n; i++) {
                    if(!completed[i] && AT[i] <= time && BT[i] < min_bt) {
                        min_bt = BT[i];
                        idx = i;
                    }
                }
                if(idx == -1) {
                    time++;
                } else {
                    time += BT[idx];
                    CT[idx] = time;
                    completed[idx] = 1;
                    count++;
                }
            }
            break;
        }

        case 2: {
            // Preemptive SJF (Shortest Remaining Time First)
            int time = 0, completed = 0;
            while(completed < n) {
                int idx = -1, min_rt = 9999;
                for(i = 0; i < n; i++) {
                    if(AT[i] <= time && RT[i] > 0 && RT[i] < min_rt) {
                        min_rt = RT[i];
                        idx = i;
                    }
                }
                if(idx == -1) {
                    time++;
                } else {
                    RT[idx]--;
                    time++;
                    if(RT[idx] == 0) {
                        CT[idx] = time;
                        completed++;
                    }
                }
            }
            break;
        }

        default:
            printf("Invalid choice!\n");
            return 0;
    }

    // Calculate TAT and WT
    for(i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        avg_wt += WT[i];
        avg_tat += TAT[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
