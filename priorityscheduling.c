#include <stdio.h>
typedef struct {
    int pid;
    int bt;     // burst time
    int pr;     // priority
    int wt;     // waiting time
    int tat;    // turnaround time
    int ct;     // finish time
} Process;
void sortByPriority(Process p[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[j].pr < p[i].pr) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time and Priority for Process P%d: ", p[i].pid);
        scanf("%d %d", &p[i].bt, &p[i].pr);
    }
    // Sort processes by priority
    sortByPriority(p, n);
    // Calculate waiting time, turnaround time, finish time
    int time = 0;
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }
    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        printf("   %d", time);
    }
    // Output results
    float avgWT = 0, avgTAT = 0;
    printf("\n\nProcess\tBT\tPriority\tFT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\t%d\n",
            p[i].pid, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }
    printf("\nAverage Turnaround Time: %.2f", avgTAT / n);
    printf("\nAverage Waiting Time: %.2f\n", avgWT / n);
    return 0;
}
