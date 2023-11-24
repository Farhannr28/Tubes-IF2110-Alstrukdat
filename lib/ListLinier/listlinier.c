#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"

AddressUtas newNodeUtas(Utasan val){
/* Definisi ListLinearUtas : */
/* ListLinearUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan AddressUtas p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir ListLinearUtas: jika AddressUtasnya Last, maka NEXT(Last)=NULL */
    AddressUtas p= malloc(sizeof(NodeUtas));
    if (p!=NULL){
        INFO(p)=val;
        NEXT(p)=NULL;
    }
    return p;
}

void CreateListLinearUtas(ListLinearUtas *l){
/* I.S. sembarang             */
/* F.S. Terbentuk ListLinearUtas kosong */
    *l= NULL;
}
boolean isEmptyListLinearUtas(ListLinearUtas l){
/* Mengirim true jika ListLinearUtas kosong */
    return FIRST(l) == NULL;
}

void insertFirstListLinearUtas(ListLinearUtas *l, Utasan val){
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
    AddressUtas p = newNodeUtas(val);
    if(p!= NULL){
        NEXT(p) = *l;
        *l = p;
    }
}


void insertLastListLinearUtas(ListLinearUtas *l, Utasan val){
    AddressUtas p = newNodeUtas(val);
    if (p != NULL){
        if(isEmptyListLinearUtas(*l)){
            insertFirstListLinearUtas(l,val);
        }else{
            AddressUtas last= *l;
            while ((NEXT(last) != NULL))
            {
            last= NEXT(last);
            } 
            NEXT(last) = p;
        }
    }
}

int lengthListLinearUtas(ListLinearUtas l){
/* Mengirimkan banyaknya elemen ListLinearUtas; mengirimkan 0 jika ListLinearUtas kosong */
    int count = 0;
    AddressUtas p = l;
    while(p != NULL){
        count ++;
        p = NEXT(p);
    }
    return count;
}

boolean isInList (ListLinearUtas l, int IDKicau){
    int i = 0;
    int pos = IDX_UNDEF;
    AddressUtas p = l;
    while(p != NULL && pos == IDX_UNDEF){
        if(IDKicauan(p) == IDKicau){
            return true;
        }else{
            p = NEXT(p);
        }
    }
    return false;
}




