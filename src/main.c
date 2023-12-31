#include <DSU.h>
#include <Simpan.h>
#include <Utasan.h>
#include <balasan.h>
#include <boolean.h>
#include <datetime.h>
#include <graph.h>
#include <kicauan.h>
#include <kicauan_methods.h>
#include <listdin.h>
#include <listlinier.h>
#include <liststatik.h>
#include <matriks.h>
#include <maxheap.h>
#include <pengguna_methods.h>
#include <prioqueue.h>
#include <stack.h>
#include <stdio.h>
#include <tagar.h>
#include <tree.h>
#include <wordmachine.h>

Word perintah;
boolean isStop = false;
Pengguna currentUser;
ListStatik listUser;
ListStatik listTagar;
Graph networkPertemanan;
ListDin listKicauan;
ListLinearUtas ListUtas;
DSU kelompokTeman;
MaxHeap fyb;

void greetings() {
  Word configFolder;
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
  GetWord(&configFolder);
  CreateListStatik(&listUser, PENGGUNA);
  CreateListStatik(&listTagar, TAGARNODE);
  CreateListDinamik(&listKicauan, 10, KICAUAN);
  CreateDSU(&kelompokTeman);
  createMaxHeap(&fyb);
  InvalidateUser(&currentUser);
  createGraph(&networkPertemanan, 20);
  printf("\n");
  if(isDir(configFolder)) {
    MuatPengguna(configFolder.TabWord, &listUser, &networkPertemanan);
    MuatUtas(configFolder.TabWord, &ListUtas);
  }   
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
  if (IsUserValid(currentUser)) {
    printf(
        "Anda sudah masuk. Keluar terlebih dahulu untuk melakukan daftar.\n\n");
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
  if (IsUserValid(currentUser)) {
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
  while (true) {
    PromptUser("Masukkan No HP:", &newNoHP);
    boolean noHpValid = validateNoHP(newNoHP);
    if (noHpValid)
      break;
    else
      printf("No HP tidak valid. Masukkan lagi yuk!\n\n");
  }
  while (true) {
    PromptUser("Masukkan Weton:", &newWeton);
    boolean wetonValid = validateWeton(newWeton);
    if (wetonValid)
      break;
    else
      printf("Weton anda tidak valid.\n\n");
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
  int pos = GetPenggunaIndex(listUser, currentUser.Nama);
  ChangeUserInfo(&listUser.elements[pos], currentUserInDatabase.isValid,
                 currentUserInDatabase.Nama, currentUserInDatabase.KataSandi,
                 newNoHP, newBioAkun, newWeton, currentUserInDatabase.JenisAkun,
                 currentUserInDatabase.FotoProfil);
  printf("Profil Anda sudah berhasil diperbarui!");
  // Pengguna Test;
  // GetUserById(listUser,&Test,currentUser.id);
  // printf("Ini harusnya isi:\n");
  // PrintWord(Test.BioAkun);
}

void DoLihatProfil(Word nama) {
  Pengguna theUser;
  GetUserByName(listUser, &theUser, nama);
  if (UserIsPrivate(theUser) && !WordCmpWord(theUser.Nama, currentUser.Nama)) {
    printf("Wah, akun ");
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
    int pos = GetPenggunaIndex(listUser, currentUser.Nama);
    ChangePrivacy(&listUser.elements[pos], true);
    printf("Akun anda sudah diubah menjadi akun Privat.\n");
  } else {
    ChangePrivacy(&currentUser, false);
    int pos = GetPenggunaIndex(listUser, currentUser.Nama);
    ChangePrivacy(&listUser.elements[pos], false);
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
  Pengguna *currentUserInDatabase;
  GetMutableUserByName(&listUser, &currentUserInDatabase, currentUser.Nama);
  UpdateProfil(&currentUser, m);
  UpdateProfil(currentUserInDatabase, m);
  int pos = GetPenggunaIndex(listUser, currentUser.Nama);
  UpdateProfil(&listUser.elements[pos], m);
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
    if (currentUser.id == friend->id) {
      printf("Anda tidak bisa berteman dengan diri sendiri.\n");
    } else if (ELMT_GRAPH(networkPertemanan, currentUser.id, friend->id) == 1 &&
               ELMT_GRAPH(networkPertemanan, friend->id, currentUser.id) == 0) {
      printf("Anda sudah mengirim permintaan pertemanan kepada ");
      PrintWord(namaPengguna);
      printf(" Silakan tunggu hingga permintaan Anda disetujui.");
      printf(".\n");
    } else if (isTeman(networkPertemanan, currentUser.id, friend->id)) {
      printf("Anda sudah berteman dengan ");
      PrintWord(namaPengguna);
      printf(".\n");
    } else if (ELMT_GRAPH(networkPertemanan, friend->id, currentUser.id) == 1) {
      printf("Anda sudah menerima permintaan pertemanan dari ");
      PrintWord(namaPengguna);
      printf(". Silakan setujui permintaan pertemanan tersebut.");
      printf(".\n");
    } else if (!isTeman(networkPertemanan, currentUser.id, friend->id)) {
      boolean success = TambahTeman(networkPertemanan, currentUser, friend);
      if (success) {
        printf("Permintaan pertemanan kepada ");
        PrintWord(namaPengguna);
        printf(" telah dikirim. Tunggu beberapa saat hingga permintaan Anda "
               "disetujui.\n");
        sendRequest(&networkPertemanan, currentUser.id, friend->id);
      } else {
        printf(
            "Terdapat permintaan pertemanan yang belum Anda setujui. Silakan "
            "kosongkan daftar permintaan pertemanan untuk Anda terlebih "
            "dahulu.");
        printf("\n");
      }
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
    Pengguna p;
    Address addressPenggunaTeratas = GetPermintaanTeratas(currentUser);
    // PrintWord(DATA(addressPenggunaTeratas));
    GetUserByName(listUser, &p, DATA(addressPenggunaTeratas));
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
      addTeman(&networkPertemanan, &kelompokTeman, currentUser.id,
               penggunaTeratas.id);
      printf("Permintaan pertemanan dari ");
      PrintWord(namaPengguna);
      printf(" telah disetujui. Selamat! Anda telah berteman dengan ");
      PrintWord(namaPengguna);
      dequeue(&currentUser.PermintaanBerteman);
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
  if (IsUserValid(currentUser))
    printTeman(listUser, networkPertemanan, currentUser);
  else
    printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
           "BurBir.\n");
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
  printf("Apakah Anda yakin ingin menghapus ");
  PrintWord(namaPengguna);
  PromptUser(" dari daftar teman Anda? (YA/TIDAK)", &response);
  printf("\n");
  if (WordCmp(response, "YA")) {
    hapusTeman(&networkPertemanan, currentUser.id, teman.id);
    PrintWord(namaPengguna);
    // currentUser.PermintaanBerteman->priority--;
    // teman.PermintaanBerteman->priority--;
    printf(" berhasil dihapus dari daftar teman Anda.\n");
  } else {
    printf("Penghapusan teman dibatalkan.\n");
  }
  printf("\n");
}

void DoKicau() {
  Word text, isiTagar;
  PromptUser("Masukkan kicauan:\n", &text);
  PromptUser("Masukkan tagar:\n", &isiTagar);
  Kicauan kicauan;
  createKicauan(&kicauan, currentUser.id, text, isiTagar);
  insertKicauanLast(&listKicauan, kicauan);
  insertKicauanToHeap(&fyb, kicauan);
  if (!WordCmp(isiTagar, "")) {
    addKicauanPadaTagar(&listTagar, kicauan.id, isiTagar);
  }
  printf("Selamat! kicauan telah diterbitkan!\n");
  printf("Detil kicauan:\n");
  showKicauan(kicauan, currentUser.Nama);
}

void DoKicauan() {
  for (int i = 0; i < listKicauan.nEff; i++) {
    int idPengkicau = ELMTDinamik(listKicauan, i).k.idPembuat;
    boolean dariTeman = isTeman(networkPertemanan, currentUser.id, idPengkicau);
    boolean dariSendiri = currentUser.id == idPengkicau;
    if (dariSendiri || dariTeman) {
      Pengguna Author;
      if (dariSendiri) {
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
  if (!found) {
    printf("Tidak ditemukan kicauan dengan ID = %d;\n", idKicau);
    return;
  }
  Pengguna pengkicau;
  GetUserById(listUser, &pengkicau, kicauan.idPembuat);
  boolean dariTeman =
      isTeman(networkPertemanan, currentUser.id, kicauan.idPembuat);
  boolean dariSendiri = (currentUser.id == kicauan.idPembuat);
  if (!UserIsPrivate(pengkicau) || dariTeman || dariSendiri) {
    sukaKicauan(&listKicauan, kicauan.id);
    updateLikeInHeap(&fyb, kicauan.id);
    getKicauanById(listKicauan, &kicauan, idKicau);
    printf("Selamat! kicauan telah disukai!\n");
    printf("Detil kicauan:\n");
    showKicauan(kicauan, pengkicau.Nama);
  } else {
    printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu "
           "ya\n");
  }
}

void DoUbahKicauan(Word idKicauWord) {
  int idKicau = IntFromWord(idKicauWord);
  Kicauan kicauan;
  boolean found = getKicauanById(listKicauan, &kicauan, idKicau);
  if (!found) {
    printf("Tidak ditemukan kicauan dengan ID = %d;\n", idKicau);
    return;
  }
  boolean dariSendiri = (currentUser.id == kicauan.idPembuat);
  if (dariSendiri) {
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

void DoBalas(Word idKicauWord, Word idBalasWord){
  int idKicau = IntFromWord(idKicauWord);
  int idBalas = IntFromWord(idBalasWord);
  Kicauan kicau;
  Pengguna pengkicau;
  if (!getKicauanById(listKicauan, &kicau, idKicau)){
    printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
  } else if (!WordCmp(idBalasWord, "-1")){
    if (searchBalasanById(kicau.treeBalasan, idBalas) == NULL){
      printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
    } else {
      GetUserById(listUser, &pengkicau, kicau.idPembuat);
      if (UserIsPrivate(pengkicau) && !isTeman(networkPertemanan, currentUser.id, pengkicau.id)){
        printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebut!\n");
      } else {
        Word inputBalasan;
        PromptUser("Masukkan Balasan: \n", &inputBalasan);
        Balasan newBalasan;
        Word author = currentUser.Nama;
        createBalasan(&newBalasan, currentUser.id, author, inputBalasan);
        AddressTreeNode newNode = newTreeNode(newBalasan);
        insertTreeNode(newNode, &kicau.treeBalasan, idBalas);
        printf("Selamat! balasan telah diterbitkan!\n");
        printf("Detil balasan: ");
        showBalasan(newBalasan, 0, true);
      }
    }
  } else {
    idBalas = -1;
    GetUserById(listUser, &pengkicau, kicau.idPembuat);
    if (UserIsPrivate(pengkicau) && !isTeman(networkPertemanan, currentUser.id, pengkicau.id)){
      printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebut!\n");
    } else {
      Word inputBalasan;
      PromptUser("Masukkan Balasan: \n", &inputBalasan);
      Balasan newBalasan;
      Word author = currentUser.Nama;
      createBalasan(&newBalasan, currentUser.id, author, inputBalasan);
      AddressTreeNode newNode = newTreeNode(newBalasan);
      insertTreeNode(newNode, &kicau.treeBalasan, idBalas);
      printf("Selamat! balasan telah diterbitkan!\n");
      printf("Detil balasan: ");
      showBalasan(newBalasan, 0, true);
    }
  }
}

void DoBalasan(Word idKicauWord){
  int idKicau = IntFromWord(idKicauWord);
  Kicauan kicau;
  Pengguna pengkicau;
  if (!getKicauanById(listKicauan, &kicau, idKicau)){
    printf("Tidak terdapat kicauan dengan id tersebut!\n");
  } else {
    GetUserById(listUser, &pengkicau, kicau.idPembuat);
    if (UserIsPrivate(pengkicau) && !isTeman(networkPertemanan, currentUser.id, pengkicau.id)){
      printf("Wah, kicauan tersebut dibuat oleh pengguna dengan akun privat!\n");
    } else {
      BinTree tree;
      tree = kicau.treeBalasan;
      if (isTreeEmpty(tree)){
        printf("Belum terdapat balasan apapun pada kicauan tersebut. Yuk balas kicauan tersebut!");
      } else {
        int i;
        boolean friendList[20];
        for (i=0; i<20; i++){
          friendList[i] = isTeman(networkPertemanan, currentUser.id, ELMTPengguna(listUser, i).id);
        }
        friendList[currentUser.id] = true;
        printf("\n");
        printTree(tree, &friendList);
      }
    }
  }
}

void DoHapusBalasan(Word idKicauWord, Word idBalasWord){
  int idKicau = IntFromWord(idKicauWord);
  int idBalas = IntFromWord(idBalasWord);
  Kicauan kicau;
  Pengguna pengkicau;
  if (!getKicauanById(listKicauan, &kicau, idKicau)){
    printf("Tidak terdapat kicauan dengan id tersebut!\n");
  } else {
    GetUserById(listUser, &pengkicau, kicau.idPembuat);
    AddressTreeNode nodeAddress = searchBalasanById(kicau.treeBalasan, idBalas);
    Balasan b = INFO(nodeAddress);
    if (nodeAddress == NULL){
      printf("Balasan tidak ditemukan");
    } else if (b.idPembuat != currentUser.id){
      printf("Hei, ini balasan punya siapa? Jangan dihapus ya!");
    } else {
      deleteTree(nodeAddress);
      printf("Balasan berhasil dihapus\n");
    }
  }
}

void DoBuatDraf() {
  Word textDrafKicauan;
  PromptUser("Masukkan draf:\n", &textDrafKicauan);
  Word command;
  PromptUser(
      "Apakah anda ingin menghapus, menyimpan, atau menerbitkan draf ini?\n",
      &command);
  if (WordCmp(command, "HAPUS")) {
    printf("Draf telah berhasil dihapus!\n");
  } else if (WordCmp(command, "SIMPAN")) {
    DrafKicau drafkicauan;
    CreateDrafKicau(&drafkicauan, textDrafKicauan, GetCurrentDateTime());
    Push(&currentUser.Draf, drafkicauan);
  } else if (WordCmp(command, "TERBIT")) {
    Kicauan kicauan;
    // TODO: should it?
    Word isiTagar;
    createKicauan(&kicauan, currentUser.id, textDrafKicauan, isiTagar);
    insertKicauanLast(&listKicauan, kicauan);
    printf("Selamat! Draf kicauan telah diterbitkan!\n");
    printf("Detil kicauan:\n");
    printf("| ID = %d\n", kicauan.id);
    printf("| ");
    PrintWord(currentUser.Nama);
    printf("\n");
    printf("| ");
    TulisDateTime(kicauan.waktu);
    printf("\n");
    printf("| ");
    PrintWord(kicauan.text);
    printf("\n");
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
    PromptUser("Apakah anda ingin mengubah, menghapus, atau menerbitkan draf "
               "ini? (KEMBALI jika ingin kembali)\n",
               &command);
    if (WordCmp(command, "HAPUS")) {
      printf("Draf telah berhasil dihapus!\n");
    } else if (WordCmp(command, "UBAH")) {
      DoBuatDraf();
    } else if (WordCmp(command, "TERBIT")) {
      Kicauan kicauan;
      Word isiTagar;
      createKicauan(&kicauan, currentUser.id, drafkicauan.text, isiTagar);
      insertKicauanLast(&listKicauan, kicauan);
      printf("Selamat! Draf kicauan telah diterbitkan!\n");
      printf("Detil kicauan:\n");
      printf("| ID = %d\n", kicauan.id);
      printf("| ");
      PrintWord(currentUser.Nama);
      printf("\n");
      printf("| ");
      TulisDateTime(kicauan.waktu);
      printf("\n");
      printf("| ");
      PrintWord(kicauan.text);
      printf("\n");
      printf("| Disukai: %d\n", kicauan.like);
      printf("\n");
    } else if (WordCmp(command, "KEMBALI")) {
      Push(&currentUser.Draf, drafkicauan);
    }
  }
}

void DoUtas(Word idKicauWord) {
  int idKicau = IntFromWord(idKicauWord);
  Kicauan K;
  if (!getKicauanById(listKicauan, &K, idKicau)) {
    printf("Kicauan tidak ditemukan\n");
  } else {
    if (currentUser.id != K.idPembuat) {
      // printf("IDnya %d dan %d\n",currentUser.id,K.id);
      printf("Utas ini bukan milik anda!\n");
    }
    else if (isInList(ListUtas,idKicau)){
    printf("Utas sudah dibuat");
  } 
    else {
      Utas(idKicau, &ListUtas, currentUser.Nama);
    }
  }
}

void DoSambungUtas(Word IDUtasWord, Word indexWord) {
  int IDUtas = IntFromWord(IDUtasWord);
  int index = IntFromWord(indexWord);
  Word Penulis;
  Pengguna InfoPenulis;
  int pos = indexOfListLinearUtas(ListUtas, IDUtas, &Penulis);
  boolean found = GetUserByName(listUser, &InfoPenulis, Penulis);
  if (pos == IDX_UNDEF) {
    printf("Utas tidak ditemukan!");
  } else {
    if (InfoPenulis.id != currentUser.id) {
      printf("Anda tidak bisa menyambung utas ini!");
    } else {
      Sambung_Utas(IDUtas, index, &ListUtas);
    }
  }
}

void DoCetakUtas(Word IDUtasWord) {
  int IDUtas = IntFromWord(IDUtasWord);
  Word Penulis;
  Kicauan K;
  Pengguna InfoPenulis;
  // printf("===========\n");
  if (indexOfListLinearUtas(ListUtas, IDUtas, &Penulis) == IDX_UNDEF) {
    printf("Utas tidak ditemukan!");
  } else {
    boolean found = GetUserByName(listUser, &InfoPenulis, Penulis);
    boolean dariTeman =
        isTeman(networkPertemanan, currentUser.id, InfoPenulis.id);
    boolean dariSendiri = (currentUser.id == InfoPenulis.id);
    if (!UserIsPrivate(InfoPenulis) || dariTeman || dariSendiri) {
      Cetak_Utas(ListUtas, IDUtas, listKicauan, listUser);
    } else {
      printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun "
             "ini untuk melihat utasnya!");
    }
  }
}

void DoHapusUtas(Word IDUtasWord, Word indexWord) {
  int IDUtas = IntFromWord(IDUtasWord);
  int index = IntFromWord(indexWord);
  Word Penulis;
  Pengguna InfoPenulis;
  int pos = indexOfListLinearUtas(ListUtas, IDUtas, &Penulis);
  boolean found = GetUserByName(listUser, &InfoPenulis, Penulis);
  if (pos == IDX_UNDEF) {
    printf("Utas tidak ditemukan!");
  } else {
    if (InfoPenulis.id != currentUser.id) {
      printf("Anda tidak bisa menghapus kicauan dalam utas ini!");
    } else {
      Hapus_Utas(IDUtas, index, &ListUtas);
    }
  }
}

void DoCariKicauan(Word isiTagar) {
  showKicauanDenganTagar(listTagar, listUser, listKicauan, isiTagar);
}

void DoKelompokTeman() {
  printKelompokTeman(listUser, kelompokTeman, currentUser);
}

void DoFYB() { tampilkanKicauanTerbaik(fyb, listUser); }

void DoPerintah() {
  Word action, args1, args2;
  ParseWord(&perintah, ' ', &action, &args1, &args2);
  if (WordCmp(action, "KELUAR")) {
    DoKeluar();
  } else if (WordCmp(action, "DAFTAR")) {
    DoDaftar();
  } else if (WordCmp(action, "MASUK")) {
    DoMasuk();
  } else if (WordCmp(action, "TUTUP_PROGRAM")) {
    DoTutupProgram();
  } else if (WordCmp(action, "GANTI_PROFIL")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoGantiProfil();
    }
  } else if (WordCmp(action, "LIHAT_PROFIL")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoLihatProfil(args1);
    }
  } else if (WordCmp(action, "ATUR_JENIS_AKUN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoAturJenisAkun();
    }
  } else if (WordCmp(action, "UBAH_FOTO_PROFIL")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoUbahFotoProfil();
    }
  } else if (WordCmp(action, "TAMBAH_TEMAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoTambahTeman();
    }
  } else if (WordCmp(action, "DAFTAR_PERMINTAAN_PERTEMANAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoDaftarPermintaanPertemanan();
    }
  } else if (WordCmp(action, "SETUJUI_PERTEMANAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoSetujuiPertemanan();
    }
  } else if (WordCmp(action, "DAFTAR_TEMAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoDaftarTeman();
    }
  } else if (WordCmp(action, "HAPUS_TEMAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoHapusTeman();
    }
  } else if (WordCmp(action, "KICAU")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoKicau();
    }
  } else if (WordCmp(action, "KICAUAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoKicauan();
    }
  } else if (WordCmp(action, "SUKA_KICAUAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoSukaKicauan(args1);
    }
  } else if (WordCmp(action, "UBAH_KICAUAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoUbahKicauan(args1);
    }
  } else if (WordCmp(action, "BALAS")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoBalas(args1, args2);
    }
  } else if (WordCmp(action, "BALASAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoBalasan(args1);
    }
  } else if (WordCmp(action, "HAPUS_BALASAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoHapusBalasan(args1, args2);
    }
  } else if (WordCmp(action, "BUAT_DRAF")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoBuatDraf();
    }
  } else if (WordCmp(action, "LIHAT_DRAF")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoLihatDraf();
    }
  } else if (WordCmp(action, "UTAS")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoUtas(args1);
    }
  } else if (WordCmp(action, "SAMBUNG_UTAS")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoSambungUtas(args1, args2);
    }
  } else if (WordCmp(action, "CETAK_UTAS")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoCetakUtas(args1);
    }
  } else if (WordCmp(action, "SIMPAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      SIMPANUTAS(ListUtas, "config");
      simpanPengguna("config", listUser, networkPertemanan);
    }
  } else if (WordCmp(action, "HAPUS_UTAS")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoHapusUtas(args1, args2);
    }
  } else if (WordCmp(action, "CARI_KICAUAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoCariKicauan(args1);
    }
  } else if (WordCmp(action, "KELOMPOK_TEMAN")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoKelompokTeman();
    }
  } else if (WordCmp(action, "FYB")) {
    if (!IsUserValid(currentUser)) {
      printf("Anda belum masuk! Masuk terlebih dahulu untuk menikmati layanan "
             "BurBir.\n");
    } else {
      DoFYB();
    }
  } else {
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
