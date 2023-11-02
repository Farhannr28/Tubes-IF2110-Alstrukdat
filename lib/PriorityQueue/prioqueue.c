#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../UndirectedGraph/graph.h"

/* Selektor */
#define DATA(p) (p)->user
#define NEXT_QUEUE(p) (p)->next
#define PRIORITY(p) (p)->priority
#define FIRST_QUEUE(l) (l) // Buat ambil node dari list l

/* Address = Pointer to Node */
typedef struct node *Address;

/* Node = Element dari Priority Queue Linked List */
typedef struct node
{
    User user;
    int priority;
    struct node *next;
} Node;

/* List = Address (Elemen pertama queue) */
typedef Address List;

/* Buat convert data user ke node */
Address newNode(User user)
{
    Address temp = (Address)malloc(sizeof(Node));
    if (temp != NULL)
    {
        DATA(temp) = user;
        PRIORITY(temp) = FOLLOWER(user);
        NEXT_QUEUE(temp) = NULL;
    }
    return temp;
}

/* Buat Priority Queue*/
void CreateList(List *l)
{
    FIRST_QUEUE(*l) = NULL;
}

/* Cek apakah queue kosong*/
boolean isEmpty(List l)
{
    return (FIRST_QUEUE(l) == NULL);
}

/* Fungsi untuk hapus elemen/node dengan prioritas tertinggi*/
void dequeue(List *l)
{
    Address temp = FIRST_QUEUE(*l);
    FIRST_QUEUE(*l) = NEXT_QUEUE(FIRST_QUEUE(*l));
    free(temp);
}

