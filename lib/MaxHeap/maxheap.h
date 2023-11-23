#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include "../Kicauan/kicauan.h"
#include "../ListStatik/liststatik.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Kicauan *kicauan;
  int capacity;
  int size;
} MaxHeap;

void swap(Kicauan *a, Kicauan *b);

void heapifyUp(MaxHeap *heap, int index);

void insertKicauanToHeap(MaxHeap *heap, Kicauan kicauan);

void heapifyDown(MaxHeap *heap, int index);

Kicauan extractMax(MaxHeap* heap); 

void updateLikeInHeap(MaxHeap *heap, int kicauanId);

void printHeap(MaxHeap *heap);

void tampilkanKicauanTerbaik(MaxHeap heap, ListStatik listUser);

MaxHeap *copyMaxHeap(const MaxHeap *sourceHeap);

#endif
