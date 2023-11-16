/* MODUL TIME */

#ifndef TIME_H
#define TIME_H

#include "../utility/boolean.h"

/* *** Definisi TYPE TIME <HH:MM:SS> *** */
typedef struct { 
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
	int SS; /* integer [0..59] */
} TIME;

/* *** Notasi Akses: selektor TIME *** */
#define Hour(T) (T).HH
#define Minute(T) (T).MM
#define Second(T) (T).SS

/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
void CreateTime (TIME * T, int HH, int MM, int SS);

/* Tulis TIME */
void TulisTIME (TIME T);

/* Konversi tipe TIME ke detik */
long TIMEToDetik (TIME T);

/* Konversi detik ke tipe TIME */
TIME DetikToTIME (long N); 

/* Mengirimkan true jika T1=T2, false jika tidak */
boolean TEQ (TIME T1, TIME T2);
/* Mengirimkan true jika T1 tidak sama dengan T2 */
boolean TNEQ (TIME T1, TIME T2);
/* Mengirimkan true jika T1<T2, false jika tidak */
boolean TLT (TIME T1, TIME T2);
/* Mengirimkan true jika T1>T2, false jika tidak */
boolean TGT (TIME T1, TIME T2);


#endif
