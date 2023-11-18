#include <stdio.h>
#include "../ListLinier/listlinier.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "Utasan.h"
void printTextList(ListLinearUtas L) {
    Paragraph* current = L->info.TextList;
    while (current != NULL) {
        PrintWord(current->text);  // Assuming PrintWord is your function to print a Word
        current = current->next;
    }
}
int main(){
    ListLinearUtas l1;
    Word Isi;
    Word Penulis;
    Utasan U1;
    // Utas(23,&l1);
    Utas(26,&l1);
    Utas(21,&l1);
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
    // printf("%d\n",GetUtasanIndex(l1,1));
    // printf("\n");
    Sambung_Utas(1,1,&l1);
    Hapus_Utas(2,3,&l1);
    printf("Ini bawah abru 2\n");
    Cetak_Utas(l1,2);
    printf("Ini bawah abru 1\n");
    Cetak_Utas(l1,1);
    // printTextList(l1);
    return 0;
}