#ifndef BALASAN_H
#define BALASAN_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/datetime.h"

typedef struct balasan{
    int id;
    int idPembuat;
    Word author;
    Word text;
    DATETIME waktu;
} Balasan;

void createBalasan(Balasan *b, int authorId, Word Author, Word balas);

void showBalasan(Balasan b, int depth, boolean visible);

#endif