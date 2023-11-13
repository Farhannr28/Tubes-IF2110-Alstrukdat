#ifndef KICAUAN_H
#define KICAUAN_H

#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/datetime.h"

typedef struct kicauan{
    int id;
    int idPembuat;
    Word text;
    int like;
    DATETIME waktu;
} Kicauan;

#define ID(k) (k).id
#define AUHTOR(k) (k).idPembuat
#define TEXT(k) (k).text
#define LIKE(p) (p).like
#define TIME(p) (p).waktu

void createKicauan(int id, int Author, Word kicau);
/* I.S. Kicauan dengan id tersebut belum ada */
/* F.S. Terbentuk kicauan dengan id tersebut dengan waktu pembuatan serta like 0 */

void sukaKicauan(int id);
/* I.S. Kicauan dengan id tersebut tersedia dan author bukan akun privat yang belum berteman dengan user sekarang */
/* F.S. Like dari kicauan dengan id tersebut bertambah 1 */

void ubahKicauan(int id, Word kicauBaru);
/* I.S. Kicauan dengan id tersebut tersedia */
/* F.S. Text dari kicauan dengan id tersebut berubah menjadi kicauBaru, tanggal tidak berubah */

void showKicauan(int id);
/* I.S. Kicauan dengan id tersebut tersedia dan pengguna saat ini sudah berteman dengan author */
/* F.S. Kicauan ditampilkan kepada pengguna sesuai format */

#endif