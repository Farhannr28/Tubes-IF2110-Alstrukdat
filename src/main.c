#include <boolean.h>
#include <graph.h>
#include <kicauan.h>
#include <liststatik.h>
#include <listdin.h>
#include <matriks.h>
#include <prioqueue.h>
#include <stdio.h>
#include <wordmachine.h>
#include <datetime.h>
#include <stack.h>
#include <Utasan.h>
#include <listlinier.h>
#include <Simpan.h>
#include <kicauan_methods.h>
#include <pengguna_methods.h>

Word perintah;
boolean isStop = false;
Pengguna currentUser;
ListStatik listUser;
Graph networkPertemanan;
ListDin listKicauan;
ListLinearUtas ListUtas;

void greetings() {
  Word configFile;
  printf(".______    __    __  .______      .______    __  .______      \n"
         "|   _  \\  |  |  |  | |   _  \\     |   _  \\  |  | |   _  \\     \n"
         "|  |_)  | |  |  |  | |  |_)  |    |  |_)  | |  | |  |_)  |    \n"
         "|   _  <  |  |  |  | |      /     |   _  <  |  | |      /     \n"
         "|  |_)  | |  `--'  | |  |\\  \\----.|  |_)  | |  | |  |\\  \\----.\n"
         "|______/   \\______/  | _| `._____||______/  |__| | _| `._____|  \n"
         "Selamat datang di BurBir. \n\n"
         "Aplikasi untuk studi kualitatif mengenai perilaku manusia dengan "
         "menggunakan metode (pengambilan data berupa) Focused Group "
         "Discussion kedua di zamannya.\n\n"
         "Silahkan masukan folder konfigurasi untuk dimuat: ");
  GetWord(&configFile);
  printf("\n");
  // TODO: load config
  // WARN: this should be ifNotLoaded
  CreateListStatik(&listUser, PENGGUNA);
  CreateListDinamik(&listKicauan, 10, KICAUAN);
  InvalidateUser(&currentUser);
  // WARN: max user asumsi 20
  createGraph(&networkPertemanan, 20);
  printf("File konfigurasi berhasil dimuat! Selamat berkicau!\n\n");
}

void GetPerintah() {
  printf(">> ");
  GetWord(&perintah);
  printf("\n");
}

