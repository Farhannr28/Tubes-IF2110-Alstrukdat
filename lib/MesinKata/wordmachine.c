#include "wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../utility/boolean.h"
#include <stdio.h>

boolean EndWord;

void GetWord(Word *w) {
  char currentChar;
  ADV(&currentChar);
  if (currentChar == MARK) {
    EndWord = true;
  } else {
    EndWord = false;
    CopyWord(&currentChar, w);
    ADV(&currentChar);
  }
}

void PrintWord(Word w) {
  for (int i = 0; i < w.Length; i++) {
    printf("%c", w.TabWord[i]);
  }
}

void CopyWord(char *currentChar, Word *w) {
  int i = 0;
  while (*currentChar != BLANK && *currentChar != MARK && w->Length < NMax) {
    w->TabWord[i] = *currentChar;
    ADV(currentChar);
    i++;
    w->Length++;
  }
}

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
