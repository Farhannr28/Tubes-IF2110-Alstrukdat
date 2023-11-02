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
Address newNode(User user);

/* Buat Priority Queue*/
void CreateList(List *l);

/* Cek apakah queue kosong*/
boolean isEmpty(List l);

/* Fungsi untuk hapus elemen/node dengan prioritas tertinggi*/
void dequeue(List *l);

/* Fungsi untuk menambahkan node*/
void enqueue(List *l, User user, int follower);

/* Buat nyari berapa banyak user yang ada */
int length_queue(List l);

/* Fungsi baut ngecek apakah ada pending request */
boolean isNoPendingRequest(User user);

/* Fungsi buat ngirim request pertemanan*/
void sendRequest(Graph *graph, User *user_asal, User *user_tujuan);
/* Fungsi buat nge cancel request pertemanan*/
void cancelRequest(User *user_asal, User *user_tujuan);

/* Fungsi untuk nyari jumlah pending request yang ada */
int jumlahPendingRequest(User user);

/* Fungsi buat print daftar teman yang ada */
void daftarPermintaanTeman(User user);

/* Fungsi buat menerima request pertemanan */
void acceptRequest(Graph *graph, User *user_asal, User *user_tujuan);

/* Fungsi buat request nolak pertemanan */
void declineRequest(User *user_asal, User *user_tujuan);