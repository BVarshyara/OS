#include <stdio.h>
#include <limits.h>
typedef struct
{
    int id;
    int execution_time;
    int period;
    int deadline;
    int remaining_time;
    int next_release;
    int absolute_deadline;
} Task;
// Find task with earliest deadline
int get_edf_task(Task tasks[], int n)
{
    int min_deadline = INT_MAX;
    int selected = -1;
    for(int i = 0; i < n; i++)
    {
        if(tasks[i].remaining_time > 0)
        {
            if(tasks[i].absolute_deadline < min_deadline)
            {
                min_deadline =
                    tasks[i].absolute_deadline;
                selected = i;
            }
        }
    }
    return selected;
}
int main()
{
    int n, total_time;
    printf("Enter Number of Tasks: ");
    scanf("%d", &n);
    Task tasks[n];
    // Input
    for(int i = 0; i < n; i++)
    {
        tasks[i].id = i + 1;
        printf("\nTask %d\n", i + 1);
        printf("Execution Time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Period: ");
        scanf("%d", &tasks[i].period);
        printf("Deadline: ");
        scanf("%d", &tasks[i].deadline);
        tasks[i].remaining_time = 0;
        tasks[i].next_release = 0;
        tasks[i].absolute_deadline = 0;
    }

    printf("\nEnter Total Simulation Time: ");
    scanf("%d", &total_time);
    printf("\n================================");
    printf("\n Earliest Deadline First (EDF)");
    printf("\n================================");
    printf("\n\nTime\tRunning Task");
    printf("\n-------------------------\n");
    // Simulation
    for(int t = 0; t < total_time; t++)
    {
        // Release tasks periodically
        for(int i = 0; i < n; i++)
        {
            if(t == tasks[i].next_release)
            {
                tasks[i].remaining_time =
                    tasks[i].execution_time;
                tasks[i].absolute_deadline =
                    t + tasks[i].deadline;
                tasks[i].next_release +=
                    tasks[i].period;
            }
        }
        // Select EDF task
        int current = get_edf_task(tasks, n);
        if(current != -1)
        {
            printf("%d\tTask %d\n",
                   t,
                   tasks[current].id);
            tasks[current].remaining_time--;
        }
        else
        {
            printf("%d\tIdle\n", t);
        }
    }
    return 0;
}
