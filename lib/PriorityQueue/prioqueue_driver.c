#include <stdio.h>
#include <stdlib.h>
#include "prioqueue.h" 

int main() {

    int choice;
    printf("1. Cek jika Queue Kosong\n");
    printf("2. Dequeue\n");
    printf("3. Enqueue\n");
    printf("4. Length Queue\n");
    printf("Masukkan input: \n");
    scanf("%d", &choice);

    Word nama;
    int priority;
    switch(choice) {
        case 1:
            PriorityQueue queue;
            CreatePriorityQueue(&queue);
            boolean empty = isEmpty(queue);
            if(empty) {
                printf("Queue is empty.\n");
            } else {
                printf("Queue is not empty.\n");
            }
            break;
        case 2:
            PriorityQueue queue;
            CreatePriorityQueue(&queue);
            Word nama;
            int priority = 99;
            Word nama2;
            int priority2 = 95;
            Word nama3;
            int priority3 = 90;
            AssignWord(&nama, "Dummy");
            AssignWord(&nama, "Dummy2");
            AssignWord(&nama, "Dummy3");
            printf("Sebelum enqueue\n");
            printf("%d\n", lengthQueue(queue));
            enqueue(&queue, nama, priority);
            enqueue(&queue, nama2, priority3);
            enqueue(&queue, nama3, priority3);
            printf("Setelah enqueue\n");
            printf("%d\n", lengthQueue(queue));
            dequeue(&queue);
            printf("Setelah dequeue\n");
            printf("%d\n", lengthQueue(queue));
            dequeue(&queue);
            Address p = FIRST_QUEUE(queue);
            while(p != NULL) {
                printf("%s %d\n", DATA(p), PRIORITY(p));
                p = NEXT_QUEUE(p);
            }
            printf("Setelah dequeue\n");
            printf("%d\n", lengthQueue(queue));
            break;
        case 3:
            PriorityQueue queue;
            CreatePriorityQueue(&queue);
            Word nama;
            int priority = 99;
            Word nama2;
            int priority2 = 95;
            Word nama3;
            int priority3 = 90;
            AssignWord(&nama, "Dummy");
            AssignWord(&nama, "Dummy2");
            AssignWord(&nama, "Dummy3");
            enqueue(&queue, nama, priority);
            enqueue(&queue, nama2, priority3);
            enqueue(&queue, nama3, priority3);
            Address p = FIRST_QUEUE(queue);
            while(p != NULL) {
                printf("%s %d\n", DATA(p), PRIORITY(p));
                p = NEXT_QUEUE(p);
            }
            break;
        case 4:
            PriorityQueue queue;
            CreatePriorityQueue(&queue);
            Word nama;
            int priority = 99;
            Word nama2;
            int priority2 = 95;
            Word nama3;
            int priority3 = 90;
            AssignWord(&nama, "Dummy");
            AssignWord(&nama, "Dummy2");
            AssignWord(&nama, "Dummy3");
            printf("Sebelum enqueue\n");
            printf("%d\n", lengthQueue(queue));
            enqueue(&queue, nama, priority);
            enqueue(&queue, nama2, priority3);
            enqueue(&queue, nama3, priority3);
            printf("Setelah enqueue\n");
            printf("%d\n", lengthQueue(queue));
            break;
    }

    return 0;
}