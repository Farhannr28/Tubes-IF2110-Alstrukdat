#include "wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../utility/boolean.h"

boolean EndWord;
Word currentWord;

void IgnoreBlanks(char *currentChar) {
  while (*currentChar == BLANK) {
    ADV(currentChar);
  }
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */

void STARTWORD(char *currentChar, Word *currentWord) {
  IgnoreBlanks(currentChar);
  if (*currentChar == MARK) {
    EndWord = true;
  } else {
    EndWord = false;
    CopyWord(currentChar, currentWord);
    ADV(currentChar);
  }
}
/* I.S. : currentChar sembarang
   F.S. : EndWord = true, dan currentChar = MARK;
          atau EndWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */

void ADVWORD(char *currentChar, Word *currentWord) {
  IgnoreBlanks(currentChar);
  if (*currentChar == MARK) {
    EndWord = true;
  } else {
    EndWord = false;
    CopyWord(currentChar, currentWord);
    IgnoreBlanks(currentChar);
  }
}
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, EndWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */

void CopyWord(char *currentChar, Word *currentWord) {
  int i = 0;
  while (*currentChar != BLANK && *currentChar != MARK && !EOP &&
         currentWord->Length < NMax) {
    currentWord->TabWord[i] = *currentChar;
    ADV(currentChar);
    i++;
    currentWord->Length++;
  }
}
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

boolean WordCmp(Word word, const char compare[]) {
  int i = 0;

  while (word.TabWord[i] != '\0' && compare[i] != '\0') {
    if (word.TabWord[i] != compare[i]) {
      return false;
    }
    i++;
  }

  return (word.TabWord[i] == '\0' && compare[i] == '\0');
}

void getInput(char currentChar, Word *input) {}
