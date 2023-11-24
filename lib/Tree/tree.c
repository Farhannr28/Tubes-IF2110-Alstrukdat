#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

AddressTreeNode newTreeNode(ElTypeTree val){
/* Alokasi sebuah address p, bernilai tidak NULL jika berhasil */
/* Mengirimkan address hasil alokasi sebuah elemen bernilai val
   Jika alokasi berhasil, maka address tidak NULL, dan misalnya 
   menghasilkan p, maka p↑.info=val, p↑.left=NULL, p↑.right=NULL 
   Jika alokasi gagal, mengirimkan NULL */
	AddressTreeNode p = (AddressTreeNode) malloc(sizeof(TreeNode));
    if (p != NULL){
		INFO(p) = val;
		CHILD(p) = NULL;
		SIBL(p) = NULL;
	} else {
		printf("Memory allocation failed\n");
	}
	return p;
}

void deallocTreeNode (AddressTreeNode p){
/* I.S. p terdefinisi 
   F.S. p dikembalikan ke sistem 
   Melakukan dealokasi/pengembalian address p */
	free(p);
}

boolean isTreeEmpty (BinTree p){
/* Mengirimkan true jika p adalah pohon biner yang kosong */
	return p == NULL;
}

boolean isOneElmt (BinTree p){
/* Mengirimkan true jika p tidak kosong dan hanya terdiri atas 1 elemen */
	return (p != NULL && (CHILD(p) == NULL && SIBL(p) == NULL));
}

boolean noSibling (BinTree p){
	return (SIBL(p) == NULL);
}

boolean noChild (BinTree p){
	return (CHILD(p) == NULL);
}

boolean isBinary (BinTree p){
/* Mengirimkan true jika pohon biner tidak kosong, p adalah pohon biner: 
  mempunyai subpohon kiri dan subpohon kanan */
	return (!noSibling(p) && !noChild(p));
}

void deleteTree (BinTree p){
/* Menghapus Tree secara cascade */
	if(!isTreeEmpty(p)){
		deleteTree(CHILD(p));
		deleteTree(SIBL(p));
		deallocTreeNode(p);
	}
}

void insertTreeNode(TreeNode* n, BinTree t, int idParent){
	if (isTreeEmpty(t)){
		t = n;
	} else {
		AddressTreeNode parent;
		AddressTreeNode temp;
		if (idParent == -1){
			parent = t;
		} else {
			parent = searchBalasanById(t, idParent);
		}
		if (noChild(parent)){
			CHILD(parent) = n;
		} else {
			temp = CHILD(parent);
			while (!noSibling(temp)){
				temp = SIBL(temp);
			}
			SIBL(temp) = n;
		}
	}
}

/* ****** Display Tree ***** */
void recursivePrint(BinTree p, int level, boolean* list){
	if(!isTreeEmpty(p)){
		Balasan b = INFO(p);
		showBalasan(b, level, list[b.idPembuat]);
		recursivePrint(CHILD(p), level + 1, list);
		recursivePrint(SIBL(p), level, list);
	}
}

void printTree(BinTree p, boolean* list){
/* I.S. p terdefinisi, ada jarak indentasi (spasi) */
/* F.S. Semua simpul p sudah ditulis dengan indentasi (spasi) */
	recursivePrint(p, 0, list);
}

/* Searching Balasan */
AddressTreeNode searchBalasanById(BinTree t, int x){
	if (isTreeEmpty(t)){
		return NULL;
	}
	if (INFO(t).id == x){
		return t;
	}
	AddressTreeNode ans = NULL;
	if(!noChild(t)){
		ans = searchBalasanById(CHILD(t), x);
	}
	if(!noSibling(t)){
		ans = searchBalasanById(SIBL(t), x);
	}
	return ans;
}