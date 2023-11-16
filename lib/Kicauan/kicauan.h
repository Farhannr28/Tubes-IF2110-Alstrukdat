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

#define CAPACITYKicauan 100

typedef struct {
  Kicauan KicauanList[CAPACITYKicauan];
} ListKicauan;

/* ********** SELEKTOR ********** */
#define ELMTKicauan(l, i) (l).KicauanList[(i)]

#define ID(k) (k).id
#define AUHTOR(k) (k).idPembuat
#define TEXT(k) (k).text
#define LIKE(p) (p).like
#define TIME(p) (p).waktu

void createKicauan(Kicauan *k, int authorId, Word kicau);
void createListKicau(ListKicauan *l);

void insertKicauan(ListKicauan *l, Kicauan k);
/* I.S. Kicauan dengan id tersebut belum ada */
/* F.S. Terbentuk kicauan dengan id tersebut dengan waktu pembuatan serta like 0 */

void sukaKicauan(ListKicauan *l, int id);
/* I.S. Kicauan dengan id tersebut tersedia dan author bukan akun privat yang belum berteman dengan user sekarang */
/* F.S. Like dari kicauan dengan id tersebut bertambah 1 */

void ubahKicauan(ListKicauan *l, int id, Word kicauBaru);
/* I.S. Kicauan dengan id tersebut tersedia */
/* F.S. Text dari kicauan dengan id tersebut berubah menjadi kicauBaru, tanggal tidak berubah */

boolean showKicauan(ListKicauan l, int id);
/* I.S. Kicauan dengan id tersebut tersedia dan pengguna saat ini sudah berteman dengan author */
/* F.S. Kicauan ditampilkan kepada pengguna sesuai format */

boolean showKicauan(ListKicauan l, int id);

void showVisibleKicauan(ListKicauan listKicauan, ListPengguna listUser,
                           Pengguna currentUser, Graph networkPertemanan);
int kicauanLength(ListKicauan l);
boolean isKicauanEmpty(ListKicauan l);
boolean isKicauanFull(ListKicauan l);
int getLastKicauanIndex(ListKicauan l);
boolean getKicauanById(ListKicauan l, Kicauan *k, int id);

#endif
