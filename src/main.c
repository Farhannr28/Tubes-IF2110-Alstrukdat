#include <boolean.h>
#include <graph.h>
#include <liststatik.h>
#include <matriks.h>
#include <prioqueue.h>
#include <stdio.h>
#include <wordmachine.h>

Word perintah;
boolean isStop = false;
Pengguna currentUser;
ListPengguna listUser;
Graph networkPertemanan;

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

void DoKeluar() {
  if (IsUserValid(currentUser)) {
    printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
    InvalidateUser(&currentUser);
  } else {
    printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan "
           "BurBir.\n");
  }
}

void DoDaftar() {
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
  insertLastListPengguna(&listUser, newUser);
  printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati "
         "fitur-fitur BurBir.\n");
}

void DoMasuk() {
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
      GetUserByName(listUser, &currentUser, nama);
      break;
    } else {
      printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa "
             "kembali kata sandi Anda!\n");
    }
  }
  printf("Anda telah berhasil masuk dengan nama pengguna ");
  PrintWord(currentUser.Nama);
  printf(". Mari "
         "menjelajahi BurBir bersama Ande-Ande Lumut!\n");
}

void DoTutupProgram() {
  isStop = true;
  printf("Anda telah keluar dari program BurBir.\n Sampai jumpa di "
         "penjelajahan berikutnya.\n");
}

void DoGantiProfil() {
  printf("| Nama: ");
  PrintWord(currentUser.Nama);
  printf("\n");
  printf("| Bio Akun: ");
  PrintWord(currentUser.BioAkun);
  printf("\n");
  printf("| No HP: ");
  PrintWord(currentUser.NoHP);
  printf("\n");
  printf("| Weton: ");
  PrintWord(currentUser.Weton);
  printf("\n");
  Word newBioAkun, newNoHP, newWeton;
  PromptUser("Masukkan Bio Akun:", &newBioAkun);
  // TODO: validation
  PromptUser("Masukkan No HP:", &newNoHP);
  // TODO: validation
  PromptUser("Masukkan Weton:", &newWeton);

  ChangeUserInfo(&currentUser, currentUser.isValid, currentUser.Nama,
                 currentUser.KataSandi, newNoHP, newBioAkun, newWeton,
                 currentUser.JenisAkun, currentUser.FotoProfil);

  Pengguna currentUserInDatabase;
  GetUserByName(listUser, &currentUserInDatabase, currentUser.Nama);
  ChangeUserInfo(&currentUserInDatabase, currentUserInDatabase.isValid,
                 currentUserInDatabase.Nama, currentUserInDatabase.KataSandi,
                 newNoHP, newBioAkun, newWeton, currentUserInDatabase.JenisAkun,
                 currentUserInDatabase.FotoProfil);
}

void DoLihatProfil(Word nama) {
  Pengguna theUser;
  GetUserByName(listUser, &theUser, nama);
  if (UserIsPrivate(theUser) || !WordCmpWord(theUser.Nama, currentUser.Nama)) {
    printf("Wah, akun");
    PrintWord(theUser.Nama);
    printf(" diprivat nih. Ikuti dulu yuk untuk bisa melihat profil ");
    PrintWord(theUser.Nama);
    printf("\n");
  } else {
    printf("| Nama: ");
    PrintWord(theUser.Nama);
    printf("\n");
    printf("| Bio Akun: ");
    PrintWord(theUser.BioAkun);
    printf("\n");
    printf("| No HP: ");
    PrintWord(theUser.NoHP);
    printf("\n");
    printf("| Weton: ");
    PrintWord(theUser.Weton);
    printf("\n");
    printf("Foto Profil:\n");
    DisplayProfile(theUser);
    printf("\n");
  }
}

void DoAturJenisAkun() {
  Word choice;

  if (UserIsPrivate(currentUser)) {
    PromptUser("Saat ini, akun Anda adalah akun Privat.\n Ingin "
               "mengubah ke akun "
               "Publik? (YA/TIDAK) ",
               &choice);
  } else {
    PromptUser("Saat ini, akun Anda adalah akun Publik.\n Ingin "
               "mengubah ke akun "
               "Privat? (YA/TIDAK) ",
               &choice);
  }

  /* while (!WordCmp(choice, "YA") || !WordCmp(choice, "TIDAK")) { */
  /*   printf("Jawaban tidak valid\n"); */
  /*   PromptUser( */
  /*       "Saat ini, akun Anda adalah akun Publik.\nIngin mengubah ke akun " */
  /*       "Privat? (YA/TIDAK) ", */
  /*       &choice); */
  /* } */

  if (WordCmp(choice, "YA")) {
    ChangePrivacy(&currentUser, true);
    printf("Akun anda sudah diubah menjadi akun Privat.\n");
  } else {
    ChangePrivacy(&currentUser, false);
    printf("Akun anda sudah diubah menjadi akun Publik.\n");
  }
}

