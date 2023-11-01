#include<stdio.h>
#include<stdlib.h>
#include"listdin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity){
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */

    /* KAMUS */
    ElType* ptr;
    /* ALGORITMA */
    ptr = (ElType*) malloc(capacity * sizeof(ElType));
    if (ptr == NULL){
        printf("Memory allocation failed\n");
    } else {
        BUFFER(*l) = ptr;
        CAPACITY(*l) = capacity;
        NEFF(*l) = 0;
    }
}


void dealocateList(ListDin *l){
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
int listLength(ListDin l){
/* Mengirimkan banyaknya elemen efektif list */
/* Mengirimkan nol jika list l kosong */
/* *** Daya tampung container *** */

    /* KAMUS */

    /* ALGORITMA */
    return(NEFF(l));
}


/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListDin l){
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
    
    /* KAMUS */
    IdxType ans = 0;
    /* ALGORITMA */
    return ans;
}

IdxType getLastIdx(ListDin l){
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
    
    /* KAMUS */
    IdxType ans = NEFF(l)-1;
    /* ALGORITMA */
    return ans;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
/* yaitu antara indeks yang terdefinisi utk container*/

    /* KAMUS */
    
    /* ALGORITMA */
    return(i >= getFirstIdx(l) && i < CAPACITY(l));
}

