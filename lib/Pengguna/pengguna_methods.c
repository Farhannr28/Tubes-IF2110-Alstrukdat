#include "pengguna_methods.h"
#include "../DisjointSetUnion/DSU.h"
#include "../PriorityQueue/prioqueue.h"
#include "../pcolor/pcolor.h"
#include "pengguna.h"

int userId = 0;

boolean UsernameTaken(ListStatik l, Word nama) {
  int length = ListStatikLength(l);
  for (int i = 0; i < length; i++) {
    Pengguna currentPengguna = ELMTPengguna(l, i);
    if (WordCmpWord(currentPengguna.Nama, nama)) {
      return true;
    }
  }
  return false;
}

boolean UserAndPasswordMatch(ListStatik l, Word nama, Word password) {
  int length = ListStatikLength(l);
  for (int i = 0; i < length; i++) {
    Pengguna currentPengguna = ELMTPengguna(l, i);
    // TODO: add hash
    if (WordCmpWord(currentPengguna.KataSandi, password) &&
        WordCmpWord(currentPengguna.Nama, nama)) {
      return true;
    }
  }
  return false;
}

void CreatePengguna(Pengguna *p, Word Nama, Word KataSandi) {
  AssignWord(&p->JenisAkun, "PUBLIK");
  p->isValid = true;
  p->Nama = Nama;
  p->KataSandi = KataSandi;
  p->id = userId;
  userId++;
  CreateProfil(&p->FotoProfil);
  CreatePriorityQueue(&p->PermintaanBerteman);
  CreateStack(&p->Draf);
}

void InvalidateUser(Pengguna *p) { p->isValid = false; }

boolean IsUserValid(Pengguna p) { return p.isValid; }

boolean GetUserByName(ListStatik l, Pengguna *p, Word nama) {
  int length = ListStatikLength(l);
  for (int i = 0; i < length; i++) {
    Pengguna currentPengguna = ELMTPengguna(l, i);
    if (WordCmpWord(currentPengguna.Nama, nama)) {
      *p = currentPengguna;
      return true;
    }
  }
  return false;
}

boolean GetUserById(ListStatik l, Pengguna *p, int id) {
  int length = ListStatikLength(l);
  for (int i = 0; i < length; i++) {
    Pengguna currentPengguna = ELMTPengguna(l, i);
    if (currentPengguna.id == id) {
      *p = currentPengguna;
      return true;
    }
  }
  return false;
}

boolean GetMutableUserByName(ListStatik *l, Pengguna **p, Word nama) {
  int length = ListStatikLength(*l);
  for (int i = 0; i < length; i++) {
    if (WordCmpWord(ELMTPengguna(*l, i).Nama, nama)) {
      *p = &l->elements[i].content.p;
      return true;
    }
  }
  return false;
}

void DisplayProfile(Pengguna p) {
  Matriks m = p.FotoProfil;
  for (int i = 0; i < ROW_EFF(m); i++) {
    for (int j = 0; j < COL_EFF(m); j++) {
      boolean isR = ELMT(m, i, j) == 'R';
      boolean isG = ELMT(m, i, j) == 'G';
      boolean isB = ELMT(m, i, j) == 'B';
      if (isR) {
        print_red(ELMT(m, i, j + 1));
      }
      if (isG) {
        print_green(ELMT(m, i, j + 1));
      }
      if (isB) {
        print_blue(ELMT(m, i, j + 1));
      }
    }
    printf("\n");
  }
}

void ChangeUserInfo(Pengguna *p, boolean isValid, Word Nama, Word KataSandi,
                    Word NoHP, Word BioAkun, Word Weton, Word JenisAkun,
                    Matriks FotoProfil) {
  p->isValid = isValid;
  p->Nama = Nama;
  p->KataSandi = KataSandi;
  p->NoHP = NoHP;
  p->BioAkun = BioAkun;
  p->Weton = Weton;
  p->FotoProfil = FotoProfil;
}

void ChangePrivacy(Pengguna *p, boolean private_) {
  if (!private_) {
    AssignWord(&p->JenisAkun, "PUBLIK");
  } else {
    AssignWord(&p->JenisAkun, "PRIVATE");
  }
}

boolean UserIsPrivate(Pengguna p) { return WordCmp(p.JenisAkun, "PRIVATE"); }

void CreateProfil(Matriks *m) {
  createMatriks(5, 10, m);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      if (j % 2 == 0)
        ELMT(*m, i, j) = 'R';
      else
        ELMT(*m, i, j) = '*';
    }
  }
}

void UpdateProfil(Pengguna *p, Matriks m) {
  Matriks *pm = &p->FotoProfil;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      ELMT(*pm, i, j) = ELMT(m, i, j);
    }
  }
}

