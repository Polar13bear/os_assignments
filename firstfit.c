#include <stdio.h>
int main() {
    int np, nb;
    printf("Enter the number of processes:\n");
    scanf("%d", &np);
    printf("Enter the number of blocks:\n");
    scanf("%d", &nb);
    int p[np]; 
    int b[nb]; 
    int bf[nb]; 
    int bn[np]; 
    int frag[np]; 
    printf("Enter the size of processes:\n");
    for (int i = 0; i < np; i++) {
        printf("p[%d]:", i+1);
        scanf("%d", &p[i]);
        bn[i] = -1;  
        frag[i] = 0;
    }
    printf("Enter the size of blocks:\n");
    for (int i = 0; i < nb; i++) {
        printf("b[%d]:", i+1);
        scanf("%d", &b[i]);
        bf[i] = 0;  
    }
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {
                bn[i] = j;
                frag[i] = b[j] - p[i];
                bf[j] = 1;
                break;
            }
        }
    }
    printf("\nProcess No\tProcess Size\tBlock No\tBlock Size\tFragment\n");
    for (int i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i+1, p[i]);
        if (bn[i] != -1) {
            printf("%d\t\t%d\t\t%d\n", bn[i]+1, b[bn[i]], frag[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
    return 0;
}