#include "../MesinKata/wordmachine.h"
#include "config.h"
#include <stdio.h>

int main() {
  Word w;
  AssignWord(&w, "test.txt");
  printf("noice\n");
  loadConfig(w);
}
