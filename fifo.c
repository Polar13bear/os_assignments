#include <stdio.h>
#define fmax 10
#define pmax 30
int main() {
    int nf, np;
    int i, j, k= 0;
    int fault = 0, hit = 0;
    int flag;
    int f[fmax], p[pmax];
    printf("Enter the number of pages:\n");
    scanf("%d", &np);
    printf("Enter the number of frames:\n");
    scanf("%d", &nf);
    for (j = 0; j < nf; j++) {
        f[j] = -1;
    }
    printf("Enter the page sequence:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &p[i]);
    }
    printf("\nFrame\t");
    for (j = 0; j < nf; j++) {
        printf("F%d\t", j);
    }
    printf("Status\n");
    for (i = 0; i < np; i++) {
        flag = 0;
        for (j = 0; j < nf; j++) {
            if (p[i] == f[j]) {
                hit++;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            f[k] = p[i];
            fault++;
            k = (k + 1) % nf;
        }
        printf("%d\t", p[i]);
        for (j = 0; j < nf; j++) {
            printf("%d\t", f[j]);
        }
        if (flag)
            printf("Hit\n");
        else
            printf("Miss\n");
    }
    printf("\nTotal Page Faults: %d\n", fault);
    printf("Total Page Hits: %d\n", hit);
    printf("Hit Ratio: %.2f\n", (float)hit / np);
    printf("Miss Ratio: %.2f\n", (float)fault / np);
    return 0;
}
