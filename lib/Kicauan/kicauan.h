#ifndef KICAUAN_H
#define KICAUAN_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/datetime.h"

typedef struct kicauan{
    int id;
    int idPembuat;
    Word text;
    int like;
    DATETIME waktu;
} Kicauan;

#endif
