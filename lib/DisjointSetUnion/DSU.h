#ifndef DSU_H
#define DSU_H

#include "../utility/boolean.h"

/*  Kamus Umum */
#define MaxPengguna 20
#define UndefinedParent -1
/* Banyaknya pengguna maksimum */

typedef int idPengguna;
typedef struct {
  idPengguna parent[MaxPengguna];
  int size[MaxPengguna];
} DSU;

/* ********** KONSTRUKTOR ********** */
void CreateDSU(DSU *d);
/* I.S. d sembarang */
/* F.S. Terbentuk DSU d kosong dengan seluruh parent & size 0 */

/* ********** SET BARU ********** */
void createSet(DSU *d, idPengguna id);
/* I.S. set untuk pengguna id belum terdefinisi */
/* F.S. parent dari v adalah dirinya sendiri, size dari v adalah 1 */

/* ********** PRIMITIF DSU ********** */
idPengguna findRoot(DSU d, idPengguna id);
/* mengembalikan id dari root set pengguna */

boolean isSameRoot(DSU d, idPengguna s1, idPengguna s2);
/* mengembalikan apakah kedua pengguna berada pada set yang sama*/

void mergeSet(DSU *d, idPengguna s1, idPengguna s2);
/* I.S. kedua set berbeda */
/* F.S. set dengan size terpendek disambung ke set terpanjang */

int getLength(DSU d, idPengguna id);

void printSet(DSU d, idPengguna id);

#endif
