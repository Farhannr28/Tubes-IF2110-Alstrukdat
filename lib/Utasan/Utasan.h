#ifndef Utasan_H
#define Utasan_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../ListLinier./listlinier.h"

Paragraph* newParagraph( Word currentWord);

void displayListLinearUtas(ListLinearUtas l);

void insertLastParagraph(Utasan *u, Word text);

void createUtasan(Utasan *u, int IDUtasan, int IDKicauan, Word Utasan,Word Penulis);

void printWord(Word word);

void readKicau(Word *input);

#endif