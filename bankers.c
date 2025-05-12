#include<stdio.h>
#define max 10
int main(int argc, char const *argv[]) {
    int ns, np;
    int i, j, k = 0;
    int flag;
    int allocation[max][max], maximum[max][max], need[max][max];
    int available[max], finish[max], safeseq[max], availability[max];
    printf("Enter the number of processes:\n");
    scanf("%d", &np);
    printf("Enter the number of resources:\n");
    scanf("%d", &ns);
    for (i = 0; i < np; i++) finish[i] = 0;
    printf("Enter the allocation matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < ns; j++)
            scanf("%d", &allocation[i][j]);
    printf("Enter the maximum matrix:\n");
    for (i = 0; i < np; i++)
        for (j = 0; j < ns; j++)
            scanf("%d", &maximum[i][j]);
    printf("Enter the available resources:\n");
    for (i = 0; i < ns; i++) {
        scanf("%d", &available[i]);
        availability[i] = available[i]; 
    }
    for (i = 0; i < np; i++)
        for (j = 0; j < ns; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
    printf("\nProcess\tAllocation\tMaximum\t\tNeed\n");
    for (i = 0; i < np; i++) {
        printf("P%d\t", i);
        for (j = 0; j < ns; j++)
            printf("%d ", allocation[i][j]);
        printf("\t\t");
        for (j = 0; j < ns; j++)
            printf("%d ", maximum[i][j]);
        printf("\t\t");
        for (j = 0; j < ns; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("\nAvailable Resources: ");
    for (i = 0; i < ns; i++)
        printf("%d ", available[i]);
    printf("\n");
    k = 0; 
    while (k < np) {
        flag = 0;
        for (i = 0; i < np; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < ns; j++) {
                    if (need[i][j] > availability[j])
                        break;
                }
                if (j == ns) {
                    for (j = 0; j < ns; j++)
                        availability[j] += allocation[i][j];
                    safeseq[k++] = i;
                    finish[i] = 1;
                    flag = 1;
                    break; 
                }
            }
        }
        if (flag == 0) {
            if (k < np) { 
                printf("\nDeadlock occurred. No safe sequence.\n");
                return 0;
            }
            break;
        }
    }
    printf("\nSafe Sequence: ");
    for (i = 0; i < k; i++)
    printf("P%d ", safeseq[i]);
    printf("\n");
    return 0;
}