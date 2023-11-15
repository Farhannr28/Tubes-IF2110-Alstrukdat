#include <stdio.h>
#include "../ListLinier/listlinier.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "Utasan.h"
int main(){
    ListLinearUtas l1;
    Word Isi;
    Word Penulis;
    // Utas(23,&l1);
    Utas(26,&l1);
    // lengthListLinearUtas(l1);
    // Sambung_Utas(1,3,&l1);
    // Cetak_Utas(l1,1);
    // Sambung_Utas(1,2,&l1);
    // Cetak_Utas(l1,1);
    // Hapus_Utas(1,6,&l1);
    // Hapus_Utas(1,5,&l1);
    // Cetak_Utas(l1,1);
    // Hapus_Utas(1,5,&l1);
    // printf("\n");
    // Hapus_Utas(1,1,&l1);
    printf("%d\n",GetUtasanIndex(l1,1));
    // printf("\n");
    Sambung_Utas(1,1,&l1);
    Cetak_Utas(l1,1);
    return 0;
}