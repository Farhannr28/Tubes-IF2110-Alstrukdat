#include <stdio.h>
#include "listlinier.h"
// #include "../MesinKata/wordmachine.h"
// #include "../MesinKarakter/charmachine.h"
int main(){
    ListLinearUtas l1;
    Ulasan ulasan;
    Ulasan ulasan2;
    Ulasan ulasan3;
    createUlasan(2,10,&ulasan);
    createUlasan(3,11,&ulasan2);
    createUlasan(4,13,&ulasan3);
    CreateListLinearUtas(&l1);
    insertFirstListLinearUtas(&l1,ulasan);
    insertFirstListLinearUtas(&l1,ulasan2);
    insertFirstListLinearUtas(&l1,ulasan3);
    displayListLinearUtas(l1);
    return 0;
}