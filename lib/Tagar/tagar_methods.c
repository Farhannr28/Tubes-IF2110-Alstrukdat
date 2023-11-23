#include "tagar_methods.h"
#include "../ListStatik/liststatik.h"
#include "../MesinKata/wordmachine.h"
#include "../Pengguna/pengguna.h"
#include "../Pengguna/pengguna_methods.h"
#include "tagar.h"
#include <stdlib.h>

int hashFunction(Word tagar) {
  int hash = 0;

  for (int i = 0; i < tagar.Length; i++) {
    hash += tagar.TabWord[i];
  }

  return hash % CAPACITYListStatik;
}

AddressKicauanNode newKicauanNode(int kicauanId) {
  AddressKicauanNode k = malloc(sizeof(KicauanNode));
  if (k != NULL) {
    InfoKicauan(k) = kicauanId;
    NextKicauan(k) = NULL;
  }
  return k;
}

AddressTagar newTagar(AddressKicauanNode k, Word isiTagar) {
  AddressTagar t = malloc(sizeof(Tagar));
  if (t != NULL) {
    DataTagar(t) = k;
    IsiTagar(t) = isiTagar;
    NextTagar(t) = NULL;
  }
  return t;
}

void addKicauanPadaTagar(ListStatik *listTagar, int kicauanId, Word isiTagar) {
  AddressKicauanNode kicauanNodeBaru = newKicauanNode(kicauanId);
  AddressTagar tagarBaru = newTagar(kicauanNodeBaru, isiTagar);
  int idx = hashFunction(isiTagar);
  if (isListStatikEmptyAt(*listTagar, idx)) {
    ListStatikElType newElement;
    newElement.content.t = tagarBaru;
    newElement.isValid = true;
    insertForceAtListStatik(listTagar, newElement, idx);
  } else {
    ListStatikElType *elAtIdx = &ELMTStatik(*listTagar, idx);
    if (WordCmpWord(elAtIdx->content.t->isiTagar, isiTagar)) {
      AddressKicauanNode kicauanNode = DataTagar(elAtIdx->content.t);
      while (NextKicauan(kicauanNode) != NULL) {
        kicauanNode = NextKicauan(kicauanNode);
      }
      NextKicauan(kicauanNode) = kicauanNodeBaru;
    } else {
      // hash collision
      AddressTagar t = elAtIdx->content.t;
      while (NextTagar(t) != NULL) {
        t = NextTagar(t);
      }
      NextTagar(t) = tagarBaru;
    }
  }
}

void showKicauanDenganTagar(ListStatik listTagar, ListStatik listUser,
                            ListDin listKicauan, Word isiTagar) {
  int idx = hashFunction(isiTagar);
  if (isListStatikEmptyAt(listTagar, idx)) {
    printf("Tidak ditemukan kicauan dengan tagar #");
    PrintWord(isiTagar);
    printf("!\n");
  } else {
    AddressTagar tagar = ELMTStatik(listTagar, idx).content.t;
    boolean found = false;

    while (tagar != NULL && !found) {
      if (WordCmpWord(tagar->isiTagar, isiTagar)) {
        found = true;
      } else {
        tagar = NextTagar(tagar);
      }
    }

    if (!found) {
      printf("Tidak ditemukan kicauan dengan tagar #");
      PrintWord(isiTagar);
      printf("!\n");
    } else {
      AddressKicauanNode kicauanNode = DataTagar(tagar);
      while (kicauanNode != NULL) {
        Kicauan kicauan;
        getKicauanById(listKicauan, &kicauan, kicauanNode->kicauanId);
        Pengguna pengkicau;
        GetUserById(listUser, &pengkicau, kicauan.idPembuat);
        showKicauan(kicauan, pengkicau.Nama);
        kicauanNode = NextKicauan(kicauanNode);
      }
    }
  }
}
