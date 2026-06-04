#include <stdio.h>

struct Task
{
    int id;
    int share;
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

        printf("Enter CPU Share for Task %d: ", i + 1);
        scanf("%d", &task[i].share);
    }

    printf("Enter simulation time: ");
    scanf("%d", &totalTime);

    printf("\nGantt Chart:\n");

    int time = 0;

    while(time < totalTime)
    {
        for(int i = 0; i < n && time < totalTime; i++)
        {
            for(int j = 0; j < task[i].share && time < totalTime; j++)
            {
                printf("| T%d ", task[i].id);
                time++;
            }
        }
    }

    printf("|\n");

    for(int i = 0; i <= totalTime; i++)
    {
        printf("%-5d", i);
    }

    printf("\n");

    return 0;
}