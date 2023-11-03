/* MODUL MATRIKS */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "../utility/boolean.h"

/* Baris maksimum Matriks */
#define ROW_CAP 100
/* Kolom maksimum Matriks */
#define COL_CAP 100

typedef int IdxType;
typedef char ElType;
typedef struct
{
   ElType mem[ROW_CAP][COL_CAP];
   int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
   int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matriks;

#define ROW_EFF(M) (M).rowEff
#define COL_EFF(M) (M).colEff
#define ELMT(M, i, j) (M).mem[(i)][(j)]

/* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
void createMatriks(int nRows, int nCols, Matriks *m);
/* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks m sesuai dengan definisi di atas terbentuk */

/* Mengirimkan Index baris terbesar m */
IdxType getLastIdxRow(Matriks m);
/* Mengirimkan Index kolom terbesar m */
IdxType getLastIdxCol(Matriks m);
/* Mengirimkan true jika i, j adalah Index efektif bagi m */
boolean isIdxEff(Matriks m, IdxType i, IdxType j);

/* Melakukan pembacaan masukan Matriks */
void readMatrix(Matriks *m, int nRow, int nCol);

/* Menampilkan Matriks */
void displayMatrix(Matriks m);
/* I.S. m terdefinisi */
/* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */


#endif