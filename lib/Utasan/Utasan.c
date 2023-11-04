#include <stdio.h>
#include <stdlib.h>
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "Utasan.h"
#include "../ListLinier/listlinier.h"
Paragraph* newParagraph( Word currentWord) {
    Paragraph* p = (Paragraph*)malloc(sizeof(Paragraph));  
    if (p != NULL) {
        p->text = currentWord;  
        p->next = NULL;  
    }
    return p;
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

void readKicau(Word *input){
    int i;
    START();

    (*input).Length = 0;
    i = 0;

    while ((currentChar != MARK) && (i < NMax)) {
        if (i<=280){
            (*input).TabWord[i] = currentChar;
        }
        if(i==280){
            (*input).TabWord[i] = '\0';
        }
        ADV();
        i++;
    }

    (*input).Length = i;
}