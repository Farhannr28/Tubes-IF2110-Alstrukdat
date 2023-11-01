#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
Address newNode(Ulasan val){
/* Definisi ListLinearUtas : */
/* ListLinearUtas kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir ListLinearUtas: jika addressnya Last, maka NEXT(Last)=NULL */
    Address p= malloc(sizeof(Node));
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

int indexOfListLinearUtas(ListLinearUtas l, int IdxUlasan){
    //Pakai ini untuk cek IDXulasan itu ada apa tidak
    int i = 0;
    int pos = IDX_UNDEF;
    Address p = l;
    while(p != NULL && pos == IDX_UNDEF){
        if(IDUlasan(p) == IdxUlasan){
            pos = i;
        }else{
            i++;
            p = NEXT(p);
        }
    }
    return pos;
}


void insertFirstListLinearUtas(ListLinearUtas *l, Ulasan val){
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
    Address p = newNode(val);
    if(p!= NULL){
        NEXT(p) = *l;
        *l = p;
    }
}

void insertLastListLinearUtas(ListLinearUtas *l, Ulasan val){
    Address p = newNode(val);
    if (p != NULL){
        if(isEmptyListLinearUtas(*l)){
            insertFirstListLinearUtas(l,val);
        }else{
            Address last= *l;
            while ((NEXT(last) != NULL))
            {
            last= NEXT(last);
            } 
            NEXT(last) = p;
        }
    }
}

void insertAtListLinearUtas(ListLinearUtas *l, Ulasan val, int idx){
    int i = 0;
    if (idx== 0){
        insertFirstListLinearUtas(l,val);
    }else{
        Address p= newNode(val);
        if(p!= NULL){
            Address insert = *l;
            while (insert != NULL && i < idx -1)
            {
                i++;
                insert= NEXT(insert);
            }
            if(insert != NULL){
                NEXT(p)= NEXT(insert);
                NEXT(insert) = p;
            }
        }
    }
}

void deleteFirstListLinearUtas(ListLinearUtas *l){
    Address p = *l;
    *l = NEXT(p);
    // *val = INFO(p);
    free(p);
}

void deleteLastListLinearUtas(ListLinearUtas *l){
    Address p = *l;
    Address mark = NULL;
    while (NEXT(p) != NULL){
        mark = p;
        p = NEXT (p);
    }
    if(mark==NULL){
        *l = NULL;
    }else{
        NEXT(mark) =  NULL;
    }
    // *val= INFO(p);
    free(p);
}


void deleteAtListLinearUtas(ListLinearUtas *l, int idx){
    if(idx == 0){
        deleteFirstListLinearUtas(l);
    }else{
        int i = 0;
        Address p = *l;
        Address mark = NULL;
        while (p != NULL && i < idx){
            i++;
            mark = p;
            p = NEXT(p);
        }

        if(p != NULL){
            NEXT(mark) = NEXT(p);
            free(p);
        }
    }
}

void displayListLinearUtas(ListLinearUtas l){
// void printInfo(ListLinearUtas l);
/* I.S. ListLinearUtas mungkin kosong */
/* F.S. Jika ListLinearUtas tidak kosong, iai ListLinearUtas dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika ListLinearUtas kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    Address p = l;
    // printf("[");
    while (p != NULL){
        printf("Indexnya:%d\n",IDUlasan(p));
        printf("Variabelnya:%d\n",Variable(p));
        p = NEXT(p);
        if(p != NULL){
            printf("==============================\n");
        }
    }
    // printf("]");
}


int lengthListLinearUtas(ListLinearUtas l){
/* Mengirimkan banyaknya elemen ListLinearUtas; mengirimkan 0 jika ListLinearUtas kosong */
    int i;
    int count = 0;
    Address p = l;
    while(p != NULL){
        count ++;
        p = NEXT(p);
    }
    return count;
}

void createUlasan(int IDUlasan, int variable, Ulasan *u) {
    u->IDUlasan = IDUlasan;
    // Set other fields here
    u->variable = variable;
}
