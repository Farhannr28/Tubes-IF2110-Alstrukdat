#include "../ListLinier/listlinier.h"
#include "../MesinKarakter/charmachine.h"
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/ctime.h"
#include "../Sederhana/datetime.h"
#include "../utility/boolean.h"
#include "../Utasan/Utasan.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
void SIMPANUTAS(ListLinearUtas ListUtas, const char *folderName) {
    char dirPath[1024];
    snprintf(dirPath, sizeof(dirPath), "%s", folderName);
    struct stat st = {0};
    if (stat(dirPath, &st) == -1) {
        if (mkdir(dirPath) != 0) {
            fprintf(stderr, "Failed to create directory: %s\n", dirPath);
            return;
        }
    }

    char filePath[1024];
    snprintf(filePath, sizeof(filePath), "%s/utas.config", dirPath);

    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s for writing.\n", filePath);
        return;
    }
    AddressUtas p = ListUtas;
    int panjang = lengthListLinearUtas(ListUtas);
    fprintf(file, "%d\n", panjang); // Include newline

    while (p != NULL) {
        Utasan current_utasan = INFO(p);
        fprintf(file, "%d\n", IDKicauan(p)); // Include newline
        int banyakutas = BanyakUtasan(ListUtas, IDKicauan(p));
        fprintf(file, "%d\n", banyakutas); // Include newline
        // printf("IdKicau %d\n",banyakutas);
        Paragraph *current_paragraph = p->info.TextList;
        int utasCount = 1; // Keep track of the utas number
        while (current_paragraph != NULL) {
            char dateTimeStr[20];
            char ConfigText[281], PenulisSTR[281];
            Word Text = current_paragraph->text;
            DATETIME D = current_paragraph->DateTime;
            GetCharsFromWord(Text,ConfigText);
            GetCharsFromWord(current_utasan.Penulis, PenulisSTR);

            format_datetime(&D, dateTimeStr, sizeof(dateTimeStr));

            // fprintf(file, "Utas ke-%d\n", utasCount); 
            fprintf(file, "%s\n", ConfigText); 
            fprintf(file, "%s\n", PenulisSTR); 
            fprintf(file, "%s\n", dateTimeStr); 

            current_paragraph = current_paragraph->next;
            utasCount++;
            // printf("It runs %d times\n",utasCount);
        }
        p = p->next;
        // break;

    }
    fclose(file);
}
