#ifndef PENGGUNA_H
#define PENGGUNA_H

#include "../MesinKata/wordmachine.h"
#include "../PriorityQueue/prioqueue.h"
#include "../Matriks/matriks.h"
#include "../Stack/stack.h"

typedef struct pengguna {
  boolean isValid;
  int id;
  Word Nama;
  Word KataSandi;
  Word NoHP;
  Word BioAkun;
  Word Weton;
  Word JenisAkun;
  Matriks FotoProfil;
  PriorityQueue PermintaanBerteman;
  Stack Draf;
} Pengguna;

#endif
