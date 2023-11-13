#include <stdio.h>
#include <time.h>
#include "time.h"
#include "datetime.h"

/* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
int GetMaxDay(int M, int Y) {
    int max;
    boolean leap;
    if (Y%400 == 0) {
        leap = true;
    } else if (Y%100 == 0) {
        leap = false;
    } else if (Y%4 == 0) {
        leap = true;
    } else {
        leap = false;
    }
    if (M == 1 || M == 3 || M == 5 || M == 7 || M == 8 || M == 10 || M == 12) {
        max = 31;
    } else if (M == 4 || M == 6 || M == 9 || M == 11) {
        max = 30;
    } else {
        if (leap) {
            max = 29;
        } else {
            max = 28;
        }
    }
    return max;
}

/* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
void CreateDATETIME(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss) {
    Day(*D) = DD;
    Month(*D) = MM;
    Year(*D) = YYYY;
    TIME T;
    CreateTime(&T, hh, mm, ss);
    Time(*D) = T;
}

void TulisDATETIME(DATETIME D) {
    int DD, MM, YY, hh, mm, ss;
    TIME T;
    DD = Day(D);
    MM = Month(D);
    YY = Year(D);
    T = Time(D);
    hh = Hour(T);
    mm = Minute(T);
    ss = Second(T);
    printf("%d/%d/%d %d:%d:%d", DD, MM, YY, hh, mm, ss);
}

boolean DEQ(DATETIME D1, DATETIME D2) {
    return ((Day(D1) == Day(D2)) && (Month(D1) == Month(D2)) && (Year(D1) == Year(D2)) && TEQ(Time(D1), Time(D2)));
}

boolean DNEQ(DATETIME D1, DATETIME D2) {
    return !DEQ(D1, D2);
}

boolean DLT(DATETIME D1, DATETIME D2) {
    boolean late = true;
    if (Year(D1) == Year(D2)) {
        if (Month(D1) == Month(D2)) {
            if (Day(D1) == Day(D2)) {
                if (!TLT(Time(D1), Time(D2))) {
                    late = false;
                }
            } else if (Day(D1) > Day(D2)) {
                late = false;
            }
        } else if (Month(D1) > Month(D2)) {
            late = false;
        }
    } else if (Year(D1) > Year(D2)) {
        late = false;
    }
    return late;
}

boolean DGT(DATETIME D1, DATETIME D2) {
    return (!DLT(D1, D2) && !DEQ(D1, D2));
}