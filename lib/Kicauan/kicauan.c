#include "kicauan.h"
#include <stdio.h>

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

void createListKicau(ListKicauan *l){
    for (int i=0;i<CAPACITYKicauan;i++){
        ELMTKicauan(*l, i).isValid = false;
    }
}

int kicauanLength(ListKicauan l){
    int listLength=0, i=0;
    if (!ELMTKicauan(l, 0).isValid){
        return 0;
    } else {
        while (ELMTKicauan(l, i).isValid && i<CAPACITYKicauan){
            listLength +=1;
            i++;
        }
    }
    return listLength;
}

boolean isKicauanEmpty(ListKicauan l){
    return (kicauanLength(l)==0);
}

boolean isKicauanFull(ListKicauan l){
    return(kicauanLength(l) == CAPACITYKicauan);
}

int getLastKicauanIndex(ListKicauan l){
    return (kicauanLength(l)-1);
}

void insertKicauan(ListKicauan *l, Kicauan k) {
   if (isKicauanEmpty(*l)) {
      ELMTKicauan(*l, 0) = k;
   }
   else if (!isKicauanFull(*l)) {
      ELMTKicauan(*l, getLastKicauanIndex(*l)+1) = k;
   }
}

boolean getKicauanById(ListKicauan l, Kicauan *k, int id) {
    for (int i = 0; i < CAPACITYKicauan; i++) {
        if(ELMTKicauan(l, i).isValid) {
            if(ELMTKicauan(l, i).id == id) {
                *k = ELMTKicauan(l, i);
                return true;
            }
        }
    }
    return false;
}

boolean getKicauanByUserId(ListKicauan l, Kicauan *k, int userId) {
    for (int i = 0; i < CAPACITYKicauan; i++) {
        if(ELMTKicauan(l, i).isValid) {
            if(ELMTKicauan(l, i).idPembuat == userId) {
                *k = ELMTKicauan(l, i);
                return true;
            }
        }
    }
    return false;
}


void sukaKicauan(ListKicauan *l, int id) {
    for (int i = 0; i < CAPACITYKicauan; i++) {
        if(ELMTKicauan(*l, i).isValid) {
            if(ELMTKicauan(*l, i).id == id) {
                ELMTKicauan(*l, i).like++;
            }
        }
    }
}

void ubahKicauan(ListKicauan *l, int id, Word kicauBaru) {
    for (int i = 0; i < CAPACITYKicauan; i++) {
        if(ELMTKicauan(*l, i).isValid) {
            if(ELMTKicauan(*l, i).id == id) {
                ELMTKicauan(*l, i).text = kicauBaru;
            }
        }
    }
}

void showVisibleKicauan(ListKicauan listKicauan, ListPengguna listUser,
                           Pengguna currentUser, Graph networkPertemanan) {
    for (int i = 0; i < CAPACITYKicauan; i++) {
        if(ELMTKicauan(listKicauan, i).isValid) {
            int idPengkicau = ELMTKicauan(listKicauan, i).idPembuat;
            boolean dariTeman = isTeman(networkPertemanan, currentUser.id, idPengkicau);
            boolean dariSendiri = currentUser.id == idPengkicau;
            if(dariSendiri || dariTeman) {
                Kicauan k = ELMTKicauan(listKicauan, i);
                printf("| ID = %d\n", k.id);
                printf("| ");
                if(dariSendiri) {
                    PrintWord(currentUser.Nama);
                } else {
                    Pengguna teman;
                    GetUserById(listUser, &teman, idPengkicau);
                    PrintWord(teman.Nama);
                } 
                printf("\n");
                printf("| ");TulisDateTime(k.waktu);printf("\n");
                printf("| ");PrintWord(k.text);printf("\n");
                printf("| Disukai: %d\n", k.like);
                printf("\n");
            } 
        }
    }
}
