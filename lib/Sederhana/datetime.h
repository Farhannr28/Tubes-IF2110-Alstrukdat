/* MODUL DATETIME */

#ifndef DATETIME_H
#define DATETIME_H

#include "../utility/boolean.h"
#include "ctime.h"

typedef struct
{
    int DD;   /* integer [1..31] */
    int MM;   /* integer [1..12] */
    int YYYY; /* integer [1900..2030] */
    TIME T;
} DATETIME;

/* SELEKTOR */
#define Day(D) (D).DD
#define Month(D) (D).MM
#define Year(D) (D).YYYY
#define Time(D) (D).T

/* PRIMITIF */

/* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
int GetMaxDay(int M, int Y);

/* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
void CreateDateTime(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss);
/* Prekondisi : DD, MM, YYYY, h, m, s valid untuk membentuk DATETIME */

/* Tulis DateTime */
void TulisDateTime(DATETIME D);
/* I.S. : D sembarang */
/* F.S. : Nilai D ditulis dg format DD/MM/YYYY HH:MM:SS */

/* Mengirimkan true jika D1=D2, false jika tidak */
boolean DEQ(DATETIME D1, DATETIME D2);
/* Mengirimkan true jika D1 tidak sama dengan D2 */
boolean DNEQ(DATETIME D1, DATETIME D2);
/* Mengirimkan true jika D1<D2, false jika tidak */
boolean DLT(DATETIME D1, DATETIME D2);
/* Mengirimkan true jika D1>D2, false jika tidak */
boolean DGT(DATETIME D1, DATETIME D2);

DATETIME GetCurrentDateTime();

void format_datetime(const DATETIME *dt, char *buffer, int bufferSize);
#endif
