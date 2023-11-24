#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    int input;
    scanf("Masukkan test case: %d", &input);
    switch (input)
    { 
    case 1:
        printf("Test case 1\n");
        Graph G;
        CreateEmptyGraph(&G);
        print("IsNoTeman User 1: ", isNoTeman(G,1));
        print("IsTeman User 1 with User 2: ", isTeman(G,1,2));
        print("Jumlah teman user 1: %d:",jumlahTeman(G,1));
        print("Jumlah teman user 2: %d:",jumlahTeman(G,2));
        printf("Menambahkan teman user 1 dengan user 2\n");
        sendRequest(&G,1,2);
        break;
    }
}