#include <stdio.h>

struct process {
    int pid, at, bt, ct, tat, wt, rt, type;
};

int main() {
    struct process p[20];
    int n, tq;
    float avgwt = 0.0, avgtat = 0.0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);
        p[i].rt = p[i].bt;
    }

    printf("\nEnter time quantum for System processes: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int visited[20] = {0};
    int queue[100], front = 0, rear = 0;

    while (completed < n) {
        // Add processes to queue
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int idx = queue[front++];

        if (p[idx].type == 0) { // System → Round Robin
            if (p[idx].rt > tq) {
                p[idx].rt -= tq;
                time += tq;
            } else {
                time += p[idx].rt;
                p[idx].rt = 0;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                avgwt += p[idx].wt;
                avgtat += p[idx].tat;
                completed++;
            }
        } else { // User → FCFS
            time += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            avgwt += p[idx].wt;
            avgtat += p[idx].tat;
            completed++;
        }

        // Add new arrivals
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Requeue system process if not finished
        if (p[idx].type == 0 && p[idx].rt > 0) {
            queue[rear++] = idx;
        }
    }

    printf("\n--- Multi-Level Queue Scheduling ---\n");
    printf("ID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].type == 0 ? "System" : "User",
               p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", avgtat / n);
    printf("\nAverage WT = %.2f\n", avgwt / n);

    return 0;
}
