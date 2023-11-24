#include "../ListLinier/listlinier.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../utility/boolean.h"
#include "../Utasan/Utasan.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
void str_copy(char *dest, const char *src, size_t dest_size) {
    size_t i;
    for (i = 0; src[i] != '\0' && i < dest_size - 1; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0'; 
}

void str_concat(char *dest, const char *src, size_t dest_size) {
    size_t i = 0;
    while (dest[i] != '\0' && i < dest_size) {
        i++;
    }

    if (i < dest_size - 1) {
        size_t j;
        for (j = 0; src[j] != '\0' && i + j < dest_size - 1; j++) {
            dest[i + j] = src[j]; 
        }
        dest[i + j] = '\0'; 
    }
}


void SIMPANUTAS(ListLinearUtas ListUtas, const char *folderName) {
    char dirPath[1024];
    str_copy(dirPath, folderName, sizeof(dirPath));
    struct stat st = {0};
    if (stat(dirPath, &st) == -1) {
        if (mkdir(dirPath) != 0) {
            fprintf(stderr, "Failed to create directory: %s\n", dirPath);
            return;
        }
    }

    char filePath[1024];
    str_copy(filePath, dirPath, sizeof(filePath));
    str_concat(filePath, "/utas.config", sizeof(filePath));
    printf("%s\n",filePath);
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s for writing.\n", filePath);
        return;
    }
    AddressUtas p = ListUtas;
    int panjang = lengthListLinearUtas(ListUtas);
    fprintf(file, "%d\n", panjang); 

    while (p != NULL) {
        Utasan current_utasan = INFO(p);
        fprintf(file, "%d\n", IDKicauan(p)); 
        int banyakutas = BanyakUtasan(ListUtas, IDKicauan(p));
        fprintf(file, "%d\n", banyakutas);
        Paragraph *current_paragraph = p->info.TextList;
        int utasCount = 1; 
        while (current_paragraph != NULL) {
            char dateTimeStr[20];
            char ConfigText[281], PenulisSTR[281];
            Word Text = current_paragraph->text;
            DATETIME D = current_paragraph->DateTime;
            GetCharsFromWord(Text,ConfigText);
            GetCharsFromWord(current_utasan.Penulis, PenulisSTR);

            format_datetime(&D, dateTimeStr, sizeof(dateTimeStr));
            fprintf(file, "%s\n", ConfigText); 
            fprintf(file, "%s\n", PenulisSTR); 
            fprintf(file, "%s\n", dateTimeStr); 

            current_paragraph = current_paragraph->next;
            utasCount++;
        }
        p = p->next;
    }
    fclose(file);
}
