#include <stdio.h>
#include "liststatik.h"
#include "../pcolor/pcolor.h"
#include "../UndirectedGraph/graph.h"

void CreateListStatik(ListStatik *l, ListStatikType type) {
    for (int i=IDXMINListStatik;i<CAPACITYListStatik;i++){
        ELMTStatik(*l, i).isValid = false;
    }
    l->type = type;
}

int ListStatikLength(ListStatik l){
    int listLength=0, i=0;
    if (!ELMTStatik(l, IDXMINListStatik).isValid){
        return 0;
    } else {
        while (ELMTStatik(l, i).isValid && i<CAPACITYListStatik){
            listLength +=1;
            i++;
        }
    }
    return listLength;
/* Mengirimkan banyaknya elemen efektif List */
/* Mengirimkan nol jika List kosong */  
}

ListStatikIdxType getFirstIdxListStatik(ListStatik l){
    return IDXMINListStatik;
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l pertama */
}

ListStatikIdxType getLastIdxListStatik(ListStatik l){
    int length;
    length = ListStatikLength(l);
    return (length-1);
/* Prekondisi : List l tidak kosong */
/* Mengirimkan indeks elemen l terakhir */
}

boolean isIdxValidListStatik(ListStatik l, ListStatikIdxType i){
    return(i>=IDXMINListStatik && i<CAPACITYListStatik);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
/* yaitu antara indeks yang terdefinisi utk container*/
}
boolean isIdxEffListStatik(ListStatik l, ListStatikIdxType i){
    return(i>=IDXMINListStatik && i<ListStatikLength(l));
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
/* yaitu antara 0..length(l)-1 */
}

boolean isEmptyListStatik(ListStatik l){
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    return(ListStatikLength(l)==0);
}

boolean isFullListStatik(ListStatik l){
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return(ListStatikLength(l)==CAPACITYListStatik);
}

void insertFirstListStatik(ListStatik *l, ListStatikElType el){
/* Proses: Menambahkan val sebagai elemen pertama List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen pertama l yang baru */
/* *** Menambahkan elemen pada index tertentu *** */
    int i;
    for (i = ListStatikLength(*l); i>IDXMINListStatik; i--){
        ELMTStatik(*l, i)= ELMTStatik(*l, i-1);
    }
    ELMTStatik(*l, IDXMINListStatik) = el;
}

void insertAtListStatik(ListStatik *l, ListStatikElType el, ListStatikIdxType idx){
/* Proses: Menambahkan val sebagai elemen pada index idx List */
/* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
/* F.S. val adalah elemen yang disisipkan pada index idx l */
/* *** Menambahkan elemen terakhir *** */
    if (!isFullListStatik(*l) && !isEmptyListStatik(*l) && isIdxValidListStatik(*l,idx)){
        for(int i=ListStatikLength(*l)+1;i>IDXMINListStatik && i > idx;i--){
            ELMTStatik(*l,i) = ELMTStatik(*l,(i-1));
        }
    }
    ELMTStatik(*l,idx) = el;
}

void insertForceAtListStatik(ListStatik *l, ListStatikElType el, ListStatikIdxType idx) {
    ELMTStatik(*l,idx) = el;
}

void insertLastListStatik(ListStatik *l, ListStatikElType user){
/* Proses: Menambahkan val sebagai elemen terakhir List */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
   if (isEmptyListStatik(*l)) {
      ELMTStatik(*l, IDXMINListStatik) = user;
   }
   else if (!isFullListStatik(*l)) {
      ELMTStatik(*l, getLastIdxListStatik(*l)+1) = user;
   }
}

void deleteFirstListStatik(ListStatik *l){
/* Proses : Menghapus elemen pertama List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen pada index tertentu *** */
    int i;
    if (!isEmptyListStatik(*l)){
        for(i=1;i<ListStatikLength(*l);i++){
            ELMTStatik(*l,i-1) = ELMTStatik(*l,i);
        }
        ELMTStatik(*l,ListStatikLength(*l)-1).isValid = false;
    }
}
void deleteAtListStatik(ListStatik *l, ListStatikIdxType idx){
/* Proses : Menghapus elemen pada index idx List */
/* I.S. List tidak kosong, idx adalah index yang valid di l */
/* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
/* *** Menghapus elemen terakhir *** */
    int i;
    if (!isEmptyListStatik(*l) && isIdxValidListStatik(*l,idx)){
        for(i=idx+1;i<ListStatikLength(*l);i++){
            ELMTStatik(*l,i-1) = ELMTStatik(*l,i);
        }
        ELMTStatik(*l,ListStatikLength(*l)-1).isValid = false; 
    }
}
void deleteLastListStatik(ListStatik *l){
/* Proses : Menghapus elemen terakhir List */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen List berkurang satu */
/*      List l mungkin menjadi kosong */
    if (!isEmptyListStatik(*l)){
         ELMTStatik(*l, getLastIdxListStatik(*l)).isValid = false; 
    }
}

boolean isListStatikEmptyAt(ListStatik l, int idx) {
    return !ELMTStatik(l, idx).isValid;
}
