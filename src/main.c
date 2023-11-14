#include <boolean.h>
#include <stdio.h>
#include <wordmachine.h>

void greetings() {
  Word configFile;
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
         "Silahkan masukan folder konfigurasi untuk dimuat: ");
  GetWord(&configFile);
  // TODO: load config
  printf("File konfigurasi berhasil dimuat! Selamat berkicau!\n");
}

Word perintah;
boolean isStop = false;
boolean currentUser = false;

void getPerintah() {
  printf(">> ");
  GetWord(&perintah);
}

void DoPerintah() {
  if (WordCmp(perintah, "KELUAR")) {
  } else if (WordCmp(perintah, "DAFTAR")) {

  } else if (WordCmp(perintah, "MASUK")) {

  } else if (WordCmp(perintah, "TUTUP_PROGRAM")) {
    isStop = true;
    printf("Anda telah keluar dari program BurBir.\n Sampai jumpa di "
           "penjelajahan berikutnya.\n");
  } else {
    printf("Perintah tidak valid!\n");
  }
}

int main() {
  greetings();
  while (!isStop) {
    getPerintah();
    DoPerintah();
  }
  return 0;
}
