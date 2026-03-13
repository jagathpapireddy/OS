#include <stdio.h>

struct Process {
    int pid, at, bt, pr;
    int ct, tat, wt, rt;
};

void nonPreemptive(struct Process p[], int n) {
    int time = 0, complete = 0;
    int done[n];
    for (int i = 0; i < n; i++) done[i] = 0;

    while (complete < n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time) {
                if (p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        complete++;
    }
}

void preemptive(struct Process p[], int n) {
    int time = 0, complete = 0;
    while (complete < n) {
        int idx = -1, highest = 9999;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr < highest) {
                    highest = p[i].pr;
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        p[idx].rt--;
        time++;
        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            complete++;
        }
    }
}

void display(struct Process p[], int n) {
    double avgTAT = 0, avgWT = 0;
    printf("P\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
    }
    printf("Average TAT = %.2f\n", avgTAT / n);
    printf("Average WT = %.2f\n", avgWT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], copy[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("AT P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("BT P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Priority P%d: ", i + 1);
        scanf("%d", &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        copy[i] = p[i];
    }

    int choice;
    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Non-Preemptive Priority Scheduling\n");
    printf("2. Preemptive Priority Scheduling\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\n--- Non-Preemptive Priority Scheduling ---\n");
            nonPreemptive(p, n);
            display(p, n);
            break;
        case 2:
            printf("\n--- Preemptive Priority Scheduling ---\n");
            preemptive(copy, n);
            display(copy, n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
