#include "kicauan.h"
#include "kicauan_methods.h"
#include <stdio.h>
#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/datetime.h"
#include "../ListDinamis/listdin.h"

int idKicauan = 1;

void createKicauan(Kicauan *k, int authorId, Word kicau){
    k->id = idKicauan;
    idKicauan++;
    k->text = kicau;
    k->idPembuat = authorId;
    k->like = 0;
    k->waktu = GetCurrentDateTime();
}

void sukaKicauan(ListDin *l, int kicauanId) {
    for (int i = 0; i < CAPACITY(*l); i++) {
        if(ELMTKicauan(*l, i).id == kicauanId) {
            ELMTKicauan(*l, i).like++;
        }
    }
}

void ubahKicauan(ListDin *l, int kicauanId, Word kicauBaru) {
    for (int i = 0; i < CAPACITY(*l); i++) {
        if(ELMTKicauan(*l, i).id == kicauanId) {
            ELMTKicauan(*l, i).text = kicauBaru;
        }
    }
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

void insertKicauanLast(ListDin *l, Kicauan k) {
    ElTypeListDin el;
    el.k = k;
    insertDinamikLast(l, el);
}


/* ********** Get ********** */
boolean getKicauanById(ListDin l, Kicauan *k, int id){
    for (int i = 0; i < l.capacity; i++) {
        if(ELMTKicauan(l, i).id == id) {
            *k = ELMTKicauan(l, i);
            return true;
        }
    }
    return false;
}

boolean getKicauanByUserId(ListDin l, Kicauan *k, int userId) {
    for (int i = 0; i < l.capacity; i++) {
        if(ELMTKicauan(l, i).idPembuat == userId) {
            *k = ELMTKicauan(l, i);
            return true;
        }
    }
    return false;
}
