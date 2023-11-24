/* MODUL STACK */

#ifndef STACK_H
#define STACK_H

#include "../utility/boolean.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/datetime.h"

#define Nil -1 /* Nil adalah stack dengan elemen kosong */
#define MaxEl 20 /* Asumsi Draf tidak akan mencapai 20 */

typedef struct drafKicau {
    Word text;
    DATETIME waktu;
} DrafKicau;

typedef DrafKicau infotype;
typedef int address;
typedef struct { 
  infotype T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* SELEKTOR */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* Konstruktor DrafKicau */
void CreateDrafKicau(DrafKicau *D, Word text, DATETIME date);

/* Menampilkan Elemen stack */
void DisplayDrafKicau(DrafKicau D);

/* Konstruktor Stack */
void CreateStack(Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */

/* Mengirim true jika Stack kosong */
boolean IsEmptyStack(Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
boolean IsFullStack(Stack S);

/* Menambahkan X sebagai elemen Stack S. */
void Push(Stack * S, infotype X);
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* Menghapus X dari Stack S. */
void Pop(Stack * S, infotype* X);
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif