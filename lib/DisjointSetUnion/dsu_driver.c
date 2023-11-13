#include<stdio.h>
#include"DSU.h"

int main(){
    DSU d;
    CreateDSU(&d);
    createSet(&d, 0);
    createSet(&d, 1);
    createSet(&d, 2);
    createSet(&d, 3);
    createSet(&d, 4);
    createSet(&d, 5);
    mergeSet(&d, 1, 4);
    mergeSet(&d, 2, 3);
    mergeSet(&d, 5, 3);
    printf("%d", findRoot(d, 5));
    printf("%d", isSameRoot(d, 4, 1));
    printf("%d", isSameRoot(d, 2, 3));
    printf("%d", isSameRoot(d, 0, 1));
    return 0;
}