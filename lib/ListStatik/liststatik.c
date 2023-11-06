#include <stdio.h>
#include "liststatik.h"
void CreateListPengguna(ListPengguna *l){
    int i;
    for (i=IDXMINListPengguna;i<CAPACITYListPengguna;i++){
        ELMTStatik(*l, i) = MARK;
    }
}

int ListPenggunaLength(ListPengguna l){
    int listLength=0,i=0;
    if (ELMTStatik(l, IDXMINListPengguna)  == -9999){
        return 0;
    }
    else{
        while (ELMTStatik(l, i) != -9999 && i<CAPACITYListPengguna){
            listLength +=1;
            i++;
        }
    }
    return listLength;
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  
}

IdxType getFirstIdxListPengguna(ListPengguna l){
    return IDXMINListPengguna;
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
}

IdxType getLastIdxListPengguna(ListPengguna l){
    int length;
    length = listLength(l);
    return (length-1);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
}

boolean isIdxValidListPengguna(ListPengguna l, IdxType i){
    return(i>=IDXMINListPengguna && i<CAPACITYListPengguna);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
}
boolean isIdxEffListPengguna(ListPengguna l, IdxType i){
    return(i>=IDXMINListPengguna && i<listLength(l));
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
}

boolean isEmptyListPengguna(ListPengguna l){
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return(listLength(l)==0);
}

boolean isFullListPengguna(ListPengguna l){
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return(listLength(l)==CAPACITYListPengguna);
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
    length = listLength(l);
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

int indexOfListPengguna(ListPengguna l, ElType val){
/* Search apakah ada elemen List l yang bernilai val */
/* Jika ada, menghasilkan indeks i terkecil, dengan ELMTStatik(l,i) = val */
/* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEFListPengguna */
/* Skema Searching yang digunakan bebas */
    int i;
    if (isEmpty(l)){
        return IDX_UNDEFListPengguna;
    }
    else{
        for(i=0;i<listLength(l);i++){
            if(ELMTStatik(l,i)==val){
                return i;
            }
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
    for (i = listLength(*l); i>IDXMINListPengguna; i--){
        ELMTStatik(*l, i)= ELMTStatik(*l, i-1);
    }
    ELMTStatik(*l, IDXMINListPengguna)= user;
}

void insertAtListPengguna(ListPengguna *l,Pengguna user, IdxType idx){
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
    int i;
    if (!isFull(*l) && !isEmpty(*l) && isIdxValid(*l,idx)){
        for(i=listLength(*l)+1;i>IDXMINListPengguna;i--){
            ELMTStatik(*l,i) = ELMTStatik(*l,(i-1));
        }
        ELMTStatik(*l,idx) = user;
    }
}

void insertLastListPengguna(ListPengguna *l, Pengguna user){
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
   if (isEmpty(*l)) {
      ELMTStatik(*l, IDXMINListPengguna) = user;
   }
   else if (!isFull(*l)) {
      ELMTStatik(*l, getLastIdx(*l)+1) = user;
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
    if (!isEmpty(*l)){
        for(i=1;i<listLength(*l);i++){
            ELMTStatik(*l,i-1) = ELMTStatik(*l,i);
        }
        ELMTStatik(*l,listLength(*l)-1) = MARK;
    }
}
void deleteAtListPengguna(ListPengguna *l, IdxType idx){
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
    int i;
    if (!isEmpty(*l) && isIdxValid(*l,idx)){
        for(i=idx+1;i<listLength(*l);i++){
            ELMTStatik(*l,i-1) = ELMTStatik(*l,i);
        }
        ELMTStatik(*l,listLength(*l)-1) = MARK;
    }
}
void deleteLastListPengguna(ListPengguna *l){
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
    int i;
    if (!isEmpty(*l)){
    ELMTStatik(*l,getLastIdx(*l)) = MARK;
    }
}