/* Fungsi untuk menambahkan node*/
void enqueue(List *l, User user, int follower)
{
    Address start = FIRST_QUEUE(*l);

    /* Convert data user ke node */
    Address temp = newNode(user);

    /* Case 1: Jika list kosong*/
    if (FIRST_QUEUE(*l) == NULL)
    {
        NEXT_QUEUE(temp) = FIRST_QUEUE(*l);
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

int length_queue(List l)
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

/* Fungsi baut ngecek apakah ada pending request */
boolean isNoPendingRequest(User user)
{
    boolean empty = true;
    for (int i = 0; i < MAX_SIMPUL; i++)
    {
        if (PENDING_REQUEST(user, i) == 1)
        {
            empty = false;
        }
    }
    return empty;
}

/* Fungsi buat ngirim request pertemanan*/
void sendRequest(Graph *graph, User *user_asal, User *user_tujuan)
{
    /* Cek jika ada pending request sebelumnya atau tidak */
    if (!isNoPendingRequest(*user_asal))
    {
        printf("Terdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n");
        return;
    }
    else
    {
        /* Jika ngirim freind request ke diri sendiri */
        if (INDEX_USER(*user_asal) == INDEX_USER(*user_tujuan))
        {
            printf("Kamu tidak bisa mengirim request ke diri sendiri.\n");
            return;
        }
        else
        {
            /* Case 1 : Jika sudah berteman dengan user tertentu*/
            if (isTeman(*graph, INDEX_USER(*user_asal), INDEX_USER(*user_tujuan)))
            {
                printf("Anda sudah bertemean dengan %s\n.", nameOfUser[INDEX_USER(*user_tujuan)]);
                return;
            }
            /* Case 2 : Jika sudah ngirim request ke user tertentu */
            else if (REQUEST(*user_asal, INDEX_USER(*user_tujuan)) == 1)
            {
                printf("Anda sudah mengirimkan permintaan pertemanan kepada %s. Silakan tunggu hingga permintaan Anda disetujui\n.", nameOfUser[INDEX_USER(*user_tujuan)]);
                return;
            }
            /* Case 3 : Jika belum ngirim request sama sekali ke user tertentu */
            else
            {
                REQUEST(*user_asal, INDEX_USER(*user_tujuan)) = 1;
                PENDING_REQUEST(*user_tujuan, INDEX_USER(*user_asal)) = 1;
                printf("Permintaan pertemanan kepada %s telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n", nameOfUser[INDEX_USER(*user_tujuan)]);
                return;
            }
        }
    }
}

/* Fungsi buat nge cancel request pertemanan*/
void cancelRequest(User *user_asal, User *user_tujuan)
{
    /* Case 1 : Jika belum ada ngirim pertemanan ke user tertentu */
    if (REQUEST(*user_asal, INDEX_USER(*user_tujuan)) == 0)
    {
        printf("Anda belum mengirimkan permintaan pertemanan kepada %s.\n", nameOfUser[INDEX_USER(*user_tujuan)]);
    }
    /* Case 2: Jika benar ada udah ngirim request ke user tertentu */
    else
    {
        REQUEST(*user_asal, INDEX_USER(*user_tujuan)) = 0;
        PENDING_REQUEST(*user_tujuan, INDEX_USER(*user_asal)) = 0;
        printf("Permintaan pertemanan kepada %s telah dibatalkan.\n", nameOfUser[INDEX_USER(*user_tujuan)]);
    }
}

/* Fungsi untuk nyari jumlah pending request yang ada */
int jumlahPendingRequest(User user)
{
    int jumlah = 0;
    for (int i = 0; i < MAX_SIMPUL; i++)
    {
        if (PENDING_REQUEST(user, i) == 1)
        {
            jumlah++;
        }
    }
    return jumlah;
}

/* Fungsi buat print daftar teman yang ada */
void daftarPermintaanTeman(User user)
{
    List listRequest;
    CreateList(&listRequest);
    /* Case 1 : Jika ga ada request pertemanan */
    if (isNoPendingRequest(user))
    {
        printf("Tidak ada permintaan pertemanan untuk Anda.\n");
        return;
    }
    /* Case 2 : Jika ada request */
    else
    {
        printf("Terdapat %d permintaan pertemanan untuk Anda.\n", jumlahPendingRequest(user));
        for (int i = 0; i < MAX_SIMPUL; i++)
        {
            if (PENDING_REQUEST(user, i) == 1)
            {
                enqueue(&listRequest, listOfUser[i], FOLLOWER(listOfUser[i]));
            }
        }
        printf("\n");
        while (!isEmpty(listRequest))
        {
            printf("| %s\n", nameOfUser[INDEX_USER(DATA(FIRST_QUEUE(listRequest)))]);
            printf("| Jumlah Teman: %d \n\n", FOLLOWER(DATA(FIRST_QUEUE(listRequest))));
            dequeue(&listRequest);
        }
    }
}

/* Fungsi buat menerima request pertemanan */
void acceptRequest(Graph *graph, User *user_asal, User *user_tujuan)
{
    if (PENDING_REQUEST(*user_asal, INDEX_USER(*user_tujuan)) == 0)
    {
        printf("Anda belum menerima permintaan pertemanan dari %s.\n", nameOfUser[INDEX_USER(*user_tujuan)]);
    }
    else
    {
        addTeman(graph, INDEX_USER(*user_asal), INDEX_USER(*user_tujuan));
        REQUEST(*user_tujuan, INDEX_USER(*user_asal)) = 0;
        PENDING_REQUEST(*user_asal, INDEX_USER(*user_tujuan)) = 0;
        printf("Permintaan pertemanan dari %s telah disetujui. Selamat! Anda telah berteman dengan %s.\n", nameOfUser[INDEX_USER(*user_tujuan)], nameOfUser[INDEX_USER(*user_tujuan)]);
    }
}

/* Fungsi buat request nolak pertemanan */
void declineRequest(User *user_asal, User *user_tujuan)
{
    if (PENDING_REQUEST(*user_asal, INDEX_USER(*user_tujuan)) == 0)
    {
        printf("Anda belum menerima permintaan pertemanan dari %s.\n", nameOfUser[INDEX_USER(*user_tujuan)]);
    }
    else
    {
        REQUEST(*user_tujuan, INDEX_USER(*user_asal)) = 0;
        PENDING_REQUEST(*user_asal, INDEX_USER(*user_tujuan)) = 0;
        printf("Permintaan pertemanan dari %s telah ditolak.\n", nameOfUser[INDEX_USER(*user_tujuan)]);
    }
}