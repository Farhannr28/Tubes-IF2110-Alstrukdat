#ifndef SIMPAN_H
#define SIMPAN_H
#include "../ListLinier/listlinier.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../MaxHeap/maxheap.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../utility/boolean.h"
#include "../Utasan/Utasan.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
void str_copy(char *dest, const char *src, size_t dest_size);
void str_concat(char *dest, const char *src, size_t dest_size);
void SIMPANUTAS(ListLinearUtas ListUtas, const char *folderName);
void simpanPengguna(char *namafolder, ListStatik listUser, Graph networkPertemanan);
void simpanKicauan(char *namafolder, ListDin* ListKicauan, ListStatik ListUser, MaxHeap* fyb);
void SimpanDraf (ListStatik listUser, const char *folderName);
void simpanBalasan(char *namafolder, ListDin* listKicauan, ListStatik ListUser);
#endif
