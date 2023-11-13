#include "config.h"
#include "../MesinKata/wordmachine.h"
#include <stdio.h>
#include <stdlib.h>

void loadConfig(Word fileWord) {
  char fileName[50]; // masih belum tau gimana cara dapet tanpa fixed size
  FILE *fptr;

  GetCharsFromWord(fileWord, fileName);

  if ((fptr = fopen(fileName, "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }

  char line[100]; // masih belum tau gimana cara dapet tanpa fixed size
  while (fgets(line, sizeof(line), fptr) != NULL) {
    // prosesnya nanti disini
    printf("%s", line);
  }

  fclose(fptr);
}
