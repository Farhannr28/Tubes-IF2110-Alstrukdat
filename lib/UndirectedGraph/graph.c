/* ADT Undirected Graph dengan adjacency matrix yang berfungsi untuk menyatakan hubungan pertemanan sautu user dengan user lainnya */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
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
void createGraph(Graph *graph, int jumlahUser)
{
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

void sendRequest(Graph *graph, int index_user_asal, int index_user_tujuan)
{
    ELMT_GRAPH(*graph, index_user_asal, index_user_tujuan) = 1;
}

void GraphFromWord(Graph *graph, Word w) {
    // I.S assuming kalau misalnya m ini fixed size dan input selalu bener
    createGraph(graph, 20);
    int i = 0;
    int j = 0;

    int wordIdx = 0;
    while (wordIdx < w.Length) {
        if(w.TabWord[wordIdx] == '\n') {
            j = 0;
            i++;
        } else {
            if(w.TabWord[i] >= '0' && w.TabWord[i] <= '9') {
                ELMT_GRAPH(*graph, i, j) = w.TabWord[wordIdx] - '0';
                j++;
            }
        } 
        wordIdx++;
    }
}
