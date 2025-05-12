#include<stdio.h>
struct process
{
    int pid;
    int at;
    int bt;
    int tat;
    int wt;
    int rt;
    int starttime;
    int ct;
};
void printganntchart(struct process p[], int n)
    {
        printf("Gannt chart:\n");
        printf(" ");
        for (int i = 0; i < n; i++)
        {
            printf(" | P%d",p[i].pid);
        }
         printf(" |\n");
         printf("0");
         for (int i = 0; i <n; i++)
         {
            printf("     %d",p[i].ct);
         }
         printf("\n");       
    }
int main(int argc, char const *argv[])
{
    int n;
    printf("Enter the number of processes: \n ");
    scanf("%d",&n);
    float total_tat = 0,total_wt = 0;
    struct process p[n];
    printf("Enter the process id's:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&p[i].pid);
    }
    printf("Enter the arrival times of processes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&p[i].at);
    }
    printf("Enter the burst times of processes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&p[i].bt);
    }
    // Sort processes by arrival time
    for (int i = 0; i < n-1; i++)
    {
        for (int j= 0; j< n-i-1; j++)
        {
            if (p[j].at > p[j+1].at)
            {
                struct process temp;
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
            
        }
        
    }
    
    for (int i = 0; i <n; i++)
    {
        if (i==0)
        {
            p[i].starttime = p[i].at;
        }
        else{
            if (p[i-1].ct < p[i].at)
            {
                p[i].starttime  = p[i].at;    
            }
            if (p[i-1].ct == p[i].at)
            {
                p[i].starttime  = p[i].at;    
            }
            if (p[i-1].ct > p[i].at)
            {
                p[i].starttime  = p[i-1].ct;    
            }
        }
        p[i].ct = p[i].starttime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;   
    }
    float sl = p[n-1].ct - p[0].at;
    float throughput = n/sl;
    printganntchart(p,n);
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Schedule Length is:%.2f\n",sl);
    printf("Throughput is:%.2f\n",throughput);

    return 0;
}