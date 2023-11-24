/* File : tree.h */
/* ADT tree */
/* Representasi Address dengan pointer */
/* ElType adalah integer */

#ifndef TREE_H
#define TREE_H

#include "../utility/boolean.h"
#include "../Balasan/balasan.h"

/* Selektor */
#define INFO(p) (p)->info
#define SIBL(p) (p)->sibling
#define CHILD(p) (p)->child

typedef Balasan ElTypeTree;
typedef struct treeNode* AddressTreeNode;
typedef struct treeNode { 
     ElTypeTree info;
     AddressTreeNode sibling;
     AddressTreeNode child;
} TreeNode;

/* Definisi Tree */
/* Tree kosong p = NULL */

typedef AddressTreeNode BinTree;

AddressTreeNode newTreeNode(ElTypeTree val);
/* Alokasi sebuah address p, bernilai tidak NULL jika berhasil */
/* Mengirimkan address hasil alokasi sebuah elemen bernilai val
   Jika alokasi berhasil, maka address tidak NULL, dan misalnya 
   menghasilkan p, maka p↑.info=val, p↑.left=NULL, p↑.right=NULL 
   Jika alokasi gagal, mengirimkan NULL */

void deallocTreeNode (AddressTreeNode p);
/* I.S. p terdefinisi 
   F.S. p dikembalikan ke sistem 
   Melakukan dealokasi/pengembalian address p */

boolean isTreeEmpty (BinTree p);
/* Mengirimkan true jika p adalah pohon biner yang kosong */

boolean isOneElmt (BinTree p);
/* Mengirimkan true jika p tidak kosong dan hanya terdiri atas 1 elemen */

boolean noSibling (BinTree p);

boolean noChild (BinTree p);

boolean isBinary (BinTree p);
/* Mengirimkan true jika pohon biner tidak kosong, p adalah pohon biner: 
  mempunyai subpohon kiri dan subpohon kanan */

void deleteTree (BinTree p);
/* Menghapus Tree secara cascade */

void insertTreeNode(TreeNode* n, BinTree t, int idParent);

/* ****** Display Tree ***** */
void recursivePrint(BinTree p, int level, boolean* list);

void printTree(BinTree p, boolean* list);
/* I.S. p terdefinisi, ada jarak indentasi (spasi) */
/* F.S. Semua simpul p sudah ditulis dengan indentasi (spasi) */

/* Search Balasan */
AddressTreeNode searchBalasanById(BinTree t, int id);
#endif
