#include <stdio.h>
#include "../ListLinier/listlinier.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "Utasan.h"
int main(){
    ListLinearUtas l1;
    Word Isi;
    Word Penulis;
    // printf("Penulis siapa:\n");
    // readKicau(&Penulis);
    printf("Isinya apa aj:\n");
    readKicau(&Isi);
    createUtasan(&INFO(l1),30,30,Isi,Penulis);
    printf("===sasasa\n");
    displayListLinearUtas(l1);
    return 0;
}