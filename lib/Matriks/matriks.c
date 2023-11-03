#include <stdio.h>
#include <stdlib.h>
#include "matriks.h"

void createMatriks(int nRows, int nCols, Matriks *m) {
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
    int i, j;
    for (i=0; i<ROW_EFF(*m); i++) {
        for (j=0; j<COL_EFF(*m); j++) {
            ELMT(*m, i, j) = 0;
        }
    }
}

IdxType getLastIdxRow(Matriks m) {
    return (ROW_EFF(m)-1);
}

IdxType getLastIdxCol(Matriks m) {
    return (COL_EFF(m)-1);
}

boolean isIdxEff(Matriks m, IdxType i, IdxType j) {
    return (0<=i && i<=ROW_EFF(m)-1 && 0<=j && j<=COL_EFF(m)-1);
}

void readMatrix(Matriks *m, int nRow, int nCol) {
    createMatrix(nRow, nCol, m);
    int i,j;
    for (i = 0; i < nRow; i++) {
        for (j = 0; j < nCol; j++) {
            scanf("%d", &ELMT(*m, i, j));
        }
    }
}

void displayMatrix(Matriks m) {
    int i, j;
    for (i=0; i<ROW_EFF(m); i++) {
        for (j=0; j<COL_EFF(m); j++) {
            if (j==0) {
                printf("%d", ELMT(m, i, j));
            } else {
                printf(" %d", ELMT(m, i, j));
            }
        }
        printf("\n");
    }
}