/* ADT Undirected Graph dengan adjacency matrix yang berfungsi untuk menyatakan hubungan pertemanan sautu user dengan user lainnya */
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/boolean.h"
/*Max user hanya 20, maka jumlah teman max hanya 19 (dibulatkan ke 20). */
#define MAX_SIMPUL 20

/* Selektor */
#define SIMPUL(p) (p).simpul
#define ELMT_GRAPH(p, i, j) (p).adjMatrix[i][j] // Baris = user asal, kolom = user tujuan
#define NAME_USER(p) (p).name
#define INDEX_USER(p) (p).userIndex
#define FOLLOWER(p) (p).follower
#define REQUEST(p, i) (p).request[i]
#define PENDING_REQUEST(p, i) (p).pendingRequest[i]

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
char nameOfUser[MAX_SIMPUL][20]; // Baris = user asal, kolom = panjang kata max
User listOfUser[MAX_SIMPUL];

/* Fungsi untuk membuat graph baru */
void createGraph(Graph *graph, int jumlahUser);

/* Fungsi untuk membuat freindlist user */
void createUser(User *newUser, char name[20], int follower);

/* Fungsi untuk mengecek apakah user tidak ada teman (adjacency matrixnya 0)*/
boolean isNoTeman(Graph graph, int user_index);

/* Fungsi untuk mencek apakah ada hubungan pertemanan antara dua user */
boolean isTeman(Graph graph, int index_user_asal, int index_user_tujuan);

/* Fungsi untuk menghitunng jumlah teman yang dimiliki oleh suatu user */
int jumlahTeman(Graph graph, int user_index);

/* Fungsi untuk menambahkan edge/sisi (hubungan pertemanan) pada graph */
void addTeman(Graph *graph, int index_user_asal, int index_user_tujuan);

/* Fungsi untuk menghapus teman */
void hapusTeman(Graph *graph, int index_user_asal, int index_user_tujuan);

/* Fungsi untuk mencetak daftar teman */
void printTeman(Graph graph, User user, int user_index);

#endif