#include<stdio.h>
int main(){
    printf("NAME : BUKKAPATNAM VARSHYARA | USN : 1BM24CS075 | DATE : 06-03-2026");
    int n,i,j;
    printf("\nEnter the number of Processes:");
    scanf("%d",&n);
    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    float avg_wt = 0, avg_tat = 0;
    for(i=0;i<n;i++){
        printf("Enter Process ID : ");
        scanf("%d",&pid[i]);
        printf("Enter Arrival Time:");
        scanf("%d",&at[i]);
        printf("Enter Burst Time:");
        scanf("%d",&bt[i]);
    }
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp=pid[1];
                pid[i]=pid[j];
                pid[j]=temp;
            }
        }
    }
    int current_time = 0;
    for(i = 0; i < n; i++) {
        if(current_time < at[i]) {
            current_time = at[i];
        }
        ct[i] = current_time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        current_time = ct[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    avg_wt /= n;
    avg_tat /= n;
    printf("\nProcess \tAT \tBT \tCT \tTAT \tWT");
    for(i = 0; i < n; i++){
        printf("\n\tP%d \t%d \t%d \t%d \t%d \t%d", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
    return 0;
}
