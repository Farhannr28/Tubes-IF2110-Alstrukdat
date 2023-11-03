#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
Address newNode(Utasan val){
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

Paragraph* newParagraph( Word currentWord) {
    Paragraph* p = (Paragraph*)malloc(sizeof(Paragraph));  
    if (p != NULL) {
        p->text = currentWord;  
        p->next = NULL;  
    }
    return p;
}


void CreateListLinearUtas(ListLinearUtas *l){
/* I.S. sembarang             */
/* F.S. Terbentuk ListLinearUtas kosong */
    *l= NULL;
}
void CreateParagraphList(ListLinearUtas *l1){
    *l1 = NULL;
}
boolean isEmptyListLinearUtas(ListLinearUtas l){
/* Mengirim true jika ListLinearUtas kosong */
    return FIRST(l) == NULL;
}

int indexOfListLinearUtas(ListLinearUtas l, int IdxUtasan){
    //Pakai ini untuk cek IDXUtasan itu ada apa tidak
    int i = 0;
    int pos = IDX_UNDEF;
    Address p = l;
    while(p != NULL && pos == IDX_UNDEF){
        if(IDUtasan(p) == IdxUtasan){
            pos = i;
        }else{
            i++;
            p = NEXT(p);
        }
    }
    return pos;
}


void insertFirstListLinearUtas(ListLinearUtas *l, Utasan val){
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


void insertLastListLinearUtas(ListLinearUtas *l, Utasan val){
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

void insertAtListLinearUtas(ListLinearUtas *l, Utasan val, int idx){
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

void displayListLinearUtas(ListLinearUtas l) {
    Address p = l; 
    while (p != NULL) {
        printf("IDKicau:%d\n", IDKicauan(p));
        printf("IDUtas:%d\n", IDUtasan(p));
        Paragraph* paragraph = TEXT(p);
        while (paragraph != NULL) {
            printWord(KONTEN(paragraph));
            paragraph = paragraph->next;   
        }

        p = NEXT(p); 
        if (p != NULL) {
            printf("==============================\n");
        }
    }
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

void insertLastParagraph(Utasan *u, Word text) {
    Paragraph* InputParagraph = newParagraph(text); 
    if (InputParagraph != NULL) {
        if (u->TextList == NULL) {
            u->TextList = InputParagraph;
        } 
        else {
            Paragraph* last = u->TextList;
            while (NEXT(last) != NULL) {
                last = NEXT(last);
            }
            NEXT(last) = InputParagraph;
        }
    }
}

void createUtasan(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,Word Penulis) {
    u->IDUtasan = IDUtasan;
    u-> IDKicauan =IDKicauan;
    u->Penulis = Penulis;
    insertLastParagraph(u,Utasan);
}

void printWord(Word word) {
   int i;
   for (i = 0; i < word.Length; i++) {
      printf("%c", word.TabWord[i]);
   }
}

