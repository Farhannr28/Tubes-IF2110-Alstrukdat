/* MODUL INTEGER DYNAMIC LIST */
/* Berisi definisi dan semua primitif pemrosesan list integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori list dinamik */

#ifndef LISTDIN_H
#define LISTDIN_H

#include "../Kicauan/kicauan.h"
#include "../utility/boolean.h"

/*  Kamus Umum */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF_LIST_DIN -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef union {
  Kicauan k;
} ElTypeListDin; /* type elemen list */

typedef enum {
  KICAUAN,
} ListDinType; /* type elemen list */

typedef int IdxType;

typedef struct {
  ElTypeListDin *buffer; /* memori tempat penyimpan elemen (container) */
  int nEff;              /* >=0, banyaknya elemen efektif */
  int capacity;          /* ukuran elemen */
  ListDinType type;
} ListDin;
/* Indeks yang digunakan [0..capacity-1] */
/* Jika l adalah : ListDin, cara deklarasi dan akses: */
/* Deklarasi : l : ListDin */
/* Maka cara akses:
   l.nEff      untuk mengetahui banyaknya elemen
   l.buffer    untuk mengakses seluruh nilai elemen list
   l.buffer[i] untuk mengakses elemen ke-i */
/* Definisi :
  list kosong: l.nEff = 0
  Definisi elemen pertama : l.buffer[i] dengan i=0
  Definisi elemen terakhir yang terdefinisi: l.buffer[i] dengan i=l.capacity */

/* ********** SELEKTOR ********** */
#define NEFF(l) (l).nEff
#define BUFFER(l) (l).buffer
#define ELMTDinamik(l, i) (l).buffer[i]
#define CAPACITY(l) (l).capacity
#define ListDinType(l) (l).type

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDinamik(ListDin *l, int capacity, ListDinType type);
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

void dealocateListDinamik(ListDin *l);
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listDinamikLength(ListDin l);
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListDinamik(ListDin l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
IdxType getLastIdxListDinamik(ListDin l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */

/* ********** Test Indeks yang valid ********** */
boolean isIdxListDinamikValid(ListDin l, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxListDinamikEff(ListDin l, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isListDinamikEmpty(ListDin l);
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */
boolean isListDinamikFull(ListDin l);
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOfListDinamik(ListDin l, int x);
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */

/* ********** OPERASI LAIN ********** */
void copyListDinamik(ListDin lIn, ListDin *lOut);
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandListDinamik(ListDin *l, int num);
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

void shrinkListDinamik(ListDin *l, int num);
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity -
 * num. */
/* F.S. Ukuran list berkurang sebanyak num. */

void compressListDinamik(ListDin *l);
/* Proses : Mengubah capacity sehingga capacity = nEff */
/* I.S. List tidak kosong */
/* F.S. Ukuran capacity = nEff */

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen *** */
void insertDinamikAt(ListDin *l, ElTypeListDin val, IdxType idx);
/* Proses: Menambahkan val sebagai elemen list pada posisi idx, menggeser elemen
 * setelahnya*/
/* I.S. List l tidak kosong, mungkin penuh, idx effektif */
/* F.S. Jika l penuh, kapasitas l menjadi 2 kalinya. Val adalah elemen terakhir
 * l yang baru */

void insertDinamikLast(ListDin *l, ElTypeListDin val);
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
void deleteDinamikAt(ListDin *l, ElTypeListDin *val, IdxType idx);
/* Proses : Menghapus elemen list pada posisi idx, menggeser elemen setelahnya*/
/* I.S. List tidak kosong, idx valid */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      Jika l <25% terisi, kapasitas menjadi setengahnya */
/*      List l mungkin menjadi kosong */

void deleteDinamikLast(ListDin *l, ElTypeListDin *val);
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
#endif
