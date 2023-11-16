#ifndef ListPengguna_H
#define ListPengguna_H

#include "../Matriks/matriks.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../PriorityQueue/prioqueue.h"
#include "../utility/boolean.h"
#include "../UndirectedGraph/graph.h"
/*  Kamus Umum */
#define CAPACITYListPengguna 20
/* Kapasitas penyimpanan */
#define IDXMINListPengguna 0
/* Indeks minimum list */
#define IDX_UNDEFListPengguna -1
/* Indeks tak terdefinisi*/
#define MARKListPengguna -9999
/* Nilai elemen tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int PenggunaElType;
typedef int PenggunaIdxType;

typedef struct pengguna {
  boolean isValid;
  int id;
  Word Nama;
  Word KataSandi;
  Word NoHP;
  Word BioAkun;
  Word Weton;
  Word JenisAkun;
  Matriks FotoProfil;
  PriorityQueue PermintaanBerteman;
} Pengguna;

typedef struct {
  Pengguna UserList[CAPACITYListPengguna];
} ListPengguna;

/* ********** SELEKTOR ********** */
#define ELMTStatik(l, i) (l).UserList[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListPengguna(ListPengguna *l);
/* I.S. l sembarang */
/* F.S. Terbentuk List l kosong dengan kapasitas CAPACITYListPengguna */
/* Proses: Inisialisasi semua elemen List l dengan MARKListPengguna */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int ListPenggunaLength(ListPengguna l);
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */

/* *** Selektor INDEKS *** */
PenggunaIdxType getFirstIdxListPengguna(ListPengguna l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
PenggunaIdxType getLastIdxListPengguna(ListPengguna l);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListPengguna(ListPengguna l, PenggunaIdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean isIdxEffListPengguna(ListPengguna l, PenggunaIdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListPengguna(ListPengguna l);
/* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
/* *** Test List penuh *** */
boolean isFullListPengguna(ListPengguna l);
/* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readListListPengguna(ListPengguna *l);
/* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <=
 * CAPACITYListPengguna */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= CAPACITYListPengguna; Lakukan n kali:
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
void printListPengguna(ListPengguna l);
/* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika List kosong : menulis [] */

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfListPengguna(ListPengguna l, PenggunaElType val);
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMTStatik(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEFListPengguna */
/* Skema Searching yang digunakan bebas */

/* ********** NILAI EKSTREM ********** */
void insertFirstListPengguna(ListPengguna *l, Pengguna user);
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
/* *** Menambahkan elemen pada index tertentu *** */
void insertAtListPengguna(ListPengguna *l, Pengguna user, PenggunaIdxType idx);
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l
 */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
void insertLastListPengguna(ListPengguna *l, Pengguna user);
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirstListPengguna(ListPengguna *l);
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen pada index tertentu *** */
void deleteAtListPengguna(ListPengguna *l, PenggunaIdxType idx);
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
void deleteLastListPengguna(ListPengguna *l);
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */

boolean UsernameTaken(ListPengguna l, Word nama);
boolean UserAndPasswordMatch(ListPengguna l, Word nama, Word password);
void CreatePengguna(Pengguna *p, Word Nama, Word KataSandi);
void InvalidateUser(Pengguna *p);
boolean IsUserValid(Pengguna p);
boolean GetUserByName(ListPengguna l, Pengguna *p, Word nama);
boolean GetUserById(ListPengguna l, Pengguna *p, int id);
boolean GetMutableUserByName(ListPengguna *l, Pengguna **p, Word nama);
void DisplayProfile(Pengguna p);
void ChangeUserInfo(Pengguna *p, boolean isValid, Word Nama, Word KataSandi,
                    Word NoHP, Word BioAkun, Word Weton, Word JenisAkun,
                    Matriks FotoProfil);
void ChangePrivacy(Pengguna *p, boolean private_);
boolean UserIsPrivate(Pengguna p);
void CreateProfil(Matriks *m);
void UpdateProfil(Pengguna *p, Matriks m);
boolean TambahTeman(Pengguna from, Pengguna *to);
Address GetPermintaanTeratas(Pengguna p);
void PrintListTeman(Pengguna p);
void hapusTeman(Graph *graph, int index_user_asal, int index_user_tujuan);
void printTeman(ListPengguna listUser, Graph graph, Pengguna p);
void addTeman(Graph *graph, int index_user_asal, int index_user_tujuan);

#endif
