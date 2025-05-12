#include <stdio.h>
int main() {
    int np, nf;
    int i, j, loc;
    int tmin, fault = 0, count = 0, flag1, flag2, hit = 0;
    printf("Enter the number of pages:\n");
    scanf("%d", &np);
    printf("Enter the number of frames:\n");
    scanf("%d", &nf);
    int p[np], f[nf], time[nf];
    printf("Enter the page sequence:\n");
    for (i = 0; i < np; i++) {
        scanf("%d", &p[i]);
    }
    for (j = 0; j < nf; j++) {
        f[j] = -1;
        time[j] = 0;
    }
    printf("\nPage\tFrames\t\tStatus\n");
    for (i = 0; i < np; i++) {
        flag1 = flag2 = 0;
        for (j = 0; j < nf; j++) {
            if (f[j] == p[i]) {
                count++;
                time[j] = count;
                flag1 = flag2 = 1;
                hit++;
                break;
            }
        }
        if (!flag1) {
            for (j = 0; j < nf; j++) {
                if (f[j] == -1) {
                    f[j] = p[i];
                    count++;
                    time[j] = count;
                    fault++;
                    flag2 = 1;
                    break;
                }
            }
        }
        if (!flag2) {
            tmin = time[0];
            loc = 0;
            for (j = 1; j < nf; j++) {
                if (time[j] < tmin) {
                    tmin = time[j];
                    loc = j;
                }
            }
            f[loc] = p[i];
            count++;
            time[loc] = count;
            fault++;
        }
        printf("%d\t", p[i]);
        for (j = 0; j < nf; j++) {
            if (f[j] != -1)
                printf(" %d ", f[j]);
            else
                printf(" -1 ");
        }
        if (flag1)
            printf("\tHit\n");
        else
            printf("\tMiss\n");
    }
    printf("\nTotal Page Faults: %d\n", fault);
    printf("Total Page Hits: %d\n", hit);
    printf("Hit Ratio: %.2f\n", (float)hit / np);
    printf("Miss Ratio: %.2f\n", (float)fault / np);
    return 0;
}
