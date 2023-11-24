#include <stdio.h>
#include <stdlib.h>
#include "balasan.h"
#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/datetime.h"

int idBalasan = 0;

void createBalasan(Balasan *b, int authorId, Word Author, Word balas){
    b->id = idBalasan;
    idBalasan++;
    b->idPembuat = authorId;
    b->author = Author;
    b->text = balas;
    b->waktu = GetCurrentDateTime();
}

void showBalasan(Balasan b, int depth, boolean visible){
    printf("%*c ID = %d\n", depth * 3 + 1, '|', b.id);
    if (visible){
        printf("%*c ", depth * 3 + 1, '|'); PrintWord(b.author); printf("\n");
        printf("%*c ", depth * 3 + 1, '|'); TulisDateTime(b.waktu);printf("\n");
        printf("%*c ", depth * 3 + 1, '|'); PrintWord(b.text); printf("\n");
    } else {
        printf("%*c ", depth * 3 + 1, '|'); printf("PRIVAT\n");
        printf("%*c ", depth * 3 + 1, '|'); printf("PRIVAT\n");
        printf("%*c ", depth * 3 + 1, '|'); printf("PRIVAT\n");
    }
    printf("\n");
}