#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
void lotteryScheduling(int n, int exec[], int tickets[]) {
    int remaining[MAX];
    int totalTickets = 0;
    int completed = 0;
    int timeCount = 0;
    for (int i = 0; i < n; i++) {
        remaining[i] = exec[i];
        totalTickets += tickets[i];
    }
    srand(time(0));
    printf("\n--- Proportional Scheduling ---\n");
    while (completed < n) {
        int winningTicket = (rand() % totalTickets) + 1;
        int sum = 0;
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                sum += tickets[i];
                if (winningTicket <= sum) {
                    selected = i;
                    break;
                }
            }
        }
        if (selected != -1) {
            printf("Time %2d -> Process P%d runs\n",
                   timeCount, selected + 1);
            remaining[selected]--;
            timeCount++;
            if (remaining[selected] == 0) {
                printf("Process P%d completed\n",
                       selected + 1);
                completed++;
                totalTickets -= tickets[selected];
            }
        }
    }
}
int main() {
    int n;
    int exec[MAX], tickets[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("\nEnter execution time for P%d: ", i + 1);
        scanf("%d", &exec[i]);
        printf("Enter tickets for P%d: ", i + 1);
        scanf("%d", &tickets[i]);
    }
    lotteryScheduling(n, exec, tickets);
    return 0;
}
