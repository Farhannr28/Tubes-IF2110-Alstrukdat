#ifndef ListLinearUtas_H
#define ListLinearUtas_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../utility/boolean.h"
typedef struct nodeUtas* AddressUtas;
typedef struct paragraph{
    DATETIME DateTime;
    Word text;
    struct paragraph* next;
} Paragraph;

typedef struct utasan{
    int IDKicauan;
    int IDUtasan;
    Word Penulis;
    Paragraph* TextList;
    int variable; 
} Utasan;

typedef struct nodeUtas {
    Utasan info;
    AddressUtas next;
} NodeUtas;

#define INFO(p) (p)->info
#define NEXT(p) (p)->next
#define IDUtasan(p) (p)->info.IDUtasan
#define Variable(p) (p)->info.variable
#define IDKicauan(p) (p)->info.IDKicauan
#define TEXT(p) (p)->info.TextList
#define KONTEN(p) (p)->text
#define CurrTime(p) (p)->DateTime

AddressUtas newNodeUtas(Utasan val);

/* Definisi ListLinearUtas : */
/* ListLinearUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan AddressUtas p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir ListLinearUtas: jika AddressUtasnya Last, maka NEXT(Last)=NULL */

typedef AddressUtas ListLinearUtas;
// typedef AddressUtas ListParagraf;

#define IDX_UNDEF (-1)
#define FIRST(l) (l)

/* PROTOTYPE */
/****************** PEMBUATAN ListLinearUtas KOSONG ******************/
void CreateListLinearUtas(ListLinearUtas *l);
/* I.S. sembarang             */
/* F.S. Terbentuk ListLinearUtas kosong */
// void CreateListParagraf(ListParagraf *l1);

/****************** TEST ListLinearUtas KOSONG ******************/
boolean isEmptyListLinearUtas(ListLinearUtas l);
/* Mengirim true jika ListLinearUtas kosong */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirstListLinearUtas(ListLinearUtas *l, Utasan val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */

void insertLastListLinearUtas(ListLinearUtas *l, Utasan val);
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListLinearUtas di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

int lengthListLinearUtas(ListLinearUtas l);
/* Mengirimkan banyaknya elemen ListLinearUtas; mengirimkan 0 jika ListLinearUtas kosong */
boolean isInList (ListLinearUtas l, int IDKicau);
#endif
