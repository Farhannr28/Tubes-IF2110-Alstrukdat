#include <boolean.h>
#include <liststatik.h>
#include <stdio.h>
#include <wordmachine.h>

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
  InvalidateUser(&currentUser);
  printf("File konfigurasi berhasil dimuat! Selamat berkicau!\n");
}

void GetPerintah() {
  printf(">> ");
  GetWord(&perintah);
}

void PromptUser(const char *c, Word *w) {
  printf("%s", c);
  GetWord(w);
}

void DoPerintah() {
  if (WordCmp(perintah, "KELUAR")) {
    if (IsUserValid(currentUser)) {
      printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
      InvalidateUser(&currentUser);
    } else {
      printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    }
  } else if (WordCmp(perintah, "DAFTAR")) {
    Word nama, password;
    while (true) {
      PromptUser("Masukkan nama:\n", &nama);
      if (UsernameTaken(listUser, nama)) {
        printf("Wah, sayang sekali nama tersebut telah diambil.\n");
      } else {
        break;
      }
    }
    PromptUser("Masukkan kata sandi:\n", &password);
    Pengguna newUser;
    CreatePengguna(&newUser, nama, password);
    insertFirstListPengguna(&listUser, newUser);
    printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati "
           "fitur-fitur BurBir.\n");
  } else if (WordCmp(perintah, "MASUK")) {
    Word nama, password;
    while (true) {
      PromptUser("Masukkan nama:\n", &nama);
      if (UsernameTaken(listUser, nama)) {
        break;
      } else {
        printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!\n");
      }
    }
    while (true) {
      PromptUser("Masukkan kata sandi:\n", &password);
      if (UserAndPasswordMatch(listUser, nama, password)) {
        CreatePengguna(&currentUser, nama, password);
        break;
      } else {
        printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa "
               "kembali kata sandi Anda!\n");
      }
    }
    printf("Anda telah berhasil masuk dengan nama pengguna Tuan Bri. Mari "
           "menjelajahi BurBir bersama Ande-Ande Lumut!\n");
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
