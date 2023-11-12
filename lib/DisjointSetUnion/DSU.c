#include<stdio.h>
#include"DSU.h"

/* ********** KONSTRUKTOR ********** */
void CreateDSU(DSU *d){
/* I.S. d sembarang */
/* F.S. Terbentuk DSU d kosong dengan seluruh parent menjadi UndefinedParent & size menjadi 0 */
    /* KAMUS LOKAL*/
    int i;

    /* ALGORITMA */
    for (i=0; i<MaxPengguna; i++){
        (*d).parent[i] = UndefinedParent;
        (*d).size[i] = 0;
    }
}

/* ********** SET BARU ********** */
void createSet(DSU *d, idPengguna id){
/* I.S. set untuk pengguna id belum terdefinisi */
/* F.S. parent dari v adalah dirinya sendiri, size dari v adalah 1 */
    /* KAMUS LOKAL*/

    /* ALGORITMA */
    (*d).parent[id] = id;
    (*d).size[id] = 1;
}

/* ********** PRIMITIF DSU ********** */
idPengguna findRoot(DSU d, idPengguna id){
/* mengembalikan id dari root set pengguna */
    /* KAMUS LOKAL*/

    /* ALGORITMA */
    while(id != d.parent[id]){
        id = d.parent[id];
    }
    return id;
}

boolean isSameRoot(DSU d, idPengguna s1, idPengguna s2){
/* mengembalikan apakah kedua pengguna berada pada set yang sama*/
    return(findRoot(d, s1) == findRoot(d, s2));
}

void mergeSet(DSU *d, idPengguna s1, idPengguna s2){
/* I.S. kedua pengguna berada pada set berbeda, atau sama */
/* F.S. jika berbeda, set dengan size terpendek disambung ke set terpanjang */
    /* KAMUS LOKAL*/

    /* ALGORITMA */
    if (!isSameRoot(*d, s1, s2)){
        if (d->size[s1] > d->size[s2]){
            d->parent[s2] = s1;
            d->size[s1] += d->size[s2];
        } else {
            d->parent[s1] = s2;
            d->size[s2] += d->size[s1];
        }
    }
}