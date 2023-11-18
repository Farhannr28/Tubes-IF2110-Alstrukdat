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

void insertParagraphAtListPosition(ListLinearUtas *L, int IDUtasan, Word text, int position) {
    // Find the Utasan node with the given IDUtasan
    Address utasanNode = *L;
    while (utasanNode != NULL && IDUtasan(utasanNode) != IDUtasan) {
        utasanNode = NEXT(utasanNode);
    }

    // If no such Utasan is found, return
    if (utasanNode == NULL) {
        printf("Utasan with ID %d not found.\n", IDUtasan);
        return;
    }

    // Now work with the found Utasan's TextList
    Utasan *u = &(INFO(utasanNode));
    Paragraph* InputParagraph = newParagraph(text); 
    if (InputParagraph == NULL) {
        return;
    }

    if (position == 1 || u->TextList == NULL) {
        InputParagraph->next = u->TextList;
        u->TextList = InputParagraph;
    } else {
        Paragraph* current = u->TextList;
        int currentPosition = 1;
        while (currentPosition < position - 1 && current->next != NULL) {
            current = current->next;
            currentPosition++;
        }
        InputParagraph->next = current->next;
        current->next = InputParagraph;
    }
}



void deleteParagraphAtPosition(ListLinearUtas *L, int IDUtasan, int position) {
    // Find the Utasan node with the given IDUtasan
    Address utasanNode = *L;
    while (utasanNode != NULL && IDUtasan(utasanNode) != IDUtasan) {
        utasanNode = NEXT(utasanNode);
    }

    // If no such Utasan is found, return
    if (utasanNode == NULL) {
        printf("Utasan with ID %d not found.\n", IDUtasan);
        return;
    }

    // Access the TextList of the found Utasan
    Paragraph *current = TEXT(utasanNode);
    Paragraph *previous = NULL;
    int currentPosition = 1;

    if (position == 1) {
        TEXT(utasanNode) = current->next;
        free(current);
    } else {
        while (currentPosition < position && current != NULL) {
            previous = current;
            current = current->next;
            currentPosition++;
        }

        if (current != NULL) {
            previous->next = current->next;
            free(current);
        }
    }
}



int GetUtasanIndex(ListLinearUtas l,int IDUtasan){
/* Mengirimkan banyaknya elemen ListLinearUtas; mengirimkan 0 jika ListLinearUtas kosong */
    int i;
    int count = 0;
    Address p = l;
    while(IDUtasan(p) != IDUtasan){
        p = NEXT(p);
    }
    Paragraph* paragraph = TEXT(p);
    while (paragraph!=NULL)
    {
        count++;
        paragraph = paragraph->next;
    }
    return count;
}

void CreateUtas(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,Word Penulis) {
    u->IDUtasan = IDUtasan;
    u-> IDKicauan =IDKicauan;
    u->Penulis = Penulis;
    u->TextList = NULL;
    insertLastParagraph(u,Utasan);
}

int indexOfListLinearUtas(ListLinearUtas l, int IdUtasan){
    //Pakai ini untuk cek IDXUtasan itu ada apa tidak
    int i = 0;
    int pos = IDX_UNDEF;
    Address p = l;
    while(p != NULL && pos == IDX_UNDEF){
        if(IDUtasan(p) == IdUtasan){
            pos = i;
        }else{
            i++;
            p = NEXT(p);
        }
    }
    return pos;
}

void Utas(int IDKicau,ListLinearUtas *l){
    Word Kicauan;
    Word Penulis;
    Word Validasi;
    Utasan U1;
    int IDUtas;
    IDUtas = lengthListLinearUtas(*l);
    printf("Ini IDUTAS:%d\n",IDUtas);
    //Sementara enggak looping validasi ada apa tidak
    //Kkeurangan: Cek kicauan ada atau bukan , dan apakah kicauan milik sendiri
    printf("Masukkan Kicauan:\n");
    GetWord(&Kicauan);
    //Sementara:
    printf("Masukkan Nama:\n");
    GetWord(&Penulis);
    CreateUtas(&U1,IDUtas,IDKicau,Kicauan,Penulis);
    insertFirstListLinearUtas(l,U1);
    printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK):\n");
    GetWord(&Validasi);
    PrintWord(Validasi);
    printf("\n");
    while(WordCmp(Validasi,"YA")){
        printf("Masukkan Kicauan:\n");
        GetWord(&Kicauan);
        insertLastParagraph(&U1,Kicauan);
        printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK):\n");
        GetWord(&Validasi);
    }
    printf("Utas Selesai\n");
}

void Sambung_Utas(int IDUtas,int index,ListLinearUtas *l){
    int pos;
    int indexMax;
    pos = indexOfListLinearUtas(*l,IDUtas);
    if (pos!=IDX_UNDEF){
        indexMax = GetUtasanIndex(*l,IDUtas);
        if(indexMax < index){
            printf("Index terlalu tinggi!\n");
        }
        else{
        Address p = *l;
        while(p!=NULL && IDUtasan(p)!=IDUtas){
            p = NEXT(p);
        }
        Utasan U1;
        U1 = INFO(p);
        Word Kicauan;
        printf("Masukkan kicauan:\n");
        GetWord(&Kicauan);
        insertParagraphAtListPosition(l,IDUtas,Kicauan,index);
        }
    }
}

void Cetak_Utas(ListLinearUtas l,int IDUtas) {
    //Kurang: Cari Kicauan utama, cari penulis, datetime
    Address p = l;
    int count =0;
    while (p!=NULL && IDUtasan(p)!=IDUtas)
    {
        printf("IDutas%d\n",IDUtasan(p));
        p = NEXT(p);
        count++;
    }
    if(p==NULL){
        printf("Utas tidak ditemukan\n");
    }
    else{
        int index = 1;
        Paragraph* paragraph = TEXT(p);
        while (paragraph !=NULL)
        {
            printf("    |");
            printf("INDEX:%d",index);
            printf("\n");
            printf("    |");
            PrintWord(KONTEN(paragraph));
            printf("\n");
            // printf("\n");
            paragraph =  paragraph-> next;
            index ++;
        }
    }
}

void Hapus_Utas(int IDUtas,int index,ListLinearUtas*l){
    //Kekurangan, kalau milik orang lain harus dicek
    int pos;
    int indexMax;
    pos = indexOfListLinearUtas(*l,IDUtas);
    if (pos!=IDX_UNDEF){
        indexMax = GetUtasanIndex(*l,IDUtas);
        if(index == 0){
            printf("Anda tidak bisa menghapus kicauan utama!");
        }
        else if(indexMax < index){
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n",index);
        }
        else{
        Address p = *l;
        while(p!=NULL && IDUtasan(p)!=IDUtas){
            p = NEXT(p);
        }
        Utasan U1;
        U1 = INFO(p);
        deleteParagraphAtPosition(l,IDUtas,index);
        }
    }
}