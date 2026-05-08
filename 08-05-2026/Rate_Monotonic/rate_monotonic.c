#include<stdio.h>
#include<math.h>
int main()
{
    int n;
    float e[20], p[20];
    int i;
    float ut = 0, u, x, y;
    printf("\nEnter Number of Processes : ");
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        printf("Enter Execution Time for P%d : ", (i + 1));
        scanf("%f", &e[i]);
        printf("Enter Period for P%d : ", (i + 1));
        scanf("%f", &p[i]);
    }
    // Calculate total utilization
    for(i = 0; i < n; i++)
    {
        x = e[i] / p[i];
        ut = ut + x;
    }
    // Calculate RMS bound
    y = (float)n;
    y = y * ((pow(2.0, 1/y)) - 1);
    u = y;
    // Check schedulability
    printf("\nTotal Utilization : %f",ut);
    printf("\nUtilization Bound : %f",u);
    if(ut < u)
    {
        printf("\nAs %f < %f,", ut, u);
        printf("\nThe System is surely Schedulable");
    }
    else
    {
        printf("\nAs %f >= %f,", ut, u);
        printf("\nNot Sure...");
    }
    return 0;
}
