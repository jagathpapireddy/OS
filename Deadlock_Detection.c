#include <stdio.h>

#define MAX 10

// Function to detect deadlock
void detectDeadlock(int n, int m,
                    int alloc[MAX][MAX],
                    int request[MAX][MAX],
                    int avail[MAX])
{
    int finish[MAX];
    int work[MAX];
    int i, j, k;

    // Work = Available
    for(i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }

    // Initially all processes are unfinished
    for(i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    int count = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                // Check Request <= Work
                for(j = 0; j < m; j++)
                {
                    if(request[i][j] > work[j])
                    {
                        break;
                    }
                }

                // Process can execute
                if(j == m)
                {
                    // Release allocated resources
                    for(k = 0; k < m; k++)
                    {
                        work[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        // No process can proceed
        if(found == 0)
        {
            break;
        }
    }

    // Check for deadlock
    if(count == n)
    {
        printf("\nNo Deadlock Detected\n");
    }
    else
    {
        printf("\nDeadlock Detected\n");

        printf("Processes in Deadlock: ");

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                printf("P%d ", i);
            }
        }

        printf("\n");
    }
}

int main()
{
    int n, m;
    int alloc[MAX][MAX];
    int request[MAX][MAX];
    int avail[MAX];
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Request Matrix
    printf("\nEnter Request Matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");

    for(i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Call Deadlock Detection Function
    detectDeadlock(n, m, alloc, request, avail);

    return 0;
}