boolean TambahTeman(Pengguna from, Pengguna *to) {
  if (isEmpty(from.PermintaanBerteman)) {
    enqueue(&to->PermintaanBerteman, from.Nama,
            length_queue(from.PermintaanBerteman));
    return true;
  }
  return false;
}

Address GetPermintaanTeratas(Pengguna p) {
  return FIRST_QUEUE(p.PermintaanBerteman);
}

void PrintListTeman(Pengguna p) {
  PriorityQueue temp;
  CreatePriorityQueue(&temp);
  while (!isEmpty(p.PermintaanBerteman)) {
    Address teman = GetPermintaanTeratas(p);
    printf("| ");
    PrintWord(DATA(teman));
    printf("\n");
    printf("| Jumlah teman: %d \n", PRIORITY(teman));
    printf("\n");
    enqueue(&temp, DATA(teman), PRIORITY(teman));
    dequeue(&p.PermintaanBerteman);
  }
  while (!isEmpty(temp)) {
    Address teman = FIRST_QUEUE(temp);
    enqueue(&p.PermintaanBerteman, DATA(teman), PRIORITY(teman));
    dequeue(&temp);
  }
}

/* Fungsi untuk menambahkan edge/sisi (hubungan pertemanan) pada graph */
void addTeman(Graph *graph, DSU *kelompokTeman, int index_user_asal,
              int index_user_tujuan) {
  ELMT_GRAPH(*graph, index_user_asal, index_user_tujuan) = 1;
  ELMT_GRAPH(*graph, index_user_tujuan, index_user_asal) = 1;
  mergeSet(kelompokTeman, index_user_asal, index_user_tujuan);
}

/* Fungsi untuk menghapus teman */
void hapusTeman(Graph *graph, int index_user_asal, int index_user_tujuan) {
  ELMT_GRAPH(*graph, index_user_asal, index_user_tujuan) = 0;
  ELMT_GRAPH(*graph, index_user_tujuan, index_user_asal) = 0;
}

/* Fungsi untuk mencetak daftar teman */
void printTeman(ListStatik listUser, Graph graph, Pengguna p) {
  int j = 0;
  int temanUser = jumlahTeman(graph, p.id);
  if (temanUser == 0) {
    PrintWord(p.Nama);
    printf(" tidak memiliki teman\n");
  } else {
    PrintWord(p.Nama);
    printf(" memiliki %d teman\n", temanUser);
    printf("Daftar teman ");
    PrintWord(p.Nama);
    printf(": \n");

    for (j = 0; j < MAX_SIMPUL; j++) {
      if (ELMT_GRAPH(graph, p.id, j) == 1) {
        Pengguna teman;
        GetUserById(listUser, &teman, j);
        printf("| ");
        PrintWord(teman.Nama);
        printf("\n");
      }
    }
  }
}

boolean validateNoHP(Word noHp) {
  if (noHp.Length < 9)
    return false;
  for (int i = 0; i < noHp.Length; i++) {
    char c = noHp.TabWord[i];
    if (!(c >= '0' && c <= '9')) {
      return false;
    }
  }
  return true;
}

boolean validateWeton(Word weton) {
  if (WordCmp(weton, "Kliwon"))
    return true;
  if (WordCmp(weton, "Wage"))
    return true;
  if (WordCmp(weton, "Legi"))
    return true;
  if (WordCmp(weton, "Pahing"))
    return true;
  if (WordCmp(weton, "Pon"))
    return true;
  if (WordCmp(weton, ""))
    return true;
  return false;
}

void insertLastListPengguna(ListStatik *l, Pengguna user) {
  ListStatikElType el;
  el.isValid = true;
  el.content.p = user;
  insertLastListStatik(l, el);
}

void printKelompokTeman(ListStatik listUser, DSU d, Pengguna currentUser) {
  int length = getLength(d, currentUser.id);
  printf("Terdapat %d orang dalam Kelompok Teman ", length);
  PrintWord(currentUser.Nama);
  printf(":\n");
  int id = currentUser.id;
  idPengguna root = findRoot(d, id);
  for (int i = 0; i < MaxPengguna; i++) {
    if (d.parent[i] == root) {
      Pengguna p;
      GetUserById(listUser, &p, i);
      PrintWord(p.Nama);
      printf("\n");
    }
  }
  printf("\n");
}

void printSet(DSU d, idPengguna id) {}
int GetPenggunaIndex(ListStatik l, Word nama) {
    int length = ListStatikLength(l);
    for (int i = 0; i < length; i++) {
        Pengguna currentPengguna = ELMTPengguna(l, i);
        if (WordCmpWord(currentPengguna.Nama, nama)) {
            return i; 
        }
    }
    return -1; 
}