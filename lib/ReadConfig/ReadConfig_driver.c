#include "ReadConfig.c"

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
