#ifndef Utasan_H
#define Utasan_H

#include "../ListLinier/listlinier.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../utility/boolean.h"

Paragraph *newParagraph(Word currentWord);

void insertLastParagraph(Utasan *u, Word text);

void deleteParagraphAtPosition(ListLinearUtas *L, int IDUtasan, int position);

int GetUtasanIndex(ListLinearUtas l, int);

void insertParagraphAtListPosition(ListLinearUtas *L, int IDUtasan, Word text, int position);

void CreateUtas(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,
                Word Penulis);

int indexOfListLinearUtas(ListLinearUtas l, int IdxUtasan);

void Utas(int IDKicau, ListLinearUtas *l);

void Sambung_Utas(int IDUtas, int index, ListLinearUtas *l);

void Cetak_Utas(ListLinearUtas l, int IDUtas);

void Hapus_Utas(int IDUtas, int index, ListLinearUtas *l);

#endif
