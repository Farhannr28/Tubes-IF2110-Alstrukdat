#ifndef Config_H
#define Config_H
#include "../ListLinier/listlinier.h"
#include "../ListStatik/liststatik.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../Utasan/Utasan.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../utility/boolean.h"

boolean MuatUtas(char *namafolder, ListLinearUtas *l1);
boolean MuatPengguna(char *namafolder, ListStatik* listUser, Graph* networkPertemanan);
boolean MuatKicau(char *namafolder, ListDin* ListKicauan, ListStatik ListUser, MaxHeap* fyb);
boolean MuatBalas(char *namafolder, ListDin* listKicauan);
boolean MuatDraf(char *namafolder, ListStatik *listUser);

#endif
