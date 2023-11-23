#include "maxheap.h"
#include "../Kicauan/kicauan.h"
#include "../ListStatik/liststatik.h"
#include "../MesinKata/wordmachine.h"
#include "../Pengguna/pengguna.h"
#include "../Pengguna/pengguna_methods.h"
#include <stdio.h>
#include <stdlib.h>

MaxHeap *createMaxHeap() {
  MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
  heap->kicauan = NULL;
  heap->capacity = 0;
  heap->size = 0;
  return heap;
}

void swap(Kicauan *a, Kicauan *b) {
  Kicauan temp = *a;
  *a = *b;
  *b = temp;
}

void heapifyUp(MaxHeap *heap, int index) {
  int parent = (index - 1) / 2;
  while (index > 0 && heap->kicauan[index].like > heap->kicauan[parent].like) {
    swap(&heap->kicauan[index], &heap->kicauan[parent]);
    index = parent;
    parent = (index - 1) / 2;
  }
}

void insertKicauanToHeap(MaxHeap *heap, Kicauan kicauan) {
  if (heap->size == heap->capacity) {
    heap->capacity = (heap->capacity == 0) ? 1 : 2 * heap->capacity;
    heap->kicauan = (Kicauan *)realloc(heap->kicauan, heap->capacity * sizeof(Kicauan));
  }

  heap->kicauan[heap->size] = kicauan;
  heap->size++;
  heapifyUp(heap, heap->size - 1);
}

void heapifyDown(MaxHeap *heap, int index) {
  int left = 2 * index + 1;
  int right = 2 * index + 2;
  int largest = index;

  if (left < heap->size && heap->kicauan[left].like > heap->kicauan[largest].like) {
    largest = left;
  }

  if (right < heap->size && heap->kicauan[right].like > heap->kicauan[largest].like) {
    largest = right;
  }

  if (largest != index) {
    swap(&heap->kicauan[index], &heap->kicauan[largest]);
    heapifyDown(heap, largest);
  }
}

void updateLikeInHeap(MaxHeap *heap, int kicauanId) {
  for (int i = 0; i < heap->size; i++) {
        if (heap->kicauan[i].id == kicauanId) {
            heap->kicauan[i].like++;
            heapifyDown(heap, 0);
            return;
        }
    }
}

MaxHeap *copyMaxHeap(const MaxHeap *sourceHeap) {
  // Create a new MaxHeap
  MaxHeap *newHeap = createMaxHeap();

  // Allocate memory for the kicauan array in the new heap
  newHeap->kicauan = (Kicauan *)malloc(sourceHeap->capacity * sizeof(Kicauan));
  if (newHeap->kicauan == NULL) {
    fprintf(stderr, "Memory allocation error in copyMaxHeap\n");
    exit(EXIT_FAILURE);
  }

  // Copy the elements from the source heap to the new heap
  for (int i = 0; i < sourceHeap->size; i++) {
    newHeap->kicauan[i] = sourceHeap->kicauan[i];
  }

  // Set the size and capacity in the new heap
  newHeap->size = sourceHeap->size;
  newHeap->capacity = sourceHeap->capacity;

  return newHeap;
}

Kicauan extractMax(MaxHeap* heap) {
    if (heap->size == 0) {
        Kicauan dummy;
        return dummy;
    }

    Kicauan max = heap->kicauan[0];
    heap->kicauan[0] = heap->kicauan[heap->size - 1];
    heap->size--;

    heapifyDown(heap, 0);
    return max;
}

void tampilkanKicauanTerbaik(MaxHeap heap, ListStatik listUser) {
  MaxHeap *copiedHeap = copyMaxHeap(&heap);
  int totalKicauan = heap.size < 8 ? heap.size : 8;
  printf("Berikut %d kicauan dengan like tertinggi di FYB\n\n", totalKicauan);

  for (int i = 0; i < totalKicauan; i++) {
    Kicauan kicauan = extractMax(copiedHeap);
    printf("Kicauan %d\n", i+1);
    Pengguna pengkicau;
    GetUserById(listUser, &pengkicau, kicauan.idPembuat);
    printf("| ");PrintWord(pengkicau.Nama);printf("\n");
    printf("| ");TulisDateTime(kicauan.waktu);printf("\n");
    printf("| ");PrintWord(kicauan.text);printf("\n");
    if(!WordCmp(kicauan.tagar, "")) {
        printf("| #");PrintWord(kicauan.tagar);printf("\n");
    }
    printf("| Disukai: %d\n", kicauan.like);
    printf("\n\n");
  }
}

