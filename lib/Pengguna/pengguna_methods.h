#ifndef PENGGUNA_METHODS_H
#define PENGGUNA_METHODS_H

#include "pengguna.h"
#include "../ListStatik/liststatik.h"

#define ELMTPengguna(l,i) ELMTStatikContent(l,i).p

boolean UsernameTaken(ListStatik l, Word nama);
boolean UserAndPasswordMatch(ListStatik l, Word nama, Word password);
void insertLastListPengguna(ListStatik *l, Pengguna user);
void CreatePengguna(Pengguna *p, Word Nama, Word KataSandi);
void InvalidateUser(Pengguna *p);
boolean IsUserValid(Pengguna p);
boolean GetUserByName(ListStatik l, Pengguna *p, Word nama);
boolean GetUserById(ListStatik l, Pengguna *p, int id);
boolean GetMutableUserByName(ListStatik *l, Pengguna **p, Word nama);
void DisplayProfile(Pengguna p);
void ChangeUserInfo(Pengguna *p, boolean isValid, Word Nama, Word KataSandi,
                    Word NoHP, Word BioAkun, Word Weton, Word JenisAkun,
                    Matriks FotoProfil);
void ChangePrivacy(Pengguna *p, boolean private_);
boolean UserIsPrivate(Pengguna p);
void CreateProfil(Matriks *m);
void UpdateProfil(Pengguna *p, Matriks m);
boolean TambahTeman(Pengguna from, Pengguna *to);
Address GetPermintaanTeratas(Pengguna p);
void PrintListTeman(Pengguna p);
void hapusTeman(Graph *graph, int index_user_asal, int index_user_tujuan);
void printTeman(ListStatik listUser, Graph graph, Pengguna p);
void addTeman(Graph *graph, int index_user_asal, int index_user_tujuan);
boolean validateNoHP(Word noHp);
boolean validateWeton(Word weton);

#endif
