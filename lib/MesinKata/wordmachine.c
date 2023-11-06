#include "wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../utility/boolean.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

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
  while (*currentChar != MARK && w->Length < NMax) {
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

void ParseWord(Word *source, char delimiter, ...) {
  va_list args;
  va_start(args, delimiter);

  int i = 0;
  boolean isDelimiterFound = false;

  while (i < source->Length) {
    if (source->TabWord[i] == delimiter) {
      isDelimiterFound = true;
    } else {
      Word *destWord = va_arg(args, Word *);
      if (!isDelimiterFound) {
        destWord->Length = 0;
        destWord->TabWord[0] = '\0';
        int j = 0;
        while (source->TabWord[i] != delimiter && i < source->Length) {
          destWord->TabWord[j] = source->TabWord[i];
          destWord->Length++;
          j++;
          i++;
        }
        destWord->TabWord[j] = '\0'; // Null-terminate the word.
      }
    }

    i++;
  }

  va_end(args);
}
