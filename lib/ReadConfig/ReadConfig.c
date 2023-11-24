// #include "../ListLinier/listlinier.h"
// #include "../Utasan/Utasan.h"
#include "stdio.h"
#include "../utility/boolean.h"
#include "../MesinKata/wordmachine.h"
#include "../MesinKarakter/charmachine.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../Pengguna/pengguna_methods.h"
#include "../UndirectedGraph/graph.h"
#include "../Kicauan/kicauan.h"
#include "../Kicauan/kicauan_methods.h"
#include "../Stack/stack.h"
#include "../MaxHeap/maxheap.h"
#include "string.h"
// #include "../Sederhana/datetime.h"
#include "ReadConfig.h"

boolean MuatUtas(char *namafolder, ListLinearUtas *l1){
    FILE *fUtas;
    boolean sukses = true;
    Utasan Utas;
    int IDUtas = 0;
    char configfile[100];
    Word InputText;
    Word Penulis;
    Word jumlahutasan;
    snprintf(configfile, sizeof(configfile), "../../config/utas.config");
    // printf("File %s\n",configfile);
    fUtas = fopen(configfile,"r");
    if (fUtas == NULL) {
        printf("Tidak ada file konfigurasi utas.\n");
        sukses = false;
    } else {
        printf("File utas ditemukan\n");
        char line[280];
        char id;
        char m;
        char jumlahutas; 
        fscanf(fUtas, "%c", &jumlahutas);
        if (jumlahutas == '\n') {
            fgets(line, 280, fUtas); 
        } else {
            ungetc(jumlahutas, fUtas);
        }
        fgets(line, 280, fUtas);
        AssignWord(&jumlahutasan,line);
        int hasiljumlahutasan,i,j;
        hasiljumlahutasan = IntFromWord(jumlahutasan);
        for (i=0;i<hasiljumlahutasan;i++){
            IDUtas+=1;
            fscanf(fUtas, "%c", &id);
            if (id == '\n') {
                fgets(line, 280, fUtas); 
            } else {
                ungetc(id, fUtas);
            }
            fgets(line, 280, fUtas);
            printf("line:%s",line);
            Word IDKicau;
            AssignWord(&IDKicau,line);
            PrintWord(IDKicau);
            int idKicau = IntFromWord(IDKicau);
            fscanf(fUtas, "%c", &m);
            if (m == '\n') {
                fgets(line, 280, fUtas); 
            } else {
                ungetc(m, fUtas);
            }
            fgets(line, 280, fUtas);
            Word Index;
            AssignWord(&Index,line);
            printf("Index:\n");
            PrintWord(Index);
            int jumlahindex = IntFromWord(Index);
            for (j=0;j<jumlahindex;j++){
                char text[500];
                fgets(text, sizeof(text), fUtas);
                AssignWord(&InputText,text);
                fgets(line,280,fUtas);
                AssignWord(&Penulis,line);
                fgets(text,sizeof(text),fUtas);
                Word DateWord;
                AssignWord(&DateWord,text);
                Word Date,Month,Year,Hour,Minute,Second,DateText,TimeText;
                DATETIME D;
                int dd,mm,yy,hh,minn,ss;
                ParseWord(&DateWord,' ',&DateText,&TimeText);
                ParseWord(&DateText,'/',&Date,&Month,&Year);
                ParseWord(&TimeText,':',&Hour,&Minute,&Second);
                // printf("Detik:\n");
                // PrintWord(Second);
                dd = IntFromWord(Date);
                mm = IntFromWord(Month);
                yy = IntFromWord(Year);
                hh = IntFromWord(Hour);
                minn = IntFromWord(Minute);
                ss = IntFromWord(Second);
                // printf("Detik:%d\n",ss);
                CreateDateTime(&D,dd,mm,yy,hh,minn,ss);
                if(j==0){
                    CreateUtas(&Utas,IDUtas,idKicau,InputText,Penulis,D);
                }
                else{
                    insertLastParagraph(&Utas,InputText,D);
                    // printf("Ini adalah:\n");
                    // PrintWord(InputText);
                }
            }
        insertFirstListLinearUtas(l1,Utas);
        }
    }
    fclose(fUtas);
    return sukses;
}

boolean MuatPengguna(char *namafolder, ListStatik* listUser, Graph* networkPertemanan) {
    FILE *fUser = fopen(namafolder, "r");
    if (fUser == NULL) {
        printf("Tidak ada file konfigurasi pengguna.\n");
        return false;
    } else {
        Word jumlahUser;
        ReadFileLine(&jumlahUser, fUser);
        for (int i = 0; i < IntFromWord(jumlahUser); i++) {
            Word nama, password, bio, noHP, weton, jenisAkun, fotoProfil;
            ReadFileLine(&nama, fUser);
            ReadFileLine(&password, fUser);
            ReadFileLine(&bio, fUser);
            ReadFileLine(&noHP, fUser);
            ReadFileLine(&weton, fUser);
            ReadFileLine(&jenisAkun, fUser);
            ReadFileNLine(&fotoProfil, fUser, 5);
            Matriks mFotoProfil;
            MatriksFromWord(&mFotoProfil, fotoProfil);
            Pengguna p;
            CreatePenggunaFullInfo(&p, nama, password, bio, noHP, weton, jenisAkun, mFotoProfil);
            insertLastListPengguna(listUser, p);
        }
        Word pertemanan;
        ReadFileNLine(&pertemanan, fUser, IntFromWord(jumlahUser));
        PrintWord(pertemanan);
        GraphFromWord(networkPertemanan, pertemanan);
        Word jumlahPermintaanTeman;
        ReadFileLine(&jumlahPermintaanTeman, fUser);
        for (int i = 0; i < IntFromWord(jumlahPermintaanTeman); i++) {
            Word line, from, to, _;
            ReadFileLine(&line, fUser);
            ParseWord(&line, ' ', &from, &to, &_);
            Pengguna *friend;
            Pengguna currentUser;
            GetMutableUserById(listUser, &friend, IntFromWord(from));
            GetUserById(*listUser, &currentUser, IntFromWord(to));
            TambahTeman(*networkPertemanan, currentUser, friend);
            sendRequest(networkPertemanan, IntFromWord(from), IntFromWord(to));
        }
    }
    fclose(fUser);
}

