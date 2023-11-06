/* File: charmachine.c */
/* Implementasi Mesin Karakter */

#include "charmachine.h"
#include <stdio.h>

char currentChar;
boolean EOP;

void ADV(char *currentChar) { fscanf(stdin, "%c", currentChar); }
