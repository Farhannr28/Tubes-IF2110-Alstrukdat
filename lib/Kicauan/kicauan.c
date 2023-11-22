#include "kicauan.h"
#include <stdio.h>
#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/datetime.h"

int idKicauan = 0;

void createKicauan(Kicauan *k, int authorId, Word kicau){
    k->id = idKicauan;
    idKicauan++;
    k->text = kicau;
    k->idPembuat = authorId;
    k->like = 0;
    k->waktu = GetCurrentDateTime();
    k->isValid = true;
}

void sukaKicauan(Kicauan *k){
    k->like++;
}

void ubahKicauan(Kicauan *k, Word kicauBaru) {
    k -> text = kicauBaru;
}

void showKicauan(Kicauan k, Word Author) {
    /* Menunjukkan Kicauan yang memang valid untuk ditunjukkan */
    printf("| ID = %d\n", k.id);
    printf("| ");
    PrintWord(Author);
    printf("\n");
    printf("| ");TulisDateTime(k.waktu);printf("\n");
    printf("| ");PrintWord(k.text);printf("\n");
    printf("| Disukai: %d\n", k.like);
    printf("\n");
}