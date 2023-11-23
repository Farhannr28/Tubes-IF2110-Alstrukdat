#ifndef ListStatik_H
#define ListStatik_H

#include "../Matriks/matriks.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../PriorityQueue/prioqueue.h"
#include "../utility/boolean.h"
#include "../UndirectedGraph/graph.h"
#include "../Stack/stack.h"
#include "../Pengguna/pengguna.h"

/*  Kamus Umum */
#define CAPACITYListStatik 20
/* Kapasitas penyimpanan */
#define IDXMINListStatik 0
/* Indeks minimum list */
#define IDX_UNDEFListStatik -1
/* Indeks tak terdefinisi*/
#define MARKListStatik -9999
/* Nilai elemen tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef struct listStatikElType {
  union {
    Pengguna p;
  } content;
  boolean isValid;
} ListStatikElType;

typedef enum {
  PENGGUNA,
} ListStatikType;

typedef int ListStatikIdxType;

typedef struct {
  ListStatikElType elements[CAPACITYListStatik];
  ListStatikType type;
} ListStatik;

/* ********** SELEKTOR ********** */
#define ELMTStatik(l, i) (l).elements[(i)]
#define ELMTStatikContent(l, i) (l).elements[(i)].content

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStatik(ListStatik *l, ListStatikType type);
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITYListStatik */
/* Proses: Inisialisasi semua elemen List l dengan MARKListStatik */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int ListStatikLength(ListStatik l);
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */

/* *** Selektor INDEKS *** */
ListStatikIdxType getFirstIdxListStatik(ListStatik l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
ListStatikIdxType getLastIdxListStatik(ListStatik l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListStatik(ListStatik l, ListStatikIdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxEffListStatik(ListStatik l, ListStatikIdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListStatik(ListStatik l);
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isFullListStatik(ListStatik l);
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */

/* ********** OPERATOR ARITMATIKA ********** */
/* ********** NILAI EKSTREM ********** */
void insertFirstListStatik(ListStatik *l, ListStatikElType el);
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
/* *** Menambahkan elemen pada index tertentu *** */
void insertAtListStatik(ListStatik *l, ListStatikElType el, ListStatikIdxType idx);
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l
 */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
void insertLastListStatik(ListStatik *l, ListStatikElType user);
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirstListStatik(ListStatik *l);
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen pada index tertentu *** */
void deleteAtListStatik(ListStatik *l, ListStatikIdxType idx);
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
void deleteLastListStatik(ListStatik *l);
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */

#endif
