#include <stdio.h>

struct process {
    int pid;    // Process ID
    int at;     // Arrival Time
    int bt;     // Burst Time
    int tbt;    // Total Burst Time (original burst time)
    int ct;     // Completion Time
    int tat;    // Turnaround Time
    int wt;     // Waiting Time
    int rt;     // Remaining Time
};

int main() {
    int n, tq;
    
    // Input number of processes
    printf("Enter the number of processes:\n");
    scanf("%d", &n);
    struct process p[n];
    
    // Input time quantum
    printf("Enter the time quantum:\n");
    scanf("%d", &tq);
    
    // Input process IDs
    printf("Enter the ID of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].pid);
    }
    
    // Input arrival times
    printf("Enter the arrival time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }
    
    // Input burst times
    printf("Enter the burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;    // Initialize remaining time
        p[i].tbt = p[i].bt;   // Store original burst time
    }
    
    int completed = 0;        // Number of completed processes
    int current_time = 0;     // Current time
    int queue[100];           // Process queue
    int front = 0, rear = 0;  // Queue management
    
    // Initially add processes with arrival time 0 to the queue
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear] = i;
            rear++;
        }
    }
    
    // Round Robin scheduling algorithm
    while (completed < n) {
        // If queue is empty, find next process
        if (front == rear) {
            int min_arrival = 1000;
            int next_process = -1;
            
            // Find the next process to execute
            for (int i = 0; i < n; i++) {
                if (p[i].rt > 0 && p[i].at > current_time && p[i].at < min_arrival) {
                    min_arrival = p[i].at;
                    next_process = i;
                }
            }
            
            // If no process found, break
            if (next_process == -1) {
                break;
             }
            
            // Update current time and add process to queue
            current_time = p[next_process].at;
            queue[rear] = next_process;
            rear++;
        }
        
        // Get current process from queue
        int current_process = queue[front];
        front++;
        
        // Determine execution time (minimum of time quantum or remaining time)
        int execution_time = (p[current_process].rt < tq) ? p[current_process].rt : tq;
        
        // Update current time
        current_time += execution_time;
        
        // Reduce remaining time
        p[current_process].rt -= execution_time;
        
        // Add new processes that have arrived to the queue
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= current_time && i != current_process) {
                int already_in_queue = 0;
                
                // Check if process is already in queue
                for (int j = front; j < rear; j++) {
                    if (queue[j] == i) {
                        already_in_queue = 1;
                        break;
                    }
                }
                
                // Add process to queue if not already present
                if (!already_in_queue) {
                    queue[rear] = i;
                    rear++;
                }
            }
        }
        
        // If process still has remaining time, add back to queue
        if (p[current_process].rt > 0) {
            queue[rear] = current_process;
            rear++;
        } 
        // Otherwise, mark process as completed
        else {
            completed++;
            p[current_process].ct = current_time;
            p[current_process].tat = p[current_process].ct - p[current_process].at;
            p[current_process].wt = p[current_process].tat - p[current_process].tbt;
        }
    }
    
    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                p[i].pid, p[i].at, p[i].tbt, p[i].ct, p[i].tat, p[i].wt);
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    
    // Calculate and print average turnaround and waiting times
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    
    return 0;
}