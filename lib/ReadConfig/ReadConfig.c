#include "../ListLinier/listlinier.h"
#include "../Utasan/Utasan.h"
#include "stdio.h"
#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "string.h"


boolean MuatUtas(char *namafolder,ListLinearUtas *l1){
    FILE *fUtas;
    boolean sukses = true;
    Utasan Utas;
    int IDUtas = 0;
    char configfile[100];
    Word InputText;
    Word Penulis;
    snprintf(configfile, sizeof(configfile), "../../config/utas.config");
    printf("%s\n",configfile);
    fUtas = fopen(configfile,"r");
    if (fUtas == NULL) {
        printf("Tidak ada file konfigurasi utas.\n");
        sukses = false;
    } else {
        printf("File utas ditemukan\n");
        char line[280];
        int jumlahutas, m, i, j;
        int id;
        // DATETIME date;

        fscanf(fUtas,"%d",&jumlahutas);
        fgets(line,280,fUtas);
        for (i=0;i<jumlahutas;i++){
            IDUtas+=1;
            fscanf(fUtas,"%d",&id);
            fgets(line,50,fUtas);
            fscanf(fUtas,"%d",&m);
            fgets(line,280,fUtas);
            for (j=0;j<m;j++){
                char text[500];
                fgets(text, sizeof(text), fUtas);
                printf("===================\n");
                AssignWord(&InputText,text);
                fgets(line,280,fUtas);
                AssignWord(&Penulis,line);
                if(j==0){
                    CreateUtas(&Utas,IDUtas,id,InputText,Penulis);
                }
                else{
                    insertLastParagraph(&Utas,InputText);
                    printf("Ini adalah:\n");
                    PrintWord(InputText);
                    printf("=============");
                }

                // int h,m,s,d,b,y;
                // fscanf(fUtas, "%d/%d/%d %d:%d:%d", &d, &b, &y, &h, &m, &s);
                // fgets(line,280,fUtas);
                // CreateDATETIME(&date,d,b,y,h,m,s);
                // p.waktu = date;
                // insertLastKicau(&(utas.Utas),p);
            }
        insertFirstListLinearUtas(l1,Utas);
        }
    }
    fclose(fUtas);
    return sukses;
}

//Contoh
int main(){
    ListLinearUtas listUtas;
    CreateListLinearUtas(&listUtas);
    // MuatUtas("config",&listUtas);
    Word W1;
    Word W2;
    AssignWord(&W1,"Asep");
    AssignWord(&W2,"Asep2");
    PrintWord(W2);
    // PrintWord(W1);
    // Cetak_Utas(listUtas,1);
}