/* File : ListLinearUtaslinier.h */
/* contoh ADT ListLinearUtas berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* ElType adalah integer */

#ifndef ListLinearUtaslinier_H
#define ListLinearUtaslinier_H

#include "boolean.h"
#include "wordmachine.h"
#include "charmachine.h"
/* Definisi Node : */
// typedef int ElType;
typedef struct node* Address;
typedef struct ulasan{
    int IDUlasan;
    Word Penulis;
    //Ada datetime;
    int variable; 
} Ulasan;

typedef struct node {
    Ulasan info;
    Address next;
} Node;


#define INFO(p) (p)->info
#define NEXT(p) (p)->next
#define IDUlasan(p) (p)->info.IDUlasan
#define Variable(p) (p)->info.variable

Address newNode(Ulasan val);

/* Definisi ListLinearUtas : */
/* ListLinearUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir ListLinearUtas: jika addressnya Last, maka NEXT(Last)=NULL */

typedef Address ListLinearUtas;

#define IDX_UNDEF (-1)
#define FIRST(l) (l)

/* PROTOTYPE */
/****************** PEMBUATAN ListLinearUtas KOSONG ******************/
void CreateListLinearUtas(ListLinearUtas *l);
/* I.S. sembarang             */
/* F.S. Terbentuk ListLinearUtas kosong */

/****************** TEST ListLinearUtas KOSONG ******************/
boolean isEmptyListLinearUtas(ListLinearUtas l);
/* Mengirim true jika ListLinearUtas kosong */

int indexOfListLinearUtas(ListLinearUtas l, int IdxUlasan);
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen ListLinearUtas l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstListLinearUtas(ListLinearUtas *l, Ulasan val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLastListLinearUtas(ListLinearUtas *l, Ulasan val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListLinearUtas di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void insertAtListLinearUtas(ListLinearUtas *l, Ulasan val, int idx);
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam ListLinearUtas pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirstListLinearUtas(ListLinearUtas *l);
/* I.S. ListLinearUtas l tidak kosong  */
/* F.S. Elemen pertama ListLinearUtas dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
void deleteLastListLinearUtas(ListLinearUtas *l);
/* I.S. ListLinearUtas tidak kosong */
/* F.S. Elemen terakhir ListLinearUtas dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */

void deleteAtListLinearUtas(ListLinearUtas *l, int idx);
/* I.S. ListLinearUtas tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */


/****************** PROSES SEMUA ELEMEN ListLinearUtas ******************/
void displayListLinearUtas(ListLinearUtas l);
// void printInfo(ListLinearUtas l);
/* I.S. ListLinearUtas mungkin kosong */
/* F.S. Jika ListLinearUtas tidak kosong, iai ListLinearUtas dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika ListLinearUtas kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

int lengthListLinearUtas(ListLinearUtas l);
/* Mengirimkan banyaknya elemen ListLinearUtas; mengirimkan 0 jika ListLinearUtas kosong */

void createUlasan(int IDUlasan, int variable, Ulasan *u);

#endif