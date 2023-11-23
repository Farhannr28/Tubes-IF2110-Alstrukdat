#ifndef TAGAR
#define TAGAR

#include "../ListDinamis/listdin.h"
#include "../MesinKata/wordmachine.h"

typedef struct KicauanNode *AddressKicauanNode;

typedef struct KicauanNode {
  int kicauanId;
  AddressKicauanNode next;
} KicauanNode;

typedef struct Tagar *AddressTagar;

typedef struct Tagar {
  Word isiTagar;
  AddressKicauanNode data;
  // Collision handler dengan chaining
  AddressTagar next;
} Tagar;

#endif
