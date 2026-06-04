#include <stdio.h>

// Function for First Fit Allocation
void firstFit(int block[], int m, int process[], int n)
{
    int allocated[m];

    // Initially all memory blocks are free
    for(int i = 0; i < m; i++)
        allocated[i] = 0;

    printf("\n--- First Fit ---\n");

    // Traverse all processes
    for(int i = 0; i < n; i++)
    {
        int found = 0;

        // Find the first suitable free block
        for(int j = 0; j < m; j++)
        {
            if(allocated[j] == 0 && block[j] >= process[i])
            {
                allocated[j] = 1;     // Mark block as allocated

                printf("Process %d KB -> Block %d (%d KB)\n",
                       process[i], j + 1, block[j]);

                found = 1;
                break;                // Stop after first suitable block
            }
        }

        // If no block is found
        if(found == 0)
        {
            printf("Process %d KB -> Not Allocated\n",
                   process[i]);
        }
    }
}

// Function for Best Fit Allocation
void bestFit(int block[], int m, int process[], int n)
{
    int allocated[m];

    // Initially all memory blocks are free
    for(int i = 0; i < m; i++)
        allocated[i] = 0;

    printf("\n--- Best Fit ---\n");

    // Traverse all processes
    for(int i = 0; i < n; i++)
    {
        int best = -1; // Stores index of best block

        // Find smallest suitable free block
        for(int j = 0; j < m; j++)
        {
            if(allocated[j] == 0 && block[j] >= process[i])
            {
                if(best == -1 || block[j] < block[best])
                {
                    best = j;
                }
            }
        }

        // If suitable block is found
        if(best != -1)
        {
            allocated[best] = 1;

            printf("Process %d KB -> Block %d (%d KB)\n",
                   process[i], best + 1, block[best]);
        }
        else
        {
            printf("Process %d KB -> Not Allocated\n",
                   process[i]);
        }
    }
}

// Function for Worst Fit Allocation
void worstFit(int block[], int m, int process[], int n)
{
    int allocated[m];

    // Initially all memory blocks are free
    for(int i = 0; i < m; i++)
        allocated[i] = 0;

    printf("\n--- Worst Fit ---\n");

    // Traverse all processes
    for(int i = 0; i < n; i++)
    {
        int worst = -1; // Stores index of largest suitable block

        // Find largest suitable free block
        for(int j = 0; j < m; j++)
        {
            if(allocated[j] == 0 && block[j] >= process[i])
            {
                if(worst == -1 || block[j] > block[worst])
                {
                    worst = j;
                }
            }
        }

        // If suitable block is found
        if(worst != -1)
        {
            allocated[worst] = 1;

            printf("Process %d KB -> Block %d (%d KB)\n",
                   process[i], worst + 1, block[worst]);
        }
        else
        {
            printf("Process %d KB -> Not Allocated\n",
                   process[i]);
        }
    }
}

int main()
{
    int m, n;

    // Read number of memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int block[m];

    // Read memory block sizes
    printf("Enter block sizes:\n");
    for(int i = 0; i < m; i++)
    {
        scanf("%d", &block[i]);
    }

    // Read number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process[n];

    // Read process sizes
    printf("Enter process sizes:\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &process[i]);
    }

    // Call all three allocation techniques
    firstFit(block, m, process, n);
    bestFit(block, m, process, n);
    worstFit(block, m, process, n);

    return 0;
}