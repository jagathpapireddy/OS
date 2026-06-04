#include <stdio.h>

// Function to calculate Need Matrix
void calculateNeed(int n, int m, int max[n][m], int alloc[n][m], int need[n][m])
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Safety Algorithm Function
int isSafe(int n, int m,
           int alloc[n][m],
           int need[n][m],
           int avail[m],
           int safeSeq[n])
{
    int finish[n];
    int work[m];
    int i, j, k;

    // Finish = false
    for (i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    // Work = Available
    for (i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }

    int count = 0;

    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                // Check Need <= Work
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }

                // Process can execute
                if (j == m)
                {
                    for (k = 0; k < m; k++)
                    {
                        work[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
        {
            break;
        }
    }

    if (count == n)
    {
        return 1;
    }

    return 0;
}

int main()
{
    int n, m, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m];
    int max[n][m];
    int need[n][m];
    int avail[m];
    int safeSeq[n];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    calculateNeed(n, m, max, alloc, need);

    // Display Need Matrix
    printf("\nNeed Matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Initial Safety Check
    if (isSafe(n, m, alloc, need, avail, safeSeq))
    {
        printf("\nSystem is in SAFE STATE\n");

        printf("Safe Sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d ", safeSeq[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in SAFE STATE\n");
        return 0;
    }

    // Resource Request Algorithm
    int p;
    int req[m];

    printf("\nEnter process number for resource request: ");
    scanf("%d", &p);

    printf("Enter request vector:\n");

    for (i = 0; i < m; i++)
    {
        scanf("%d", &req[i]);
    }

    // Check Request <= Need
    for (i = 0; i < m; i++)
    {
        if (req[i] > need[p][i])
        {
            printf("\nError: Request exceeds Need\n");
            return 0;
        }
    }

    // Check Request <= Available
    for (i = 0; i < m; i++)
    {
        if (req[i] > avail[i])
        {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }

    // Pretend Allocation
    for (i = 0; i < m; i++)
    {
        avail[i] -= req[i];
        alloc[p][i] += req[i];
        need[p][i] -= req[i];
    }

    // Check Safe State Again
    if (isSafe(n, m, alloc, need, avail, safeSeq))
    {
        printf("\nRequest can be GRANTED\n");

        printf("New Safe Sequence: ");

        for (i = 0; i < n; i++)
        {
            printf("P%d ", safeSeq[i]);
        }

        printf("\n");
    }
    else
    {
        printf("\nRequest CANNOT be granted (Unsafe State)\n");
    }

    return 0;
}