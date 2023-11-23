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

/* Define structur untuk graph */
typedef struct graph
{
    int simpul;                            // simpul = jumlah user
    int adjMatrix[MAX_SIMPUL][MAX_SIMPUL]; // adjacency matrix yg berisi pointer to integer untuk menyimpan hubungan pertemanan
} Graph;

/* Fungsi untuk membuat graph baru */
void createGraph(Graph *graph, int jumlahUser);

/* Fungsi untuk mengecek apakah user tidak ada teman (adjacency matrixnya 0)*/
boolean isNoTeman(Graph graph, int user_index);

/* Fungsi untuk mencek apakah ada hubungan pertemanan antara dua user */
boolean isTeman(Graph graph, int index_user_asal, int index_user_tujuan);

/* Fungsi untuk menghitunng jumlah teman yang dimiliki oleh suatu user */
int jumlahTeman(Graph graph, int user_index);

#endif
