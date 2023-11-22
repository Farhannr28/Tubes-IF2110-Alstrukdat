/* ADT Undirected Graph dengan adjacency matrix yang berfungsi untuk menyatakan hubungan pertemanan sautu user dengan user lainnya */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/boolean.h"
/*Max user hanya 20, maka jumlah teman max hanya 19 (dibulatkan ke 20). */
#define MAX_SIMPUL 20

/* Selektor */
#define SIMPUL(p) (p).simpul
#define ELMT_GRAPH(p, i, j) (p).adjMatrix[i][j] // Baris = user asal, kolom = user tujuan
// #define NAME_USER(p) (p).name
// #define INDEX_USER(p) (p).userIndex
// #define FOLLOWER(p) (p).follower
// #define REQUEST(p, i) (p).request[i]
// #define PENDING_REQUEST(p, i) (p).pendingRequest[i]

/* Define structur untuk graph */
typedef struct graph
{
    int simpul;                            // simpul = jumlah user
    int adjMatrix[MAX_SIMPUL][MAX_SIMPUL]; // adjacency matrix yg berisi pointer to integer untuk menyimpan hubungan pertemanan
} Graph;

// /* Define structur untuk user */
// typedef struct user
// {
//     char name[20];
//     int userIndex;
//     int follower;
//     int request[20];
//     int pendingRequest[20];
// } User;

/* Define array of user index ( 0 berarti masih belum keisi ) */
// char nameOfUser[MAX_SIMPUL][20]; // Baris = user asal, kolom = panjang kata max
// int indexOfUser[MAX_SIMPUL] = {0};
// User listOfUser[MAX_SIMPUL];

/* Fungsi untuk membuat graph baru */
void createGraph(Graph *graph, int jumlahUser)
{
    int i, j;
    SIMPUL(*graph) = jumlahUser;

    for (int i = 0; i < jumlahUser; i++)
    {
        for (int j = 0; j < jumlahUser; j++)
        {
            ELMT_GRAPH(*graph, i, j) = 0;
        }
    }
}

/* Fungsi untuk mengecek apakah user tidak ada teman (adjacency matrixnya 0)*/
boolean isNoTeman(Graph graph, int user_index)
{
    int j;
    boolean empty = true;
    for (j = 0; j < MAX_SIMPUL; j++)
    {
        if (ELMT_GRAPH(graph, user_index, j) == 1)
        {
            empty = false;
        }
    }
    return empty;
}

/* Fungsi untuk mencek apakah ada hubungan pertemanan antara dua user */
boolean isTeman(Graph graph, int index_user_asal, int index_user_tujuan)
{
    if (ELMT_GRAPH(graph, index_user_asal, index_user_tujuan) == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/* Fungsi untuk menghitunng jumlah teman yang dimiliki oleh suatu user */
int jumlahTeman(Graph graph, int user_index)
{
    int j, jumlah = 0;
    for (j = 0; j < MAX_SIMPUL; j++)
    {
        if (ELMT_GRAPH(graph, user_index, j) == 1)
        {
            jumlah++;
        }
    }
    return jumlah;
}
// /* Fungsi baut ngecek apakah user sudah penuh */
// boolean isUserFull(int indexOfUser[])
// {
//     for (int i = 0; i < MAX_SIMPUL; i++)
//     {
//         if (indexOfUser[i] == 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }

// /* Fungsi untuk membuat freindlist user */
// void createUser(User *newUser, char name[20], int follower)
// {
//     if (isUserFull(indexOfUser))
//     {
//         printf("User sudah penuh\n");
//         return;
//     }
//     else
//     {
//         int i;
//         strncpy(NAME_USER(*newUser), name, sizeof(NAME_USER(*newUser))); // NB : INI HARUS DIGANTI KE COPYWORD MESIN KATA
//         for (i = 0; i < MAX_SIMPUL; i++)
//         {
//             if (indexOfUser[i] == 0)
//             {
//                 INDEX_USER(*newUser) = i;
//                 indexOfUser[i] = 1;
//                 strncpy(nameOfUser[i], name, sizeof(nameOfUser[i])); // NB : INI HARUS DIGANTI KE COPYWORD MESIN KATA
//                 FOLLOWER(*newUser) = follower;
//                 listOfUser[i] = *newUser;
//                 for (int j = 0; j < MAX_SIMPUL; j++)
//                 {
//                     REQUEST(*newUser, j) = 0;
//                     PENDING_REQUEST(*newUser, j) = 0;
//                 }
//                 break; // Break agar ga lanjut nge loop
//             }
//         }
//     }
// }

