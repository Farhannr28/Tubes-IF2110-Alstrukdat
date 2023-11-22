#include<stdio.h>
#include<stdlib.h>
#include"listdin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListKicauan(ListDin *l, int capacity){
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

    /* KAMUS */
    ElTypeListDin* ptr;
    /* ALGORITMA */
    ptr = (ElTypeListDin*) malloc(capacity * sizeof(ElTypeListDin));
    if (ptr == NULL){
        printf("Memory allocation failed\n");
    } else {
        BUFFER(*l) = ptr;
        CAPACITY(*l) = capacity;
        NEFF(*l) = 0;
    }
}


void dealocateListKicauan(ListDin *l){
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */

    /* KAMUS */

    /* ALGORITMA */
    CAPACITY(*l) = 0;
    NEFF(*l) = 0;
    free(BUFFER(*l));
}


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listKicauanLength(ListDin l){
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */

    /* KAMUS */

    /* ALGORITMA */
    return(NEFF(l));
}


/* *** Selektor INDEKS *** */
IdxType getFirstIdxListKicauan(ListDin l){
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
    
    /* KAMUS */
    IdxType ans = 0;
    /* ALGORITMA */
    return ans;
}

IdxType getLastIdxListKicauan(ListDin l){
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
    
    /* KAMUS */
    IdxType ans = NEFF(l)-1;
    /* ALGORITMA */
    return ans;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxListKicauanValid(ListDin l, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/

    /* KAMUS */
    
    /* ALGORITMA */
    return(i >= getFirstIdxListKicauan(l) && i < CAPACITY(l));
}

boolean isIdxListKicauanEff(ListDin l, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */

    /* KAMUS */
    
    /* ALGORITMA */
    return(i >= getFirstIdxListKicauan(l) && i <= getLastIdxListKicauan(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isListKicauanEmpty(ListDin l){
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */

    /* KAMUS */
    
    /* ALGORITMA */
    return(NEFF(l)==0);
}

boolean isListKicauanFull(ListDin l){
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

    /* KAMUS */
    
    /* ALGORITMA */
    return(NEFF(l)==CAPACITY(l));
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOfListKicauan(ListDin l, int x){
/* Search apakah ada kicauan di List l yang memiliki id x */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
    
    /* KAMUS */
    IdxType i;
    IdxType ans;
    /* ALGORITMA */
    ans = IDX_UNDEF;
    if (isListKicauanEmpty(l)){
        return ans;
    }
    for (i=NEFF(l)-1; i>-1; i--){
        /* if((ELMT(l,i)).id == x){ */
        /*     ans = i; */
        /* } */
    }
    return ans;
}


/* ********** OPERASI LAIN ********** */
void copyListKicauan(ListDin lIn, ListDin *lOut){
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */ 
    
    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    CreateListKicauan(lOut, CAPACITY(lIn));
    NEFF(*lOut) = NEFF(lIn);
    for(i=0; i<NEFF(lIn); i++){
        ELMTKicauan(*lOut, i) = ELMTKicauan(lIn, i);
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandListKicauan(ListDin *l, int num){
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

    /* KAMUS */
    ListDin baru;
    int i;
    /* ALGORITMA */
    CreateListKicauan(&baru, CAPACITY(*l)+num);
    // copyList(*l, &baru);
    for (i=0; i<NEFF(*l); i++){
        ELMTKicauan(baru, i) = ELMTKicauan(*l, i);
    }
    NEFF(baru) = NEFF(*l);
    copyListKicauan(baru, l);
    dealocateListKicauan(&baru);
}

void shrinkListKicauan(ListDin *l, int num){
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

    /* KAMUS */
    ListDin baru;
    int i;
    /* ALGORITMA */
    CreateListKicauan(&baru, CAPACITY(*l)-num);
    // copyList(*l, &baru);
    for (i=0; i<NEFF(*l); i++){
        ELMTKicauan(baru, i) = ELMTKicauan(*l, i);
    }
    NEFF(baru) = NEFF(*l);
    copyListKicauan(baru, l);
    dealocateListKicauan(&baru);
}

void compressListKicauan(ListDin *l){
/* Proses : Mengubah capacity sehingga capacity = nEff */
/* I.S. List tidak kosong */
/* F.S. Ukuran capacity = nEff */

    /* KAMUS */
    ListDin baru;
    int i;
    /* ALGORITMA */
    CreateListKicauan(&baru, NEFF(*l));
    // copyList(*l, &baru);
    for (i=0; i<NEFF(*l); i++){
        ELMTKicauan(baru, i) = ELMTKicauan(*l, i);
    }
    NEFF(baru) = NEFF(*l);
    copyListKicauan(baru, l);
    dealocateListKicauan(&baru);
}

/* *** Menambahkan elemen *** */
void insertKicauanAt(ListDin *l, ElTypeListDin val, IdxType idx){
/* Proses: Menambahkan val sebagai elemen list pada posisi idx, menggeser elemen setelahnya*/
/* I.S. List l tidak kosong, mungkin penuh, idx effektif */
/* F.S. Jika l penuh, kapasitas l menjadi 2 kalinya. Val adalah elemen terakhir l yang baru */
    
    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    if (isListKicauanFull(*l)){
        expandListKicauan(l, CAPACITY(*l));
    }
    NEFF(*l) = NEFF(*l) + 1;
    for (i = getLastIdxListKicauan(*l); i > idx; i--){
        ELMTKicauan(*l, i) = ELMTKicauan(*l, i-1);
    }
    ELMTKicauan(*l, idx) = val;
}

void insertKicauanLast(ListDin *l, ElTypeListDin val){
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, mungkin penuh */
/* F.S. Jika l penuh, kapasitas l menjadi 2 kalinya. Val adalah elemen terakhir l yang baru */
    
    /* KAMUS */
    
    /* ALGORITMA */
    if (isListKicauanFull(*l)){
        expandListKicauan(l, CAPACITY(*l));
    }
    NEFF(*l) = NEFF(*l) + 1;
    ELMTKicauan(*l, getLastIdxListKicauan(*l)) = val;
}

/* *** Menghapus elemen *** */
void deleteKicauanAt(ListDin *l, ElTypeListDin *val, IdxType idx){
/* Proses : Menghapus elemen list pada posisi idx, menggeser elemen setelahnya*/
/* I.S. List tidak kosong, idx valid */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      Jika l <25% terisi, kapasitas menjadi setengahnya */
/*      List l mungkin menjadi kosong */
    
    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    *val = ELMTKicauan(*l, idx);
    for (i = idx; i < getLastIdxListKicauan(*l); i++){
        ELMTKicauan(*l, i) = ELMTKicauan(*l, i+1);
    }
    NEFF(*l) = NEFF(*l) - 1;
    if (listKicauanLength(*l) < (CAPACITY(*l) / 4)){
        shrinkListKicauan(l, (CAPACITY(*l) / 2));
    }
}

void deleteKicauanLast(ListDin *l, ElTypeListDin *val){
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
/*      Jika l <25% terisi, kapasitas menjadi setengahnya */
    
    /* KAMUS */
    
    /* ALGORITMA */
    *val = ELMTKicauan(*l, getLastIdxListKicauan(*l));
    NEFF(*l) = NEFF(*l) - 1;
    if (listKicauanLength(*l) < (CAPACITY(*l) / 4)){
        shrinkListKicauan(l, (CAPACITY(*l) / 2));
    }
}

/* ********** Get ********** */
boolean getKicauanById(ListDin l, Kicauan *k, int id){
    for (int i = 0; i < l.capacity; i++) {
        if(ELMTKicauan(l, i).isValid) {
            if(ELMTKicauan(l, i).id == id) {
                *k = ELMTKicauan(l, i);
                return true;
            }
        }
    }
    return false;
}

boolean getKicauanByUserId(ListDin l, Kicauan *k, int userId) {
    for (int i = 0; i < l.capacity; i++) {
        if(ELMTKicauan(l, i).isValid) {
            if(ELMTKicauan(l, i).idPembuat == userId) {
                *k = ELMTKicauan(l, i);
                return true;
            }
        }
    }
    return false;
}