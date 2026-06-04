#include <stdio.h>

struct Task
{
    int id;
    int burst;
    int period;
    int deadline;
    int remaining;
};

int main()
{
    int n, totalTime;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    struct Task task[n];

    for(int i = 0; i < n; i++)
    {
        task[i].id = i + 1;

        printf("\nTask %d\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &task[i].burst);

        printf("Period: ");
        scanf("%d", &task[i].period);

        task[i].remaining = 0;
        task[i].deadline = task[i].period;
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &totalTime);

    printf("\nGantt Chart:\n");

    for(int time = 0; time < totalTime; time++)
    {
        for(int i = 0; i < n; i++)
        {
            if(time % task[i].period == 0)
            {
                task[i].remaining = task[i].burst;
                task[i].deadline = time + task[i].period;
            }
        }

        int selected = -1;

        for(int i = 0; i < n; i++)
        {
            if(task[i].remaining > 0)
            {
                if(selected == -1 || task[i].deadline < task[selected].deadline)
                {
                    selected = i;
                }
            }
        }

        if(selected != -1)
        {
            printf("| T%d ", task[selected].id);
            task[selected].remaining--;
        }
        else
        {
            printf("| IDLE ");
        }
    }

    printf("|\n");

    for(int i = 0; i <= totalTime; i++)
    {
        printf("%-6d", i);
    }

    printf("\n");

    return 0;
}
