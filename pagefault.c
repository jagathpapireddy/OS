#include <stdio.h>

int main()
{
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int fifo[f], lru[f], opt[f];

    for(int i = 0; i < f; i++)
    {
        fifo[i] = -1;
        lru[i] = -1;
        opt[i] = -1;
    }

    int fifoFaults = 0, lruFaults = 0, optFaults = 0;

    int pos = 0;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(fifo[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            fifo[pos] = pages[i];
            pos = (pos + 1) % f;
            fifoFaults++;
        }
    }

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(lru[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int empty = -1;

            for(int j = 0; j < f; j++)
            {
                if(lru[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if(empty != -1)
            {
                lru[empty] = pages[i];
            }
            else
            {
                int least = i;
                int index = -1;

                for(int j = 0; j < f; j++)
                {
                    int k;

                    for(k = i - 1; k >= 0; k--)
                    {
                        if(lru[j] == pages[k])
                            break;
                    }

                    if(k < least)
                    {
                        least = k;
                        index = j;
                    }
                }

                lru[index] = pages[i];
            }

            lruFaults++;
        }
    }

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < f; j++)
        {
            if(opt[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int empty = -1;

            for(int j = 0; j < f; j++)
            {
                if(opt[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if(empty != -1)
            {
                opt[empty] = pages[i];
            }
            else
            {
                int farthest = -1;
                int index = -1;

                for(int j = 0; j < f; j++)
                {
                    int k;

                    for(k = i + 1; k < n; k++)
                    {
                        if(opt[j] == pages[k])
                            break;
                    }

                    if(k == n)
                    {
                        index = j;
                        break;
                    }

                    if(k > farthest)
                    {
                        farthest = k;
                        index = j;
                    }
                }

                opt[index] = pages[i];
            }

            optFaults++;
        }
    }

    printf("\nFIFO Page Faults = %d", fifoFaults);
    printf("\nLRU Page Faults = %d", lruFaults);
    printf("\nOptimal Page Faults = %d", optFaults);

    return 0;
}