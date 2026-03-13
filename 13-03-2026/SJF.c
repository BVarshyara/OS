#include <stdio.h>
int main()
{
    printf("NAME : BUKKAPATNAM VARSHYARA | USN : 1BM24CS075 | DATE : 06-03-2026");
    int n,i,choice;
    printf("\nEnter the number of Processes: ");
    scanf("%d",&n);
    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    float avg_wt = 0, avg_tat = 0;
    int completed=0, time=0;
    int min, pos, finish;
    for(i=0;i<n;i++)
    {
        printf("Enter Process ID : ");
        scanf("%d",&pid[i]);
        printf("Enter Arrival Time: ");
        scanf("%d",&at[i]);
        printf("Enter Burst Time: ");
        scanf("%d",&bt[i]);
        rt[i] = bt[i];   // remaining time
    }
    printf("\n1. Non Preemptive SJF");
    printf("\n2. Preemptive SJF");
    printf("\nEnter choice: ");
    scanf("%d", &choice);
    switch(choice)
    {
    case 1: // Non Preemptive SJF
    {
        int done[n];
        for(i=0;i<n;i++)
            done[i]=0;
        while(completed < n)
        {
            min = 9999;
            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && done[i] == 0)
                {
                    if(bt[i] < min)
                    {
                        min = bt[i];
                        pos = i;
                    }
                }
            }
            time += bt[pos];
            ct[pos] = time;
            tat[pos] = ct[pos] - at[pos];
            wt[pos] = tat[pos] - bt[pos];
            done[pos] = 1;
            completed++;
        }
        break;
    }
    case 2: // Preemptive SJF
    {
        while(completed < n)
        {
            min = 9999;
            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && rt[i] > 0)
                {
                    if(rt[i] < min)
                    {
                        min = rt[i];
                        pos = i;
                    }
                }
            }
            rt[pos]--;
            time++;
            if(rt[pos] == 0)
            {
                completed++;
                finish = time;
                ct[pos] = finish;
                tat[pos] = ct[pos] - at[pos];
                wt[pos] = tat[pos] - bt[pos];
            }
        }
        break;
    }
    default:
        printf("Invalid choice");
        return 0;
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
        pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    return 0;
}
