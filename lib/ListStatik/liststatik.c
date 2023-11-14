#include <stdio.h>
#include "liststatik.h"
#include "../pcolor/pcolor.h"

void CreateListPengguna(ListPengguna *l){
    int i;
    for (i=IDXMINListPengguna;i<CAPACITYListPengguna;i++){
        ELMTStatik(*l, i).isValid = false;
    }
}

int ListPenggunaLength(ListPengguna l){
    int listLength=0,i=0;
    // WARN: sementara dicomment dulu, ganggu compilation
    if (!ELMTStatik(l, IDXMINListPengguna).isValid){
        return 0;
    } else {
        while (ELMTStatik(l, i).isValid && i<CAPACITYListPengguna){
            listLength +=1;
            i++;
        }
    }
    return listLength;
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  
}

PenggunaIdxType getFirstIdxListPengguna(ListPengguna l){
    return IDXMINListPengguna;
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
}

PenggunaIdxType getLastIdxListPengguna(ListPengguna l){
    int length;
    length = ListPenggunaLength(l);
    return (length-1);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
}

boolean isIdxValidListPengguna(ListPengguna l, PenggunaIdxType i){
    return(i>=IDXMINListPengguna && i<CAPACITYListPengguna);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
}
boolean isIdxEffListPengguna(ListPengguna l, PenggunaIdxType i){
    return(i>=IDXMINListPengguna && i<ListPenggunaLength(l));
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
}

boolean isEmptyListPengguna(ListPengguna l){
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return(ListPenggunaLength(l)==0);
}

boolean isFullListPengguna(ListPengguna l){
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return(ListPenggunaLength(l)==CAPACITYListPengguna);
}

void readListListPengguna(ListPengguna *l){
    /* I.S. l sembarang */
/* F.S. List l terdefinisi */
/* Proses: membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
/*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITYListPengguna */
/*    Jika n tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < n <= CAPACITYListPengguna; Lakukan n kali: 
          Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
/*    Jika n = 0; hanya terbentuk List kosong */
    int n,i;
    do
    {
        /* code */
        scanf("%d",&n);
    } while (n<0 || n>CAPACITYListPengguna);
    CreateListPengguna(l);
    for (i=IDXMINListPengguna;i<n;i++){
        scanf("%d", &ELMTStatik(*l,i));
    }
}

void printListPengguna(ListPengguna l){
    /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
   siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
   karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika List kosong : menulis [] */
    int length,i;
    length = ListPenggunaLength(l);
    if (length==0){
        printf("[]");
    }
    else if (length == 1){
        printf("[%d]",ELMTStatik(l,0));
    }
    else{
        for (i=0;i<length;i++){
            if (i==0){
                printf("[%d,", ELMTStatik(l, i));
            }
            else if (i==length-1 ){
                printf("%d]",ELMTStatik(l, i));
            }
            else{
                printf("%d,",ELMTStatik(l, i));
            }
        }
    }
}

