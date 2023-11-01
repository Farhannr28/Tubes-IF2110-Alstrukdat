#include <stdio.h>
#include <user.h>
#include <wordmachine.h>

void greetings() {
  printf(".______    __    __  .______      .______    __  .______      \n"
         "|   _  \\  |  |  |  | |   _  \\     |   _  \\  |  | |   _  \\     \n"
         "|  |_)  | |  |  |  | |  |_)  |    |  |_)  | |  | |  |_)  |    \n"
         "|   _  <  |  |  |  | |      /     |   _  <  |  | |      /     \n"
         "|  |_)  | |  `--'  | |  |\\  \\----.|  |_)  | |  | |  |\\  \\----.\n"
         "|______/   \\______/  | _| `._____||______/  |__| | _| `._____|  \n"
         "Selamat datang di BurBir. \n"
         "Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan "
         "menggunakan metode (pengambilan data berupa) Focused Group "
         "Discussion kedua di zamannya.\n"
         "Silahkan masukan folder konfigurasi untuk dimuat: config-1;\n"
         "File konfigurasi berhasil dimuat! Selamat berkicau!\n");
  printf(">> ");
  START();
  STARTWORD();
}

void parseCommand(Word command) {
  if (WordCmp(command, "DAFTAR")) {
    RegisterUser();
  } else if (WordCmp(command, "MASUK")) {

  } else if (WordCmp(command, "MUAT")) {

  } else if (WordCmp(command, "DAFTAR")) {
  }
}

int main() {
  greetings();
  do {
    parseCommand(currentWord);
  } while (true);

  return 0;
}
