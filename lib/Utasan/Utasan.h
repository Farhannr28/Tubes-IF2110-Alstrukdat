#ifndef Utasan_H
#define Utasan_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../ListLinier./listlinier.h"

Paragraph* newParagraph( Word currentWord);

void insertLastParagraph(Utasan *u, Word text);

void deleteParagraphAtPosition(Utasan *u, int position);

int GetUtasanIndex(ListLinearUtas l,int);

void insertParagraphAtPosition(Utasan *u, Word text, int position);

void CreateUtas(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,Word Penulis);

int indexOfListLinearUtas(ListLinearUtas l, int IdxUtasan);

void Utas(int IDKicau,ListLinearUtas *l);

void Sambung_Utas(int IDUtas,int index,ListLinearUtas *l);

void Cetak_Utas(ListLinearUtas l,int IDUtas);

void Hapus_Utas(int IDUtas,int index,ListLinearUtas*l);

#endif