void PromptUser(const char *c, Word *w) {
  printf("%s", c);
  GetWord(w);
  printf("\n");
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
  if(IsUserValid(currentUser)) {
    printf("Anda sudah masuk. Keluar terlebih dahulu untuk melakukan daftar.\n\n");
    return;
  }
  Word nama, password;
  while (true) {
    PromptUser("Masukkan nama:\n", &nama);
    if (UsernameTaken(listUser, nama)) {
      printf("Wah, sayang sekali nama tersebut telah diambil.\n\n");
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
  if(IsUserValid(currentUser)) {
    printf("Wah Anda sudah masuk. Keluar dulu yuk!\n\n");
    return;
  }
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
  printf("\n\n");
  Word newBioAkun, newNoHP, newWeton;
  PromptUser("Masukkan Bio Akun:", &newBioAkun);
  while(true) {
    PromptUser("Masukkan No HP:", &newNoHP);
    boolean noHpValid = validateNoHP(newNoHP);
    if(noHpValid) break;
    else printf("No HP tidak valid. Masukkan lagi yuk!\n\n");
  }
  while(true) {
    PromptUser("Masukkan Weton:", &newWeton);
    boolean wetonValid = validateWeton(newWeton);
    if(wetonValid) break;
    else printf("Weton anda tidak valid.\n\n");
  }

  ChangeUserInfo(&currentUser, currentUser.isValid, currentUser.Nama,
                 currentUser.KataSandi, newNoHP, newBioAkun, newWeton,
                 currentUser.JenisAkun, currentUser.FotoProfil);

  Pengguna currentUserInDatabase;
  // TODO: not changed in list
  GetUserByName(listUser, &currentUserInDatabase, currentUser.Nama);
  ChangeUserInfo(&currentUserInDatabase, currentUserInDatabase.isValid,
                 currentUserInDatabase.Nama, currentUserInDatabase.KataSandi,
                 newNoHP, newBioAkun, newWeton, currentUserInDatabase.JenisAkun,
                 currentUserInDatabase.FotoProfil);
  printf("Profil Anda sudah berhasil diperbarui!");
}

void DoLihatProfil(Word nama) {
  Pengguna theUser;
  GetUserByName(listUser, &theUser, nama);
  if (UserIsPrivate(theUser) || !WordCmpWord(theUser.Nama, currentUser.Nama)) {
    printf("Wah, akun");
    PrintWord(theUser.Nama);
    printf(" diprivat nih. Ikuti dulu yuk untuk bisa melihat profil ");
    PrintWord(theUser.Nama);
    printf("\n\n");
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
    printf("\n\n");
    printf("Foto Profil:\n");
    DisplayProfile(theUser);
    printf("\n\n");
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
  printf("\n");

  if (WordCmp(choice, "YA")) {
    ChangePrivacy(&currentUser, true);
    printf("Akun anda sudah diubah menjadi akun Privat.\n");
  } else {
    ChangePrivacy(&currentUser, false);
    printf("Akun anda sudah diubah menjadi akun Publik.\n");
  }
  printf("\n");
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
  printf("\n");
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
      printf("\n");
    }
  } else {
    printf("Pengguna bernama ");
    PrintWord(namaPengguna);
    printf(" tidak ditemukan");
    printf("\n");
  }
  printf("\n");
}

void DoDaftarPermintaanPertemanan() {
  int banyakTeman = length_queue(currentUser.PermintaanBerteman);
  if (banyakTeman) {
    printf("Terdapat %d permintaan pertemanan untuk Anda.\n\n", banyakTeman);
    PrintListTeman(currentUser);
  } else {
    printf("Tidak ada permintaan pertemanan untuk Anda.\n");
  }
  printf("\n");
}

void DoSetujuiPertemanan() {
  int banyakTeman = length_queue(currentUser.PermintaanBerteman);
  if (banyakTeman) {
    Address addressPenggunaTeratas = GetPermintaanTeratas(currentUser);
    Word namaPengguna = DATA(addressPenggunaTeratas);
    int jumlahTemanPengguna = PRIORITY(addressPenggunaTeratas);

    printf("| ");
    PrintWord(namaPengguna);
    printf("\n");
    printf("| Jumlah teman: %d\n\n", jumlahTemanPengguna);

    Word response;
    PromptUser(
        "Apakah Anda ingin menyetujui permintaan pertemanan ini? (YA/TIDAK) ",
        &response);
    if (WordCmp(response, "YA")) {
      Pengguna penggunaTeratas;
      GetUserByName(listUser, &penggunaTeratas, namaPengguna);
      addTeman(&networkPertemanan, currentUser.id, penggunaTeratas.id);
      printf("Permintaan pertemanan dari ");
      PrintWord(namaPengguna);
      printf(" telah disetujui. Selamat! Anda telah berteman dengan ");
      PrintWord(namaPengguna);
      printf(".\n\n");
    } else {
      dequeue(&currentUser.PermintaanBerteman);
      printf("Permintaan pertemanan dari ");
      PrintWord(namaPengguna);
      printf(" telah ditolak.\n\n");
    }

  } else {
    printf("Tidak ada permintaan pertemanan untuk Anda.\n");
    printf("\n");
  }
}

void DoDaftarTeman() { 
  if(IsUserValid(currentUser))
    printTeman(listUser, networkPertemanan, currentUser); 
  else
    printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
  printf("\n");
}

void DoHapusTeman() {
  Word namaPengguna;
  PromptUser("Masukkan nama pengguna:\n", &namaPengguna);
  printf("\n");
  Pengguna teman;
  GetUserByName(listUser, &teman, namaPengguna);
  if (!isTeman(networkPertemanan, currentUser.id, teman.id)) {
    PrintWord(teman.Nama);
    printf(" bukan teman Anda.\n");
    printf("\n");
    return;
  }
  Word response;
  PromptUser("Apakah anda yakin ingin menghapus Bob dari daftar teman "
             "anda?(YA/TIDAK) ",
             &response);
  printf("\n");
  if (WordCmp(response, "YA")) {
    hapusTeman(&networkPertemanan, currentUser.id, teman.id);
    PrintWord(namaPengguna);
    printf(" berhasil dihapus dari daftar teman Anda.\n");
  } else {
    printf("Penghapusan teman dibatalkan.\n");
  }
  printf("\n");
}

void DoKicau() {
  Word text;
  PromptUser("Masukkan kicauan:\n", &text);
  Kicauan kicauan;
  createKicauan(&kicauan, currentUser.id, text);
  insertKicauanLast(&listKicauan, kicauan);
  printf("Selamat! kicauan telah diterbitkan!\n");
  printf("Detil kicauan:\n");
  showKicauan(kicauan, currentUser.Nama);
}

void DoKicauan() {
  for (int i=0; i<listKicauan.nEff; i++){
    int idPengkicau = ELMTDinamik(listKicauan, i).k.idPembuat;
    boolean dariTeman = isTeman(networkPertemanan, currentUser.id, idPengkicau);
    boolean dariSendiri = currentUser.id == idPengkicau;
    if(dariSendiri || dariTeman) {
            Pengguna Author;
            if(dariSendiri) {
              Author = currentUser;
            } else {
              GetUserById(listUser, &Author, idPengkicau);
            } 
            showKicauan(ELMTDinamik(listKicauan, i).k, Author.Nama);
    } 
  }
}

void DoSukaKicauan(Word idKicauWord) {
  int idKicau = IntFromWord(idKicauWord);
  Kicauan kicauan;
  boolean found = getKicauanById(listKicauan, &kicauan, idKicau);
  if(!found) {
    printf("Tidak ditemukan kicauan dengan ID = %d;\n", idKicau);
    return;
  } 
  Pengguna pengkicau;
  GetUserById(listUser, &pengkicau, kicauan.idPembuat);
  boolean dariTeman = isTeman(networkPertemanan, currentUser.id, kicauan.idPembuat);
  boolean dariSendiri = (currentUser.id == kicauan.idPembuat);
  if(!UserIsPrivate(pengkicau) || dariTeman || dariSendiri) {
    sukaKicauan(&listKicauan, kicauan.id);
    getKicauanById(listKicauan, &kicauan, idKicau);
    printf("Selamat! kicauan telah disukai!\n");
    printf("Detil kicauan:\n");
    showKicauan(kicauan, pengkicau.Nama);
  } else {
    printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n");
  }
}

void DoUbahKicauan(Word idKicauWord) {
  int idKicau = IntFromWord(idKicauWord);
  Kicauan kicauan;
  boolean found = getKicauanById(listKicauan, &kicauan, idKicau);
  if(!found) {
    printf("Tidak ditemukan kicauan dengan ID = %d;\n", idKicau);
    return;
  } 
  boolean dariSendiri = (currentUser.id == kicauan.idPembuat);
  if(dariSendiri) {
    Word textKicauanBaru;
    PromptUser("Masukkan kicauan baru:\n", &textKicauanBaru);
    ubahKicauan(&listKicauan, kicauan.id, textKicauanBaru);
    getKicauanById(listKicauan, &kicauan, idKicau);
    printf("Selamat! kicauan telah diterbitkan!\n");
    printf("Detil kicauan:\n");
    showKicauan(kicauan, currentUser.Nama);
  } else {
    printf("Kicauan dengan ID = %d bukan milikmu!\n", idKicau);
  }
}

void DoBuatDraf () {
  Word textDrafKicauan;
  PromptUser("Masukkan draf:\n", &textDrafKicauan);
  Word command;
  PromptUser("Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n", &command);
  if (WordCmp(command, "HAPUS")) {
    printf("Draf telah berhasil dihapus!\n");
  } else if (WordCmp(command, "SIMPAN")) {
    DrafKicau drafkicauan;
    CreateDrafKicau(&drafkicauan, textDrafKicauan);
    Push(&currentUser.Draf, drafkicauan);
  } else if (WordCmp(command, "TERBIT")) {
    Kicauan kicauan;
    createKicauan(&kicauan, currentUser.id, textDrafKicauan);
    insertKicauanLast(&listKicauan, kicauan);
    printf("Selamat! Draf kicauan telah diterbitkan!\n");
    printf("Detil kicauan:\n");
    printf("| ID = %d\n", kicauan.id);
    printf("| ");PrintWord(currentUser.Nama);printf("\n");
    printf("| ");TulisDateTime(kicauan.waktu);printf("\n");
    printf("| ");PrintWord(kicauan.text);printf("\n");
    printf("| Disukai: %d\n", kicauan.like);
    printf("\n");
  }
}

void DoLihatDraf() {
  if (IsEmptyStack(currentUser.Draf)) {
    printf("Yah, anda belum memiliki draf apapun! Buat dulu ya :D\n");
  } else {
    DrafKicau drafkicauan;
    Pop(&currentUser.Draf, &drafkicauan);
    printf("Ini draf terakhir Anda:\n");
    DisplayDrafKicau(drafkicauan);
    Word command;
    PromptUser("Apakah anda ingin mengubah, menghapus, atau menerbitkan draf ini? (KEMBALI jika ingin kembali)\n", &command);
    if (WordCmp(command, "HAPUS")) {
      printf("Draf telah berhasil dihapus!\n");
    } else if (WordCmp(command, "UBAH")) {
      DoBuatDraf();
    } else if (WordCmp(command, "TERBIT")) {
      Kicauan kicauan;
      createKicauan(&kicauan, currentUser.id, drafkicauan.text);
      insertKicauanLast(&listKicauan, kicauan);
      printf("Selamat! Draf kicauan telah diterbitkan!\n");
      printf("Detil kicauan:\n");
      printf("| ID = %d\n", kicauan.id);
      printf("| ");PrintWord(currentUser.Nama);printf("\n");
      printf("| ");TulisDateTime(kicauan.waktu);printf("\n");
      printf("| ");PrintWord(kicauan.text);printf("\n");
      printf("| Disukai: %d\n", kicauan.like);
      printf("\n");
    } else if (WordCmp(command, "KEMBALI")) {
      Push(&currentUser.Draf, drafkicauan);
    }
  }
}

void DoUtas(Word idKicauWord){
  int idKicau = IntFromWord(idKicauWord);
  Kicauan K;
  if(!getKicauanById(listKicauan,&K,idKicau)){
    printf("Kicauan tidak ditemukan\n");
  }
  else{
    if(currentUser.id != K.idPembuat){
      // printf("IDnya %d dan %d\n",currentUser.id,K.id);
      printf("Utas ini bukan milik anda!\n");
    }
    else{
      Utas(idKicau,&ListUtas,currentUser.Nama);
    }
  }
}

void DoSambungUtas(Word IDUtasWord, Word indexWord){
  int IDUtas = IntFromWord(IDUtasWord);
  int index = IntFromWord(indexWord);
  Word Penulis;
  Pengguna InfoPenulis;
  int pos = indexOfListLinearUtas(ListUtas,IDUtas,&Penulis);
  boolean found = GetUserByName(listUser,&InfoPenulis,Penulis);
  if(pos == IDX_UNDEF){
    printf("Utas tidak ditemukan!");
  }
  else{
  if(InfoPenulis.id != currentUser.id){
    printf("Anda tidak bisa menyambung utas ini!");
  }
  else{
    Sambung_Utas(IDUtas,index,&ListUtas);
  }
  }
}

void DoCetakUtas(Word IDUtasWord){
  int IDUtas = IntFromWord(IDUtasWord);
  Pengguna user;
  Kicauan K;
  // printf("===========\n");
  if(indexOfListLinearUtas(ListUtas,IDUtas,&user) == IDX_UNDEF){
    printf("Utas tidak ditemukan!");
  }
  else{
      boolean dariTeman = isTeman(networkPertemanan, currentUser.id, user.id);
      boolean dariSendiri = (currentUser.id == user.id);
      if(!UserIsPrivate(user) || dariTeman || dariSendiri){
        Cetak_Utas(ListUtas,IDUtas,listKicauan,listUser);
      }
    else{
        printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!");
    }
  }
}

void DoHapusUtas(Word IDUtasWord, Word indexWord){
  int IDUtas = IntFromWord(IDUtasWord);
  int index = IntFromWord(indexWord);
  Word Penulis;
  Pengguna InfoPenulis;
  int pos = indexOfListLinearUtas(ListUtas,IDUtas,&Penulis);
  boolean found = GetUserByName(listUser,&InfoPenulis,Penulis);
  if(pos == IDX_UNDEF){
    printf("Utas tidak ditemukan!");
  }
  else{
  if(InfoPenulis.id != currentUser.id){
    printf("Anda tidak bisa menghapus kicauan dalam utas ini!");
  }
  else{
    Hapus_Utas(IDUtas,index,&ListUtas);
  }
  }
}
void DoPerintah() {
  Word action, args1,args2;
  ParseWord(&perintah, ' ', &action, &args1,&args2);
  // PrintWord(action);
  // PrintWord(args1);
  // PrintWord(args2);
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
  } else if (WordCmp(action, "DAFTAR_TEMAN")) {
    DoDaftarTeman();
  } else if (WordCmp(action, "HAPUS_TEMAN")) {
    DoHapusTeman();
  } else if (WordCmp(action, "KICAU")) {
    DoKicau();
  } else if (WordCmp(action, "KICAUAN")) {
    DoKicauan();
  } else if (WordCmp(action, "SUKA_KICAUAN")) {
    DoSukaKicauan(args1);
  } else if (WordCmp(action, "UBAH_KICAUAN")) {
    DoUbahKicauan(args1);
  } else if (WordCmp(action, "BUAT_DRAF")) {
    DoBuatDraf();
  } else if (WordCmp(action, "LIHAT_DRAF")) {
    DoLihatDraf();
  }
  else if (WordCmp(action,"UTAS")){
    DoUtas(args1);
  }
  else if(WordCmp(action,"SAMBUNG_UTAS")){
    DoSambungUtas(args1,args2);
  } 
  else if (WordCmp(action,"CETAK_UTAS")){
    DoCetakUtas(args1);
  }
  else if (WordCmp(action,"SIMPAN")){
    SIMPANUTAS(ListUtas,"testing");
  }
  else if (WordCmp(action,"HAPUS_UTAS")){
    DoHapusUtas(args1,args2);
  }
  else {
    printf("Perintah tidak valid!\n");
  }
  printf("\n");
}

int main() {
  greetings();
  while (!isStop) {
    GetPerintah();
    DoPerintah();
  }
  return 0;
}
