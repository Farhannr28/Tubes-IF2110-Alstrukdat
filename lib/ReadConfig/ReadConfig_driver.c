#include "ReadConfig.h"
#include "../ListLinier/listlinier.h"
#include "../Utasan/Utasan.h"
#include "stdio.h"
#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
// #include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../ListStatik/liststatik.h"
#include "../UndirectedGraph/graph.h"
#include "string.h"
//Contoh
int main(){
    ListStatik listUser;
    Graph networkPertemanan;
    MuatPengguna("config/pengguna.config", &listUser, &networkPertemanan);
}
