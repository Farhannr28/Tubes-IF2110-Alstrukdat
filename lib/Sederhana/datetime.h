/* MODUL DATETIME */

#ifndef DATETIME_H
#define DATETIME_H

#include "../utility/boolean.h"
#include "time.h"

typedef struct
{
    int DD;   /* integer [1..31] */
    int MM;   /* integer [1..12] */
    int YYYY; /* integer [1900..2030] */
    Time T;
} DateTime;

/* SELEKTOR */
#define Day(D) (D).DD
#define Month(D) (D).MM
#define Year(D) (D).YYYY
#define Time(D) (D).T

/* PRIMITIF */

/* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
int GetMaxDay(int M, int Y);

/* Mengirim true jika D,M,Y,h,m,s dapat membentuk D yang valid */
boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s);

/* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
void CreateDateTime(DateTime *D, int DD, int MM, int YYYY, int hh, int mm, int ss);
/* Prekondisi : DD, MM, YYYY, h, m, s valid untuk membentuk DATETIME */

/* Baca DateTime */
void BacaDateTime(DateTime *D);
/* I.S. : D tidak terdefinisi */
/* F.S. : D terdefinisi dan merupakan DATETIME yang valid */

/* Tulis DateTime */
void TulisDateTime(DateTime D);
/* I.S. : D sembarang */
/* F.S. : Nilai D ditulis dg format DD/MM/YYYY HH:MM:SS */

#endif