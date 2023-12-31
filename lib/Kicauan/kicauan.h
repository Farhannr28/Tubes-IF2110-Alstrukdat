#ifndef KICAUAN_H
#define KICAUAN_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/datetime.h"
#include "../Tree/tree.h"

typedef struct kicauan{
    int id;
    int idPembuat;
    Word text;
    int like;
    DATETIME waktu;
    BinTree treeBalasan;
    Word tagar;
} Kicauan;

#endif
