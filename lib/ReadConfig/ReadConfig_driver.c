#include "../ListLinier/listlinier.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../Utasan/Utasan.h"
#include "../utility/boolean.h"
#include "ReadConfig.h"
#include "stdio.h"
// #include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "string.h"
// Contoh
int main() {
  ListLinearUtas listUtas;
  CreateListLinearUtas(&listUtas);
  MuatUtas("config", &listUtas);
  printf("fungsi Selesai\n");
  // PrintWord(W1);
  /* Cetak_Utas(listUtas,1); */
}
