#include<stdio.h>
struct process {
    int pid;
    int at;     // Arrival Time
    int bt;     // Burst Time
    int tbt;    // Total Burst Time
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Response Time
    int is_completed;
    int start_time;  // New field to track start time for Gantt chart
};
void generate_gantt_chart(struct process p[], int n) {
    printf("\nGantt Chart:\n");
    printf("Time\t");
    for (int i = 0; i < n; i++) {
        if (p[i].is_completed) {
            printf("| P%d ", p[i].pid);
        }
    }
    printf("|\n");  
    printf("      ");
    for (int i = 0; i < n; i++) {
        if (p[i].is_completed) {
            printf("%d    ", p[i].start_time);
        }
    }
    printf("%d\n", p[n-1].ct);
}
int main() {
    int n;
    printf("Enter the no. of processes:\n");
    scanf("%d", &n);
    struct process p[n];   
    printf("Enter the id of the process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].pid);
    }
    printf("Enter the arrival time of the process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }
    printf("Enter the burst time of the process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
        p[i].tbt = p[i].bt;
        p[i].is_completed = 0;
        p[i].start_time = -1;  // Initialize start time
    }
    int completed = 0;
    int current_time = 0; 
    while (completed < n) {
        int min = 1000;
        int shortest_job = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].is_completed == 0) {
                if (p[i].bt < min) {
                    min = p[i].bt;
                    shortest_job = i;
                }
            }
        }
        if (shortest_job == -1) {
            current_time++;
        } else {
            if (p[shortest_job].start_time == -1) {
                p[shortest_job].start_time = current_time;
            }
            p[shortest_job].ct = current_time + p[shortest_job].bt;
            p[shortest_job].tat = p[shortest_job].ct - p[shortest_job].at;
            p[shortest_job].wt = p[shortest_job].tat - p[shortest_job].bt;
            p[shortest_job].rt = p[shortest_job].start_time - p[shortest_job].at;
            current_time = p[shortest_job].ct;
            p[shortest_job].is_completed = 1;
            completed++;
        }
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    float total_tat = 0, total_wt = 0, total_rt = 0;
    int min_at = 1000;
    int max_ct = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        total_rt += p[i].rt;   
        if (p[i].at < min_at) {
            min_at = p[i].at;
        }
        if (p[i].ct > max_ct) {
            max_ct = p[i].ct;
        }
    }
    generate_gantt_chart(p, n);
    float sl = max_ct - min_at;
    float th = (float)n / sl;
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
    printf("Schedule Length: %.2f\n", sl);
    printf("Throughput: %.2f process/unit time\n", th);
    return 0;
}