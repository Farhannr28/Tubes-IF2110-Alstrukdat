#ifndef KICAUAN_METHODS_H
#define KICAUAN_METHODS_H

#include "kicauan.h"
#include "../ListDinamis/listdin.h"

/* ********** SELEKTOR ********** */
#define ID(k) (k).id
#define AUHTOR(k) (k).idPembuat
#define TEXT(k) (k).text
#define LIKE(p) (p).like
#define TIME(p) (p).waktu
#define ELMTKicauan(l, i) ELMTDinamik(l, i).k

void createKicauan(Kicauan *k, int authorId, Word kicau);
void sukaKicauan(ListDin *l, int kicauanId);
void ubahKicauan(ListDin *l, int kicauanId, Word kicauBaru);
void showKicauan(Kicauan k, Word Author);
void insertKicauanLast(ListDin *l, Kicauan k);
boolean getKicauanById(ListDin l, Kicauan *k, int id);
boolean getKicauanByUserId(ListDin l, Kicauan *k, int userId);

#endif
