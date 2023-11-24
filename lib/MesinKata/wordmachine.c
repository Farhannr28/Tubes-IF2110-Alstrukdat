#include "wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../utility/boolean.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

boolean EndWord;

void GetWord(Word *w) {
  if (w->Length != 0)
    w->Length = 0;

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

void ReadFileLine(Word *w, FILE *file) {
  if (w->Length != 0)
    w->Length = 0;
  char currentChar;
  int i = 0;
  do {
    if(currentChar != '\n') {
      w->TabWord[i] = currentChar;
      currentChar = fgetc(file);
      i++;
      w->Length++;
    }
  } while (currentChar != '\n' && currentChar != EOF && w->Length < NMax);
}

void ReadFileNLine(Word *w, FILE *file, int nLine) {
  if (w->Length != 0)
    w->Length = 0;
  char currentChar;
  for (int i = 0; i<nLine; i++) {
    int j = w->Length;
    do {
      w->TabWord[j] = currentChar;
      currentChar = fgetc(file);
      j++;
      w->Length++;
    } while (currentChar != '\n' && currentChar != EOF && w->Length < NMax);
  }
}

void WriteToFile(Word w, FILE *file) {
  for (int i = 0; i < w.Length; i++) {
    fprintf(file, "%c", w.TabWord[i]);
  }
}

void GetWordButTrim(Word *w, char delim) {
  if (w->Length != 0)
    w->Length = 0;

  char currentChar;
  ADV(&currentChar);
  if (currentChar == MARK) {
    EndWord = true;
  } else {
    EndWord = false;
    CopyWordButTrim(&currentChar, w, delim);
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

void CopyWordButTrim(char *currentChar, Word *w, char delim) {
  int i = 0;
  while (*currentChar != MARK && w->Length < NMax) {
    if (*currentChar != delim) {
      w->TabWord[i] = *currentChar;
      i++;
      w->Length++;
    }
    ADV(currentChar);
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

  return true && (i == word.Length);
}

boolean WordCmpWord(Word w1, Word w2) {
  int i = 0;

  if (w1.Length != w2.Length)
    return false;

  while (w1.Length != i && w2.Length != i) {
    if (w1.TabWord[i] != w2.TabWord[i]) {
      return false;
    }
    i++;
  }

  return true;
}

void AssignWord(Word *word, const char chars[]) {
  int i = 0;
  while (chars[i] != '\0') {
    word->TabWord[i] = chars[i];
    i++;
  }
  word->Length = i;
}

void GetCharsFromWord(Word word, char *chars) {
  int i = 0;
  while (i < word.Length) {
    chars[i] = word.TabWord[i];
    i++;
  }
  chars[i] = '\0';
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

void AssignWordFromWord(Word from, Word *to) {
  for (int i = 0; i < from.Length; i++) {
    to->TabWord[i] = from.TabWord[i];
  }
  to->Length = from.Length;
}

void ConcatWordWithSpace(Word *result, Word concat) {
  result->TabWord[result->Length+1] = ' ';
  result->Length++;
  for (int i = 0; i < concat.Length; i++) {
    result->TabWord[i+result->Length] = concat.TabWord[i];
  }
  result->Length += concat.Length;
}

int IntFromWord(Word w) {
  int result = 0;
  for (int i = 0; i < w.Length; ++i) {
    if (w.TabWord[i] >= '0' && w.TabWord[i] <= '9')
      result = result * 10 + (w.TabWord[i] - '0');
  }
  return result;
}

Word WordFromInt(int num) {
  int temp = num;
  int numDigits = 0;
  while (temp != 0) {
    temp /= 10;
    numDigits++;
  }

  Word result;
  for (int i = numDigits - 1; i >= 0; --i) {
    result.TabWord[i] = (char)('0' + num % 10);
    num /= 10;
  }
  result.Length = numDigits;

  return result;
}

boolean isWordNumeric(Word w) {
  for (int i = 0; i < w.Length; ++i) {
    if (!(w.TabWord[i] >= '0' && w.TabWord[i] <= '9')) return false;
  }
  return true;
}