int indexOfListPengguna(ListPengguna l, PenggunaElType val){
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMTStatik(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEFListPengguna */
/* Skema Searching yang digunakan bebas */
    int i;
    if (isEmptyListPengguna(l)){
        return IDX_UNDEFListPengguna;
    }
    else{
        for(i=0;i<ListPenggunaLength(l);i++){
            // WARN: sementara dicomment dulu, ganggu compilation
            /* if(ELMTStatik(l,i)==val){ */
            /*     return i; */
            /* } */
        }
        return IDX_UNDEFListPengguna;
    }
}

void insertFirstListPengguna(ListPengguna *l, Pengguna user){
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
/* *** Menambahkan elemen pada index tertentu *** */
    int i;
    for (i = ListPenggunaLength(*l); i>IDXMINListPengguna; i--){
        ELMTStatik(*l, i)= ELMTStatik(*l, i-1);
    }
    ELMTStatik(*l, IDXMINListPengguna) = user;
}

void insertAtListPengguna(ListPengguna *l,Pengguna user, PenggunaIdxType idx){
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
    int i;
    if (!isFullListPengguna(*l) && !isEmptyListPengguna(*l) && isIdxValidListPengguna(*l,idx)){
        for(i=ListPenggunaLength(*l)+1;i>IDXMINListPengguna;i--){
            ELMTStatik(*l,i) = ELMTStatik(*l,(i-1));
        }
        ELMTStatik(*l,idx) = user;
    }
}

void insertLastListPengguna(ListPengguna *l, Pengguna user){
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
   if (isEmptyListPengguna(*l)) {
      ELMTStatik(*l, IDXMINListPengguna) = user;
   }
   else if (!isFullListPengguna(*l)) {
      ELMTStatik(*l, getLastIdxListPengguna(*l)+1) = user;
   }
}

void deleteFirstListPengguna(ListPengguna *l){
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen pada index tertentu *** */
    int i;
    if (!isEmptyListPengguna(*l)){
        for(i=1;i<ListPenggunaLength(*l);i++){
            ELMTStatik(*l,i-1) = ELMTStatik(*l,i);
        }
        // WARN: sementara dicomment dulu, ganggu compilation
        /* ELMTStatik(*l,ListPenggunaLength(*l)-1) = MARK; */
    }
}
void deleteAtListPengguna(ListPengguna *l, PenggunaIdxType idx){
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
    int i;
    if (!isEmptyListPengguna(*l) && isIdxValidListPengguna(*l,idx)){
        for(i=idx+1;i<ListPenggunaLength(*l);i++){
            ELMTStatik(*l,i-1) = ELMTStatik(*l,i);
        }
        // WARN: sementara dicomment dulu, ganggu compilation
        /* ELMTStatik(*l,ListPenggunaLength(*l)-1) = MARK; */
    }
}
void deleteLastListPengguna(ListPengguna *l){
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
    int i;
    if (!isEmptyListPengguna(*l)){
        // WARN: sementara dicomment dulu, ganggu compilation
        /* ELMTStatik(*l,getLastIdx(*l)) = MARK; */
    }
}

boolean UsernameTaken(ListPengguna l, Word nama) {
    int length = ListPenggunaLength(l);
    for (int i = 0; i < length; i++) {
        Pengguna currentPengguna = ELMTStatik(l, i);
        if(WordCmpWord(currentPengguna.Nama, nama)) {
            return true;
        }
    }
    return false;
}

boolean UserAndPasswordMatch(ListPengguna l, Word nama, Word password) {
    int length = ListPenggunaLength(l);
    for (int i = 0; i < length; i++) {
        Pengguna currentPengguna = ELMTStatik(l, i);
        // TODO: add hash
        if(WordCmpWord(currentPengguna.KataSandi, password) && WordCmpWord(currentPengguna.Nama, nama)) {
            return true;
        }
    }
    return false;
}

void CreatePengguna(Pengguna *p, Word Nama, Word KataSandi) {
    AssignWord(&p->JenisAkun, "PUBLIK");
    p->isValid = true;
    p->Nama = Nama;
    p->KataSandi = KataSandi;
    CreateProfil(&p->FotoProfil);
}

void InvalidateUser(Pengguna *p) {
    p->isValid = false;
}

boolean IsUserValid(Pengguna p) {
    return p.isValid;
}

void GetUserByName(ListPengguna l, Pengguna *p, Word nama) {
    int length = ListPenggunaLength(l);
    for (int i = 0; i < length; i++) {
        Pengguna currentPengguna = ELMTStatik(l, i);
        PrintWord(currentPengguna.Nama);
        printf(" ?? ");
        PrintWord(nama);
        printf("\n");
        if(WordCmpWord(currentPengguna.Nama, nama)) {
            printf("HERE\n");
            p = &currentPengguna;
        }
    }
}

void DisplayProfile(Pengguna p) {
    Matriks m = p.FotoProfil;
    for (int i=0; i<ROW_EFF(m); i++) {
        for (int j=0; j<COL_EFF(m); j++) {
            boolean isR = ELMT(m, i, j) == 'R';
            boolean isG = ELMT(m, i, j) == 'G';
            boolean isB = ELMT(m, i, j) == 'B';
            if(isR) {
                print_red(ELMT(m, i, j+1));
            } 
            if(isG) {
                print_green(ELMT(m, i, j+1));
            } 
            if(isB) {
                print_blue(ELMT(m, i, j+1));
            } 
        }
        printf("\n");
    }
}

void ChangeUserInfo(Pengguna *p, boolean isValid, Word Nama, Word KataSandi,
                    Word NoHP, Word BioAkun, Word Weton, Word JenisAkun,
                    Matriks FotoProfil) {
    p->isValid = isValid;
    p->Nama = Nama;
    p->KataSandi = KataSandi;
    p->NoHP = NoHP;
    p->BioAkun = BioAkun;
    p->Weton = Weton;
    p->FotoProfil = FotoProfil;
}

void ChangePrivacy(Pengguna *p, boolean private_) {
    if(!private_) {
        AssignWord(&p->JenisAkun, "PUBLIK");
    } else {
        AssignWord(&p->JenisAkun, "PRIVATE");
    }
}

boolean UserIsPrivate(Pengguna p) {
    return WordCmp(p.JenisAkun, "PRIVATE");
}

void CreateProfil(Matriks *m) {
    createMatriks(5, 10, m);
    for (int i=0; i<5; i++) {
        for (int j=0; j<10; j++) {
            if(j % 2 == 0) 
                ELMT(*m, i, j) = 'R';
            else
                ELMT(*m, i, j) = '*';
        }
    }
}

void UpdateProfil(Pengguna *p, Matriks m) {
    Matriks *pm = &p->FotoProfil;
    for (int i=0; i<5; i++) {
        for (int j=0; j<10; j++) {
            ELMT(*pm, i, j) = ELMT(m, i, j);
        }
    }
}
