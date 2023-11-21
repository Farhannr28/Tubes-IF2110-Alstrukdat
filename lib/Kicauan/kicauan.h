#ifndef KICAUAN_H
#define KICAUAN_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/datetime.h"
#include "../UndirectedGraph/graph.h"
#include "../ListStatik/liststatik.h"

typedef struct kicauan{
    boolean isValid;
    int id;
    int idPembuat;
    Word text;
    int like;
    DATETIME waktu;
} Kicauan;

/* ********** SELEKTOR ********** */
#define ID(k) (k).id
#define AUHTOR(k) (k).idPembuat
#define TEXT(k) (k).text
#define LIKE(p) (p).like
#define TIME(p) (p).waktu

void createKicauan(Kicauan *k, int authorId, Word kicau);

void sukaKicauan(Kicauan *k);

void ubahKicauan(Kicauan *k, Word kicauBaru);
/* I.S. Kicauan dengan id tersebut tersedia */
/* F.S. Text dari kicauan dengan id tersebut berubah menjadi kicauBaru, tanggal tidak berubah */

void showKicauan(Kicauan k, Pengguna Author);
#endif