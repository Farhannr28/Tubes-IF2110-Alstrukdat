#ifndef Utasan_H
#define Utasan_H

#include "../ListLinier/listlinier.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../utility/boolean.h"
#include "../ListDinamis/listdin.h"
#include "../Kicauan/kicauan.h"
#include "../ListStatik/liststatik.h"
Paragraph *newParagraph(Word currentWord,DATETIME D);

void insertLastParagraph(Utasan *u, Word text,DATETIME D);

void deleteParagraphAtPosition(ListLinearUtas *L, int IDUtasan, int position);

int GetUtasanIndex(ListLinearUtas l, int);

void insertParagraphAtListPosition(ListLinearUtas *L, int IDUtasan, Word text, int position,DATETIME D);

void CreateUtas(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,
                Word Penulis,DATETIME D);

int indexOfListLinearUtas(ListLinearUtas l, int IdxUtasan,Word* Penulis);

void Utas(int IDKicau, ListLinearUtas *l,Word Penulis);

void Sambung_Utas(int IDUtas, int index, ListLinearUtas *l);

void Cetak_Utas(ListLinearUtas l, int IDUtas,ListDin ListKicau, ListStatik Users);

void Hapus_Utas(int IDUtas, int index, ListLinearUtas *l);

int BanyakUtasan(ListLinearUtas l,int IDKicau);

#endif
