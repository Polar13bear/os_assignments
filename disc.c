#include <stdio.h>
#include <stdlib.h>
int main() {
    int n = 7;                           
    int disc_seq[200];                  
    int head;                            
    int tracks = 200;                    
    int distance = 0;                    
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the disk request sequence: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &disc_seq[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the total number of tracks: ");
    scanf("%d", &tracks);
    printf("\nInitial head position: %d\n", head);
    printf("\nHead movement sequence: %d", head);
    for(int i = 0; i < n; i++) {
        distance += abs(head - disc_seq[i]);
        head = disc_seq[i];
        printf(" -> %d", head);
    }
    printf("\n\nTotal head movement (distance): %d\n", distance);
    return 0;
}