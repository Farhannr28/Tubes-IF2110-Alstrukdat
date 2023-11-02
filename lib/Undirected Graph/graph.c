/* ADT Undirected Graph dengan adjacency matrix yang berfungsi untuk menyatakan hubungan pertemanan sautu user dengan user lainnya */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/boolean.h"
/*Max user hanya 20, maka jumlah teman max hanya 19 (dibulatkan ke 20). */
#define MAX_SIMPUL 20

/* Selektor */
#define SIMPUL(p) (p).simpul
#define ELMT(p, i, j) (p).adjMatrix[i][j] // Baris = user asal, kolom = user tujuan
#define NAME(p) (p).name
#define INDEX_USER(p) (p).userIndex
#define FOLLOWER(p) (p).follower
#define REQUEST(p) (p).request
#define PENDING_REQUEST(p) (p).pendingRequest

/* Define structur untuk graph */
typedef struct graph
{
    int simpul;                            // simpul = jumlah user
    int adjMatrix[MAX_SIMPUL][MAX_SIMPUL]; // adjacency matrix yg berisi pointer to integer untuk menyimpan hubungan pertemanan
} Graph;

/* Define structur untuk user */
typedef struct user
{
    char name[20];
    int userIndex;
    int follower;
    int request[20];
    int pendingRequest[20];
} User;

/* Define array of user index ( 0 berarti masih belum keisi ) */
int indexOfUser[MAX_SIMPUL] = {0};
char nameOfUser[MAX_SIMPUL][20]; // Baris = user asal, kolom = panjang kata max

/* Fungsi untuk membuat graph baru */
void createGraph(Graph *graph, int jumlahUser)
{
    int i, j;
    SIMPUL(*graph) = jumlahUser;

    for (int i = 0; i < jumlahUser; i++)
    {
        for (int j = 0; j < jumlahUser; j++)
        {
            ELMT(*graph, i, j) = 0;
        }
    }
}

/* Fungsi untuk membuat freindlist user */
void createUser(User *newUser, char name[20], int follower)
{
    int i;
    strncpy(NAME(*newUser), name, sizeof(NAME(*newUser))); // NB : INI HARUS DIGANTI KE COPYWORD MESIN KATA
    for (i = 0; i < MAX_SIMPUL; i++)
    {
        if (indexOfUser[i] == 0)
        {
            INDEX_USER(*newUser) = i;
            indexOfUser[i] = 1;
            strncpy(nameOfUser[i], name, sizeof(nameOfUser[i])); // NB : INI HARUS DIGANTI KE COPYWORD MESIN KATA
            FOLLOWER(*newUser) = follower;
            for (int j = 0; j < MAX_SIMPUL; j++)
            {
                REQUEST(*newUser)
                [j] = 0;
                PENDING_REQUEST(*newUser)
                [j] = 0;
            }
            break;
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
        if (ELMT(graph, user_index, j) == 1)
        {
            empty = false;
        }
    }
    return empty;
}

/* Fungsi untuk mencek apakah ada hubungan pertemanan antara dua user */
boolean isTeman(Graph graph, int index_user_asal, int index_user_tujuan)
{
    if (ELMT(graph, index_user_asal, index_user_tujuan) == 1)
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
        if (ELMT(graph, user_index, j) == 1)
        {
            jumlah++;
        }
    }
    return jumlah;
}

/* Fungsi untuk menambahkan edge/sisi (hubungan pertemanan) pada graph */
void addTeman(Graph *graph, int index_user_asal, int index_user_tujuan)
{
    ELMT(*graph, index_user_asal, index_user_tujuan) = 1;
    ELMT(*graph, index_user_tujuan, index_user_asal) = 1;
}

/* Fungsi untuk menghapus teman */
void hapusTeman(Graph *graph, int index_user_asal, int index_user_tujuan)
{
    ELMT(*graph, index_user_asal, index_user_tujuan) = 0;
    ELMT(*graph, index_user_tujuan, index_user_asal) = 0;
}
/* Fungsi untuk mencetak daftar teman */
void printTeman(Graph graph, User user, int user_index)
{
    int j = 0;
    int temanUser = jumlahTeman(graph, user_index);
    if (temanUser == 0)
    {
        printf("%s tidak memiliki teman\n", NAME(user));
    }
    else
    {
        printf("%s memiliki %d teman\n", NAME(user), temanUser);
        printf("Daftar teman %s: \n", NAME(user));

        for (j = 0; j < MAX_SIMPUL; j++)
        {
            if (ELMT(graph, user_index, j) == 1)
            {
                printf("| %s \n", nameOfUser[j]);
            }
        }
    }
}