#include <stdio.h>
int main() {
    int n, i, j;
    int p[10], AT[10], BT[10], TAT[10], CT[10], WT[10];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &AT[i]);
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &BT[i]);
        p[i] = i+1;
    }
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(AT[i] > AT[j]) {
                swap(&AT[i], &AT[j]);
                swap(&BT[i], &BT[j]);
                swap(&p[i], &p[j]);
            }
        }
    }
    CT[0] = AT[0] + BT[0];
    for(i = 1; i < n; i++) {
        if(CT[i-1] < AT[i]) {
            CT[i] = AT[i] + BT[i];
        } else {
            CT[i] = CT[i-1] + BT[i];
        }
    }
    for(i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
        avg_wt += WT[i];
        avg_tat += TAT[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i], AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }
    printf("\nAverage Waiting Time: %f", avg_wt);
    printf("\nAverage Turnaround Time: %f\n", avg_tat);

}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
