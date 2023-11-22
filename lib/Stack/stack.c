#include <stdio.h>
#include "../MesinKata/wordmachine.h"
#include "../Sederhana/datetime.h"
#include "stack.h"

void CreateDrafKicau(DrafKicau *D, Word text) {
    D->text = text;
    D->waktu = GetCurrentDateTime();
}

void DisplayDrafKicau(DrafKicau D) {
    printf("| ");TulisDateTime(D.waktu);printf("\n");
    printf("| ");PrintWord(D.text);printf("\n");
}

void CreateStack(Stack *S) {
    Top(*S) = Nil;
}

boolean IsEmptyStack(Stack S) {
    return Top(S) == Nil;
}

boolean IsFullStack(Stack S) {
    return Top(S) == MaxEl-1;
}

void Push(Stack * S, infotype X) {
    Top(*S)++;
    InfoTop(*S) = X;
}

void Pop(Stack * S, infotype* X) {
    *X = InfoTop(*S);
    Top(*S)--;
}