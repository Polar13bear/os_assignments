#include <stdio.h>
#include <stdlib.h>
int main() {
    int n;                      
    int disc_seq[200];          
    int head;                   
    int tracks;                 
    int distance = 0;           
    int completed[200] = {0};   
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
    int current_head = head;
    int count = 0;
    printf("\nHead movement sequence: %d", current_head);
    while(count < n) {
        int min_distance = 1000;
        int min_index = -1;
        for(int i = 0; i < n; i++) {
            if(!completed[i]) {
                int current_distance = abs(current_head - disc_seq[i]);
                if(current_distance < min_distance) {
                    min_distance = current_distance;
                    min_index = i;
                }
            }
        }
        completed[min_index] = 1;
        distance += min_distance;
        current_head = disc_seq[min_index];
        printf(" -> %d", current_head);
        count++;
    }
    printf("\n\nTotal head movement (distance): %d\n", distance);
    return 0;
}