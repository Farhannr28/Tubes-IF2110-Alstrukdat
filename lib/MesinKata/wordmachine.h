/* File: wordmachine.h */
/* Definisi Mesin Word: Model Akuisisi Versi I */

#ifndef __WORDMACHINE_H__
#define __WORDMACHINE_H__

#include "../MesinKarakter/charmachine.h"
#include "../utility/boolean.h"

#define NMax 280
#define BLANK ' '

typedef struct {
  char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai
                         [0..NMax-1] */
  int Length;
} Word;

/* State Mesin Word */
extern boolean EndWord;
extern Word currentWord;

void GetWord(Word *w);
void CopyWord(char *currentChar, Word *w);
void PrintWord(Word w);
boolean WordCmp(Word word, const char compare[]);
void readParagraph(Word *input);
void AssignWord(Word *word, const char chars[]);
void AssignWordFromWord(Word from, Word *to);
void GetCharsFromWord(Word word, char *chars);
void ParseWord(Word *source, char delimiter, ...);
boolean WordCmpWord(Word w1, Word w2);
void CopyWordButTrim(char *currentChar, Word *w, char delim);
void GetWordButTrim(Word *w, char delim);
#endif
