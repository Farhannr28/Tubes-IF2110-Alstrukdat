#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../MesinKata/wordmachine.h"
#include "../UndirectedGraph/graph.h"
#include "prioqueue.h"

/* Buat convert data user ke node */
Address newNode(Word nama, int priority)
{
    Address temp = (Address)malloc(sizeof(PriorityQueueNode));
    if (temp != NULL)
    {
        DATA(temp) = nama;
        PRIORITY(temp) = priority;
        NEXT_QUEUE(temp) = NULL;
    }
    return temp;
}

/* Buat Priority Queue*/
void CreatePriorityQueue(PriorityQueue *l)
{
    FIRST_QUEUE(*l) = NULL;
}

/* Cek apakah queue kosong*/
boolean isEmpty(PriorityQueue l)
{
    return (FIRST_QUEUE(l) == NULL);
}

/* Fungsi untuk hapus elemen/node dengan prioritas tertinggi*/
void dequeue(PriorityQueue *l)
{
    Address temp = FIRST_QUEUE(*l);
    FIRST_QUEUE(*l) = NEXT_QUEUE(FIRST_QUEUE(*l));
    free(temp);
}

/* Fungsi untuk menambahkan node*/
void enqueue(PriorityQueue *l, Word nama, int follower)
{
    Address start = FIRST_QUEUE(*l);

    /* Convert data user ke node */
    Address temp = newNode(nama, follower);

    /* Case 1: Jika list kosong*/
    if (FIRST_QUEUE(*l) == NULL)
    {
        FIRST_QUEUE(*l) = temp;
    }
    /* Case 2 : Jika elemen pertama memiliki prioritas lebih kecil dari user yang akan diinput*/
    else if (PRIORITY(FIRST_QUEUE(*l)) < follower)
    {
        // Insert New Node before head
        NEXT_QUEUE(temp) = FIRST_QUEUE(*l);
        FIRST_QUEUE(*l) = temp;
    }
    /* Case 3 : Mencari posisi yang pas untuk node baru, perlu dilakukan looping */
    else
    {

        while (NEXT_QUEUE(start) != NULL && PRIORITY(NEXT_QUEUE(start)) > follower)
        {
            start = NEXT_QUEUE(start);
        }

        /* Node akan diinput diakhir atau di posisi yang sesuai */
        NEXT_QUEUE(temp) = NEXT_QUEUE(start);
        NEXT_QUEUE(start) = temp;
    }
}

int length_queue(PriorityQueue l)
{
    int count = 0;
    Address temp = FIRST_QUEUE(l);
    while (temp != NULL)
    {
        count++;
        temp = NEXT_QUEUE(temp);
    }
    return count;
}