void DoUbahFotoProfil() {
  printf("Foto profil Anda saat ini adalah\n");
  DisplayProfile(currentUser);
  printf("\n");
  printf("Masukkan foto profil yang baru\n");
  Word inputProfile;
  GetWordButTrim(&inputProfile, ' ');
  Matriks m;
  MatriksFromWord(&m, inputProfile);
  Pengguna currentUserInDatabase;
  GetUserByName(listUser, &currentUserInDatabase, currentUser.Nama);
  UpdateProfil(&currentUser, m);
  UpdateProfil(&currentUserInDatabase, m);
  printf("\n");
  printf("Foto profil anda sudah berhasil diganti!\n");
}

void DoTambahTeman() {
  Word namaPengguna;
  PromptUser("Masukkan nama pengguna:\n", &namaPengguna);
  Pengguna *friend;
  boolean userAvailable =
      GetMutableUserByName(&listUser, &friend, namaPengguna);
  if (userAvailable) {
    boolean success = TambahTeman(currentUser, friend);
    if (success) {
      printf("Permintaan pertemanan kepada ");
      PrintWord(namaPengguna);
      printf(" telah dikirim. Tunggu beberapa saat hingga permintaan Anda "
             "disetujui.\n");
    } else {
      printf(
          "Terdapat permintaan pertemanan yang belum Anda setujui. Silakan "
          "kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.");
    }
  } else {
    printf("Pengguna bernama ");
    PrintWord(namaPengguna);
    printf(" tidak ditemukan");
  }
}

void DoDaftarPermintaanPertemanan() {
  int banyakTeman = length_queue(currentUser.PermintaanBerteman);
  if (banyakTeman) {
    printf("Terdapat %d permintaan pertemanan untuk Anda.\n\n", banyakTeman);
    PrintListTeman(currentUser);
  } else {
    printf("Tidak ada permintaan pertemanan untuk Anda.\n");
  }
}

void DoSetujuiPertemanan() {
  int banyakTeman = length_queue(currentUser.PermintaanBerteman);
  if (banyakTeman) {
    Address penggunaTeratas = GetPermintaanTeratas(currentUser);
    Word namaPengguna = DATA(penggunaTeratas);
    int jumlahTemanPengguna = PRIORITY(penggunaTeratas);
    printf("| ");
    PrintWord(namaPengguna);
    printf("\n");
    printf("| Jumlah teman: %d\n\n", jumlahTemanPengguna);

    Word response;
    PromptUser(
        "Apakah Anda ingin menyetujui permintaan pertemanan ini? (YA/TIDAK) ",
        &response);
    if (WordCmp(response, "YA")) {
      // TODO: add accepts

      printf("Permintaan pertemanan dari ");
      PrintWord(namaPengguna);
      printf(" telah disetujui. Selamat! Anda telah berteman dengan ");
      PrintWord(namaPengguna);
      printf(".\n\n");
    } else {
      printf("Permintaan pertemanan dari ");
      PrintWord(namaPengguna);
      printf(" telah ditolak.\n\n");
    }

  } else {
    printf("Tidak ada permintaan pertemanan untuk Anda.\n");
  }
}

void DoPerintah() {
  Word action, args1;
  ParseWord(&perintah, ' ', &action, &args1);
  if (WordCmp(action, "KELUAR")) {
    DoKeluar();
  } else if (WordCmp(action, "DAFTAR")) {
    DoDaftar();
  } else if (WordCmp(action, "MASUK")) {
    DoMasuk();
  } else if (WordCmp(action, "TUTUP_PROGRAM")) {
    DoTutupProgram();
  } else if (WordCmp(action, "GANTI_PROFIL")) {
    DoGantiProfil();
  } else if (WordCmp(action, "LIHAT_PROFIL")) {
    DoLihatProfil(args1);
  } else if (WordCmp(action, "ATUR_JENIS_AKUN")) {
    DoAturJenisAkun();
  } else if (WordCmp(action, "UBAH_FOTO_PROFIL")) {
    DoUbahFotoProfil();
  } else if (WordCmp(action, "TAMBAH_TEMAN")) {
    DoTambahTeman();
  } else if (WordCmp(action, "DAFTAR_PERMINTAAN_PERTEMANAN")) {
    DoDaftarPermintaanPertemanan();
  } else if (WordCmp(action, "SETUJUI_PERTEMANAN")) {
    DoSetujuiPertemanan();
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