boolean MuatKicau(char *namafolder, ListDin* ListKicauan, ListStatik ListUser, MaxHeap* fyb){
    FILE *fUser = fopen(namafolder, "r");
    if (fUser == NULL) {
        printf("Tidak ada file konfigurasi kicauan.\n");
        return false;
    } else {
        Word banyakKicauWord;
        ReadFileLine(&banyakKicauWord, fUser);
        int banyakKicau;
        banyakKicau = IntFromWord(banyakKicauWord);
        int i;
        Kicauan k;
        Pengguna Author;
        Word idKicau, text, like, author, dateTime;
        Word Date,Month,Year,Hour,Minute,Second,DateText,TimeText;
        DATETIME D;
        Word null;
        for (i = 0; i < banyakKicau; i++) {
            ReadFileLine(&idKicau, fUser);
            ReadFileLine(&text, fUser);
            ReadFileLine(&like, fUser);
            ReadFileLine(&author, fUser);
            ReadFileLine(&dateTime, fUser);
            GetUserByName(ListUser, &Author, author);
            int dd,mm,yy,hh,minn,ss;
            ParseWord(&dateTime,' ',&DateText,&TimeText);
            ParseWord(&DateText,'/',&Date,&Month,&Year);
            ParseWord(&TimeText,':',&Hour,&Minute,&Second);
            dd = IntFromWord(Date);
            mm = IntFromWord(Month);
            yy = IntFromWord(Year);
            hh = IntFromWord(Hour);
            minn = IntFromWord(Minute);
            ss = IntFromWord(Second);
            CreateDateTime(&D,dd,mm,yy,hh,minn,ss);
            k.id = IntFromWord(idKicau);
            k.text = text;
            k.idPembuat = Author.id;
            k.like = IntFromWord(like);
            k.waktu = D;
            k.treeBalasan = NULL;
            k.tagar = null;
            insertKicauanLast(&ListKicauan, k);
            insertKicauanToHeap(&fyb, k);
        }
    }
    fclose(fUser);
}

boolean MuatBalas(char *namafolder, ListDin* listKicauan){

}

boolean MuatDraf(char *namaFolder, ListStatik *listUser) {
    FILE *fDraf = fopen(namaFolder, "r");
    if (fDraf == NULL) {
        printf("Tidak ada file konfigurasi Draf.\n");
        return false;
    } else {
        Word jumlahDraf;
        ReadFileLine(&jumlahDraf, fDraf);
        for (int i=0; i<IntFromWord(jumlahDraf); i++) {
            Word info;
            ReadFileLine(&info, fDraf);
            Word nama, banyakDraf, parse1, parse2, parse3, parse4;
            ParseWord(&info, ' ', &parse1, &parse2, &parse3, &parse4); // Asumsi nama tidak ada yang > 3 kata
            if (isWordNumeric(parse2)) {
                AssignWordFromWord(parse1, &nama);
                AssignWordFromWord(parse2, &banyakDraf);
            } else if (isWordNumeric(parse3)) {
                ConcatWordWithSpace(&parse1, parse2);
                AssignWordFromWord(parse1, &nama);
                AssignWordFromWord(parse3, &banyakDraf);
            } else {
                ConcatWordWithSpace(&parse1, parse2);
                ConcatWordWithSpace(&parse1, parse3);
                AssignWordFromWord(parse1, &nama);
                AssignWordFromWord(parse4, &banyakDraf);
            }
            int j=0;
            boolean done=false;
            Word textDraf, dateTimeDraf;
            while (j<ListStatikLength(*listUser) && !done) {
                if (WordCmpWord(ELMTPengguna(*listUser, i).Nama, nama)) {
                    Stack S;
                    CreateStack(&S);
                    for (int k=0; k<IntFromWord(banyakDraf); k++) {
                        DATETIME D;
                        DrafKicau draf;
                        ReadFileLine(&textDraf, fDraf);
                        ReadFileLine(&dateTimeDraf, fDraf);
                        Word wDay, wMonth, wYear, wHour, wMinute, wSecond, wDate, wTime;
                        int dd, mm, yy, hh, min, ss;
                        ParseWord(&dateTimeDraf, ' ', &wDate, &wTime);
                        ParseWord(&wDate, '/', &wDay, &wMonth, &wYear);
                        ParseWord(&wTime, ':', &wHour, &wMinute, &wSecond);
                        dd = IntFromWord(wDay);
                        mm = IntFromWord(wMonth);
                        yy = IntFromWord(wYear);
                        hh = IntFromWord(wHour);
                        min = IntFromWord(wMinute);
                        ss = IntFromWord(wSecond);
                        CreateDateTime(&D, dd, mm, yy, hh, min, ss);
                        CreateDrafKicau(&draf, textDraf, D);
                        S.T[IntFromWord(banyakDraf)-1] = draf;
                    }
                    Top(S) = IntFromWord(banyakDraf)-1;
                }
                i++;
            }
        }
    }
    fclose(fDraf);
}