/* MODUL STACK */

#ifndef STACK_H
#define STACK_H

#include "../utility/boolean.h"
#include "../Kicauan/kicauan.h"

#define Nil -1 /* Nil adalah stack dengan elemen kosong */
#define MaxEl 100

typedef Kicauan infotype;
typedef int address;
typedef struct { 
  infotype T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* SELEKTOR */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* Konstruktor Stack */
void CreateEmpty(Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */

/* Mengirim true jika Stack kosong */
boolean IsEmpty(Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
boolean IsFull(Stack S);

/* Menambahkan X sebagai elemen Stack S. */
void Push(Stack * S, infotype X);
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* Menghapus X dari Stack S. */
void Pop(Stack * S, infotype* X);
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif