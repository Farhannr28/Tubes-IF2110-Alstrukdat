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

void displayMatrix(Matriks m) {
    int i, j;
    for (i=0; i<ROW_EFF(m); i++) {
        for (j=0; j<COL_EFF(m)*2; j++) {
            if (j!=COL_EFF(m)-1) {
                printf("%c", ELMT(m, i, j));
            } else {
                printf("%c", ELMT(m, i, j));
            }
        }
        printf("\n");
    }
}

void MatriksFromWord(Matriks *m, Word w) {
    // I.S assuming kalau misalnya m ini fixed size dan input selalu bener
    createMatriks(5, 10, m);
    int i = 0;
    int j = 0;

    int wordIdx = 0;
    while (wordIdx < w.Length) {
        if(w.TabWord[wordIdx] == '\n') {
            j = 0;
            i++;
        } else {
            ELMT(*m, i, j) = w.TabWord[wordIdx];
            j++;
        } wordIdx++;
    }
}

void saveMatrixToFile(Matriks m, FILE *file) {
    int i, j;
    fprintf(file, "\n");
    for (i=0; i<ROW_EFF(m); i++) {
        for (j=0; j<COL_EFF(m)*2; j++) {
            if (j!=COL_EFF(m)-1) {
                fprintf(file, "%c", ELMT(m, i, j));
            } else {
                fprintf(file, "%c", ELMT(m, i, j));
            }
        }
        fprintf(file, "\n");
    }
}