boolean isIdxEff(ListDin l, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
/* yaitu antara 0..NEFF(l) */

    /* KAMUS */
    
    /* ALGORITMA */
    return(i >= getFirstIdx(l) && i <= getLastIdx(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l){
/* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
/* *** Test list penuh *** */

    /* KAMUS */
    
    /* ALGORITMA */
    return(NEFF(l)==0);
}

boolean isFull(ListDin l){
/* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */

    /* KAMUS */
    
    /* ALGORITMA */
    return(NEFF(l)==CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l){
/* I.S. l sembarang dan sudah dialokasikan sebelumnya */
/* F.S. List l terdefinisi */
/* Proses : membaca banyaknya elemen l dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
      0 satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk l kosong */

    /* KAMUS */
    int n;
    ElType a;
    IdxType i;
    /* ALGORITMA */
    scanf("%d", &n);
    while(!isIdxValid(*l,n)){
        scanf("%d", &n);
    }
    if (n==0){
        NEFF(*l) = 0;
    } else {
        for (i=0; i<n; i++){
            scanf("%d", &a);
            ELMT(*l,i) = a;
        }
        NEFF(*l) = n;
    }
}

void printList(ListDin l){
/* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. l boleh kosong */
/* F.S. Jika l tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */

    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    if (isEmpty(l)){
        printf("[]");
    } else {
        printf("[%d", ELMT(l,0));
        for(i=1; i<NEFF(l); i++){
            printf(",%d", ELMT(l,i));
        }
        printf("]");
    }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus){
/* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
/* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */

    /* KAMUS */
    IdxType i;
    ListDin l3;
    int len;
    /* ALGORITMA */
    len = listLength(l1);
    CreateListDin(&l3, CAPACITY(l1));
    if(plus){
        for (i = 0; i < len; i++){
            ELMT(l3, i) = ELMT(l1, i) + ELMT(l2, i);
        }
    } else {
        for (i = 0; i < len; i++){
            ELMT(l3, i) = ELMT(l1, i) - ELMT(l2, i);
        }
    }
    NEFF(l3) = len;
    return l3;
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2){
/* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */

    /* KAMUS */
    IdxType i;
    int len;
    boolean ans;
    /* ALGORITMA */
    ans = true;
    if (NEFF(l1) != NEFF(l2)){
        return false;
    }
    len = NEFF(l1);
    for(i=0; i<len; i++){
        if (ELMT(l1,i) != ELMT(l2,i)){
            ans = false;
        }
    }
    return ans;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val){
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
/* Jika tidak ada, mengirimkan IDX_UNDEF */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
/* Skema Searching yang digunakan bebas */
    
    /* KAMUS */
    IdxType i;
    IdxType ans;
    /* ALGORITMA */
    ans = IDX_UNDEF;
    if (isEmpty(l)){
        return ans;
    }
    for (i=NEFF(l)-1; i>-1; i--){
        if(ELMT(l,i) == val){
            ans = i;
        }
    }
    return ans;
}


/* ********** NILAI EKSTREM ********** */
void extremeValues(ListDin l, ElType *max, ElType *min){
/* I.S. List l tidak kosong */
/* F.S. max berisi nilai maksimum l;
        min berisi nilai minimum l */
    
    /* KAMUS */
    IdxType i;
    ElType maximum;
    ElType minimum;
    /* ALGORITMA */
    maximum = ELMT(l,0);
    minimum = ELMT(l,0);
    for(i=1; i<NEFF(l); i++){
        if (ELMT(l,i) < minimum){
            minimum = ELMT(l,i);
        }
        if (ELMT(l,i) > maximum){
            maximum = ELMT(l,i);
        }
        *max = maximum;
        *min = minimum;
    }
}

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut){
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */ 
    
    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    CreateListDin(lOut, CAPACITY(lIn));
    NEFF(*lOut) = NEFF(lIn);
    for(i=0; i<NEFF(lIn); i++){
        ELMT(*lOut, i) = ELMT(lIn, i);
    }
}

ElType sumList(ListDin l){
/* Menghasilkan hasil penjumlahan semua elemen l */
/* Jika l kosong menghasilkan 0 */
    
    /* KAMUS */
    IdxType i;
    ElType ans;
    /* ALGORITMA */
    ans = 0;
    for(i=0; i<listLength(l); i++){
        ans = ans + ELMT(l,i);
    }
    return ans;
}

int countVal(ListDin l, ElType val){
/* Menghasilkan berapa banyak kemunculan val di l */
/* Jika l kosong menghasilkan 0 */
    
    /* KAMUS */
    IdxType i;
    int ans;
    /* ALGORITMA */
    if (isEmpty(l)){
        return 0;
    }
    ans = 0;
    for (i=0; i<listLength(l); i++){
        if (ELMT(l,i)==val){
            ans = ans + 1;
        }
    }
    return ans;
}

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc){
/* I.S. l boleh kosong */
/* F.S. Jika asc = true, l terurut membesar */
/*      Jika asc = false, l terurut mengecil */
/* Proses : Mengurutkan l dengan salah satu algoritma sorting,
   algoritma bebas */
    
    /* KAMUS */
    IdxType i;
    IdxType j;
    ElType temp;
    ElType ex;
    IdxType idx;
    /* ALGORITMA */
    for (i=0; i<listLength(*l); i++){
        ex = ELMT(*l, i);
        idx = i;
        for (j=i+1; j<listLength(*l); j++){
            if (asc){
                if (ELMT(*l,j)<ex){
                    ex = ELMT(*l,j);
                    idx = j;
                }
            } else {
                if (ELMT(*l,j)>ex){
                    ex = ELMT(*l,j);
                    idx = j;
                }
            }
        }
        temp = ELMT(*l,i);
        ELMT(*l, i) = ex;
        ELMT(*l, idx) = temp;
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandList(ListDin *l, int num){
/* Proses : Menambahkan capacity l sebanyak num */
/* I.S. List sudah terdefinisi */
/* F.S. Ukuran list bertambah sebanyak num */

    /* KAMUS */
    ListDin baru;
    int i;
    /* ALGORITMA */
    CreateListDin(&baru, CAPACITY(*l)+num);
    // copyList(*l, &baru);
    for (i=0; i<NEFF(*l); i++){
        ELMT(baru, i) = ELMT(*l, i);
    }
    NEFF(baru) = NEFF(*l);
    copyList(baru, l);
    dealocateList(&baru);
}

void shrinkList(ListDin *l, int num){
/* Proses : Mengurangi capacity sebanyak num */
/* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
/* F.S. Ukuran list berkurang sebanyak num. */

    /* KAMUS */
    ListDin baru;
    int i;
    /* ALGORITMA */
    CreateListDin(&baru, CAPACITY(*l)-num);
    // copyList(*l, &baru);
    for (i=0; i<NEFF(*l); i++){
        ELMT(baru, i) = ELMT(*l, i);
    }
    NEFF(baru) = NEFF(*l);
    copyList(baru, l);
    dealocateList(&baru);
}

void compressList(ListDin *l){
/* Proses : Mengubah capacity sehingga capacity = nEff */
/* I.S. List tidak kosong */
/* F.S. Ukuran capacity = nEff */

    /* KAMUS */
    ListDin baru;
    int i;
    /* ALGORITMA */
    CreateListDin(&baru, NEFF(*l));
    // copyList(*l, &baru);
    for (i=0; i<NEFF(*l); i++){
        ELMT(baru, i) = ELMT(*l, i);
    }
    NEFF(baru) = NEFF(*l);
    copyList(baru, l);
    dealocateList(&baru);
}

/* *** Menambahkan elemen *** */
void insertAt(ListDin *l, ElType val, IdxType idx){
/* Proses: Menambahkan val sebagai elemen list pada posisi idx, menggeser elemen setelahnya*/
/* I.S. List l tidak kosong, mungkin penuh, idx effektif */
/* F.S. Jika l penuh, kapasitas l menjadi 2 kalinya. Val adalah elemen terakhir l yang baru */
    
    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    if (isFull(*l)){
        expandList(l, CAPACITY(*l));
    }
    NEFF(*l) = NEFF(*l) + 1;
    for (i = getLastIdx(*l); i > idx; i--){
        ELMT(*l, i) = ELMT(*l, i-1);
    }
    ELMT(*l, idx) = val;
}

void insertLast(ListDin *l, ElType val){
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, mungkin penuh */
/* F.S. Jika l penuh, kapasitas l menjadi 2 kalinya. Val adalah elemen terakhir l yang baru */
    
    /* KAMUS */
    
    /* ALGORITMA */
    if (isFull(*l)){
        expandList(l, CAPACITY(*l));
    }
    NEFF(*l) = NEFF(*l) + 1;
    ELMT(*l, getLastIdx(*l)) = val;
}

/* *** Menghapus elemen *** */
void deleteAt(ListDin *l, ElType *val, IdxType idx){
/* Proses : Menghapus elemen list pada posisi idx, menggeser elemen setelahnya*/
/* I.S. List tidak kosong, idx valid */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      Jika l <25% terisi, kapasitas menjadi setengahnya */
/*      List l mungkin menjadi kosong */
    
    /* KAMUS */
    IdxType i;
    /* ALGORITMA */
    *val = ELMT(*l, idx);
    for (i = idx; i < getLastIdx(*l); i++){
        ELMT(*l, i) = ELMT(*l, i+1);
    }
    NEFF(*l) = NEFF(*l) - 1;
    if (listLength(*l) < (CAPACITY(*l) / 4)){
        shrinkList(l, (CAPACITY(*l) / 2));
    }
}

void deleteLast(ListDin *l, ElType *val){
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
/*      Jika l <25% terisi, kapasitas menjadi setengahnya */
    
    /* KAMUS */
    
    /* ALGORITMA */
    *val = ELMT(*l, getLastIdx(*l));
    NEFF(*l) = NEFF(*l) - 1;
    if (listLength(*l) < (CAPACITY(*l) / 4)){
        shrinkList(l, (CAPACITY(*l) / 2));
    }
}