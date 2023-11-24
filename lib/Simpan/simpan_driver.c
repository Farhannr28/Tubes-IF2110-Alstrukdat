#include "../ReadConfig/ReadConfig.h"
#include "../UndirectedGraph/graph.h"
#include "../ListStatik/liststatik.h"
#include "Simpan.h"

int main() {
    ListStatik listUser;
    Graph networkPertemanan;
    MuatPengguna("config/pengguna.config", &listUser, &networkPertemanan);
    simpanPengguna("config", listUser, networkPertemanan);
    return 0;
}
