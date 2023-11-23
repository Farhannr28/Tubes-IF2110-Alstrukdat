#include "../Matriks/matriks.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../PriorityQueue/prioqueue.h"
#include "../utility/boolean.h"
#include "../UndirectedGraph/graph.h"
#include "../Stack/stack.h"
#include "../Pengguna/pengguna.h"
#include <stdio.h>
#include "Utasan.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
int main(){
    //Set up kondisi
    ListLinearUtas ListUtas;
    int type;
    DATETIME D = GetCurrentDateTime();
    Word UtasanBaru;
    Utasan U;
    Word UtasanInput;
    Word Penulis;
    Word PenulisOutput;
    ListStatik User;
    ListDin ListKicau;
    Kicauan kicauan;
    Word Utama;
    Word Text2;
    CreateListLinearUtas(&ListUtas);
    printf("Initialized test cases :\n");
    printf("Masukkan Utasan untuk driver test:\n");
    GetWord(&UtasanInput);
    printf("Masukkan PENULIS untuk driver test:\n");
    GetWord(&Penulis);
    CreateUtas(&U,23,23,UtasanInput,Penulis,D);
    insertLastListLinearUtas(&ListUtas,U);
    AddressUtas p = ListUtas;
    int IndexUtas;
    int indexmax;
    Paragraph* paragraph = p->info.TextList;
    printf("Kondisi yang ingin di tes\n");
    scanf("%d",&type);
    switch (type)
    {
        case 1:
        printf("Drive test untuk insertLastParagraph\n");
        printf("Masukkan kicauan sambungan:\n");
        GetWord(&Text2);
        insertLastParagraph(&U,Text2,D);
        int index = 1;
        printf("IDKICAU = %d ",U.IDKicauan);
        printf("IDUTAS = %d  ",U.IDUtasan);
        printf("\n");
        printf("Penulis yaitu:\n");
        PrintWord(Penulis);
        printf("\n");
        while(p!=NULL){
            while( paragraph !=NULL){
                printf("Ini untuk index %d\n",index);
                printf("Pada jam:\n");
                TulisDateTime(CurrTime(paragraph));
                printf("\n");
                printf("Dituliskan:");
                PrintWord(KONTEN(paragraph));
                printf("\n");
                printf("\n");
                paragraph =  paragraph-> next;
                index ++;
            }
            p = NEXT(p);
        }
        break;

        case 2:
        printf("Drive test untuk CreateUtas\n");
        index = 1;
        printf("IDKICAU = %d ",U.IDKicauan);
        printf("IDUTAS = %d  ",U.IDUtasan);
        printf("\n");
        printf("Penulis yaitu:\n");
        PrintWord(Penulis);
        printf("\n");
        while(p!=NULL){
            while( paragraph !=NULL){
                printf("Pada jam:\n");
                TulisDateTime(CurrTime(paragraph));
                printf("\n");
                printf("Dituliskan:");
                PrintWord(KONTEN(paragraph));
                printf("\n");
                printf("\n");
                paragraph =  paragraph-> next;
                index ++;
            }
            p = NEXT(p);
        }
        break;
        case 3:
            printf("Drive test untuk deleteParagraphAtPosition\n");
            printf("Masukkan kicauan sambungan:\n");
            GetWord(&Text2);
            insertLastParagraph(&U,Text2,D);
            index = 1;
            printf("Masukkan input index yang ingin dihapus, pastikkan valid:\n");
            // scanf("%d",&IndexUtas);
            deleteParagraphAtPosition(&ListUtas,23,1);
            paragraph = p->info.TextList;
            while(p!=NULL){
                while( paragraph !=NULL){
                    printf("Ini untuk index %d\n",index);
                    printf("Pada jam:\n");
                    TulisDateTime(CurrTime(paragraph));
                    printf("\n");
                    printf("Dituliskan:");
                    PrintWord(KONTEN(paragraph));
                    printf("\n");
                    printf("\n");
                    paragraph =  paragraph-> next;
                    index ++;
                }
            p = NEXT(p);
            break;
        }
        case 4:
            printf("Driver test untuk GetUtasanIndex\n");
            indexmax = GetUtasanIndex(ListUtas,23);
            printf("Index max Awal:%d\n",indexmax);
            printf("Tambah sambungan text:\n");
            GetWord(&Text2);
            insertLastParagraph(&U,Text2,D);
            indexmax = GetUtasanIndex(ListUtas,23);
            printf("Index max Akhir:%d\n",indexmax);
        case 5:
            printf("Driver test untuk indexOfListLinearUtas\n");
            indexmax = indexOfListLinearUtas(ListUtas,23,&PenulisOutput);
            printf("Index dalam List (IDX_UNDEF jika tidak ada):%d",indexmax);
}
}