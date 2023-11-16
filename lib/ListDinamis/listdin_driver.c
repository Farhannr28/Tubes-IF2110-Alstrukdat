#include<stdio.h>
#include"listdin.h"
#include "../Kicauan/kicauan.h"

int main(){
    ListDin l, l2;
    Kicauan k1, k2, k3, k4, k5, del;
    CreateListDin(&l, 2);
    printf("isEmpty: %d\n", isEmpty(l));
    k1.id = 1;
    k2.id = 2;
    k3.id = 3;
    k4.id = 4;
    k5.id = 5;
    insertLast(&l, k1);
    insertLast(&l, k2);
    insertLast(&l, k3);
    printf("current capacity: %d\n", CAPACITY(l));
    printf("last element: %d\n", ELMT(l, getLastIdx(l)).id);
    insertAt(&l, k4, 2);
    insertAt(&l, k5, 1);
    printf("2nd element: %d\n", ELMT(l, 1).id);
    printf("3rd element: %d\n", ELMT(l, 2).id);
    printf("4th element: %d\n", ELMT(l, 3).id);
    copyList(l, &l2);
    dealocateList(&l);
    printf("first element: %d\n", ELMT(l2, getFirstIdx(l2)).id);
    printf("current capacity: %d\n", CAPACITY(l2));
    compressList(&l2);
    printf("current capacity: %d\n", CAPACITY(l2));
    deleteLast(&l2, &del);
    printf("last element: %d\n", del.id);
    deleteLast(&l2, &del);
    printf("last element: %d\n", del.id);
    deleteAt(&l2, &del, 1);
    printf("2nd element: %d\n", del.id);
    return 0;
}
