#include <stdio.h>
#include <stdlib.h>
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "Utasan.h"
#include "../Pengguna/pengguna_methods.h"
#include "../Kicauan/kicauan_methods.h"
#include "../ListLinier/listlinier.h"

Paragraph* newParagraph( Word currentWord,DATETIME D) {
    Paragraph* p = (Paragraph*)malloc(sizeof(Paragraph));  
    if (p != NULL) {;
        p->DateTime = D;
        p->text = currentWord;  
        p->next = NULL;  
    }
    return p;
}

void CreateUtas(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,Word Penulis,DATETIME D) {
    u->IDUtasan = IDUtasan;
    u-> IDKicauan =IDKicauan;
    u->Penulis = Penulis;
    u->TextList = NULL;
    insertLastParagraph(u,Utasan,D);
}

void insertLastParagraph(Utasan *u, Word text,DATETIME D) {
    Paragraph* InputParagraph = newParagraph(text,D); 
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

void insertParagraphAtListPosition(ListLinearUtas *L, int IDUtasan, Word text, int position,DATETIME D) {
    // Find the Utasan node with the given IDUtasan
    AddressUtas utasanNode = *L;
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
    Paragraph* InputParagraph = newParagraph(text,D); 
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
    AddressUtas utasanNode = *L;
    while (utasanNode != NULL && IDUtasan(utasanNode) != IDUtasan) {
        utasanNode = NEXT(utasanNode);
    }

    // If no such Utasan is found, return
    if (utasanNode == NULL) {
        printf("Utasan with ID %d not found.\n", IDUtasan);
        return;
    }

    // Access the TextList of the found Utasan
    Paragraph *current = utasanNode->info.TextList;
    Paragraph *previous = NULL;
    int currentPosition = 1;

    if (position == 1) {
        utasanNode->info.TextList = current->next;
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
    int count = 0;
    AddressUtas p = l;
    while(IDUtasan(p) != IDUtasan){
        p = NEXT(p);
    }
    Paragraph* paragraph = p->info.TextList;
    while (paragraph!=NULL)
    {
        count++;
        paragraph = paragraph->next;
    }
    return count;
}


int indexOfListLinearUtas(ListLinearUtas l, int IdUtasan,Word* Penulis){
    //Pakai ini untuk cek IDXUtasan itu ada apa tidak
    int i = 0;
    int pos = IDX_UNDEF;
    AddressUtas p = l;
    while(p != NULL && pos == IDX_UNDEF){
        if(IDUtasan(p) == IdUtasan){
            pos = i;
            *Penulis = p->info.Penulis;
        }else{
            i++;
            p = NEXT(p);
        }
    }
    return pos;
}

void Utas(int IDKicau,ListLinearUtas *l,Word Penulis){
    Word Kicauan;
    Word Validasi;
    DATETIME D;
    Utasan U1;
    int IDUtas;
    IDUtas = lengthListLinearUtas(*l)+1;
    // printf("============\n");
    // printf("Ini IDUTAS:%d\n",IDUtas);
    //Sementara enggak looping validasi ada apa tidak
    //Kkeurangan: Cek kicauan ada atau bukan , dan apakah kicauan milik sendiri
    printf("Masukkan Kicauan:\n");
    GetWord(&Kicauan);
    D = GetCurrentDateTime();
    CreateUtas(&U1,IDUtas,IDKicau,Kicauan,Penulis,D);
    insertFirstListLinearUtas(l,U1);
    printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK):\n");
    GetWord(&Validasi);
    printf("\n");
    while(WordCmp(Validasi,"YA")){
        printf("Masukkan Kicauan:\n");
        GetWord(&Kicauan);
        D = GetCurrentDateTime();
        insertLastParagraph(&U1,Kicauan,D);
        printf("Apakah Anda ingin melanjutkan utas ini? (YA/TIDAK):\n");
        GetWord(&Validasi);
    }
    printf("Utas Selesai\n");
}

void Sambung_Utas(int IDUtas,int index,ListLinearUtas *l){
    int pos;
    DATETIME D;
    int indexMax;
    Word Penulis;
    pos = indexOfListLinearUtas(*l,IDUtas,&Penulis);
    if (pos!=IDX_UNDEF){
        indexMax = GetUtasanIndex(*l,IDUtas);
        if(indexMax+1 < index){
            printf("Index terlalu tinggi!\n");
        }
        else{
        AddressUtas p = *l;
        while(p!=NULL && IDUtasan(p)!=IDUtas){
            p = NEXT(p);
        }
        Utasan U1;
        U1 = INFO(p);
        Word Kicauan;
        printf("Masukkan kicauan:\n");
        GetWord(&Kicauan);
        D = GetCurrentDateTime();
        insertParagraphAtListPosition(l,IDUtas,Kicauan,index,D);
        }
    }
}

void Cetak_Utas(ListLinearUtas l,int IDUtas,ListDin ListKicau, ListStatik Users) {
    //Kurang: Cari Kicauan utama, cari penulis, datetime
    AddressUtas p = l;
    int count =0;
    int id,idpembuat;
    Kicauan K;
    Pengguna target;
    while (p!=NULL && IDUtasan(p)!=IDUtas)
    {
        // printf("IDutas%d\n",IDUtasan(p));
        p = NEXT(p);
        count++;
    }
    id = p->info.IDKicauan;
    getKicauanById(ListKicau, &K, id);
    idpembuat = K.idPembuat;
    GetUserById(Users, &target, idpembuat);
    if(p==NULL){
        printf("Utas tidak ditemukan\n");
    }
    else{
        printf("|");
        printf("ID = %d\n",id);
        printf("|");
        PrintWord(target.Nama);
        printf("\n");
        printf("|");
        TulisDateTime(K.waktu);
        printf("\n");
        printf("|");
        PrintWord(K.text);
        printf("\n");
        printf("\n");
        int index = 1;
        Paragraph* paragraph = p->info.TextList;
        while (paragraph !=NULL)
        {
            printf("    |");
            printf("INDEX:%d",index);
            printf("\n");
            printf("    |");
            PrintWord(p->info.Penulis);
            printf("\n");
            printf("    |");
            TulisDateTime(CurrTime(paragraph));
            printf("\n");
            printf("    |");
            PrintWord(KONTEN(paragraph));
            printf("\n");
            // printf("Idkicau:%d\n",p->info.IDKicauan);
            printf("\n");
            paragraph =  paragraph-> next;
            index ++;
        }
    }
}

void Hapus_Utas(int IDUtas,int index,ListLinearUtas*l){
    //Kekurangan, kalau milik orang lain harus dicek
    int pos;
    int indexMax;
    Word Penulis;
    pos = indexOfListLinearUtas(*l,IDUtas,&Penulis);
    if (pos!=IDX_UNDEF){
        indexMax = GetUtasanIndex(*l,IDUtas);
        if(index == 0){
            printf("Anda tidak bisa menghapus kicauan utama!");
        }
        else if(indexMax < index){
            printf("Kicauan sambungan dengan index %d tidak ditemukan pada utas!\n",index);
        }
        else{
        AddressUtas p = *l;
        while(p!=NULL && IDUtasan(p)!=IDUtas){
            p = NEXT(p);
        }
        Utasan U1;
        U1 = INFO(p);
        deleteParagraphAtPosition(l,IDUtas,index);
        printf("Kicauan sambungan berhasil dihapus!\n");
        }
    }
}

int BanyakUtasan(ListLinearUtas l,int IDKicau){
    AddressUtas p =l;
    while(p!=NULL){
        // printf("Jalan %d\n",IDKicauan(p));
        // break;
        if(IDKicauan(p) == IDKicau){
            Paragraph *currentParagraph = p->info.TextList;
            int length = 0;
            while(currentParagraph !=NULL){
                length++;
                currentParagraph = currentParagraph->next;
            }
            return length;
        }
        p = NEXT(p);
    }
}
