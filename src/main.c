#include <boolean.h>
#include <stdio.h>
#include <wordmachine.h>
#include <liststatik.h>

Word perintah;
boolean isStop = false;
Pengguna currentUser;
ListPengguna listUser;

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
  // WARN: this should be ifNotLoaded
  CreateListPengguna(&listUser);
  printf("File konfigurasi berhasil dimuat! Selamat berkicau!\n");
}


void GetPerintah() {
  printf(">> ");
  GetWord(&perintah);
}

void PromptUser(const char* c,Word *w) {
  printf("%s", c);
  GetWord(w);
}

void DoPerintah() {
  if (WordCmp(perintah, "KELUAR")) {
  } else if (WordCmp(perintah, "DAFTAR")) {
    Word nama, password;
    PromptUser("Masukkan nama:\n", &nama);
    PromptUser("Masukkan kata sandi:\n", &password);
    // TODO: validate user and password
    printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
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
    GetPerintah();
    DoPerintah();
  }
  return 0;
}
