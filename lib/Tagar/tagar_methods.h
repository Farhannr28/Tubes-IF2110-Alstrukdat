#include "../ListStatik/liststatik.h"
#include "../MesinKata/wordmachine.h"
#include "tagar.h"
#include <stdlib.h>

#define DataTagar(t) (t)->data
#define IsiTagar(t) (t)->isiTagar
#define NextTagar(t) (t)->next
#define InfoKicauan(k) (k)->kicauanId
#define NextKicauan(k) (k)->next

int hashFunction(Word tagar);

AddressKicauanNode newKicauanNode(int kicauanId);

AddressTagar newTagar(AddressKicauanNode k, Word isiTagar);

void addKicauanPadaTagar(ListStatik *listTagar, int kicauanId, Word isiTagar);

void showKicauanDenganTagar(ListStatik listTagar, ListStatik listUser,
                            ListDin kicauan, Word isiTagar);
