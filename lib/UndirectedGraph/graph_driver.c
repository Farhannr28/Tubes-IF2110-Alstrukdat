#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    int input;
    printf("List Test Case:\n");
    printf("1. Test untuk isNoTeman\n");
    printf("2. Test case untuk isTeman\n");
    printf("3. Test case untuk jumlahTeman\n");
    printf("4. Test case untuk sendRequest\n");
    printf("Masukkan test case:\n");
    scanf("%d", &input);
    switch (input)
    { 
    case 1:
        printf("Test untuk isNoTeman\n");
        Graph G;
        CreateEmptyGraph(&G);
        print("IsNoTeman User 1: ", isNoTeman(G,1));
        printf("IsNoTeman User 1: ", isNoTeman(G,0));
        printf("isNoTeman User 2: ", isNoTeman(G,1));
        print("IsNoTeman User 20: ", isNoTeman(G,19));
        break;

    case 2 :
        printf("Test case untuk isTeman\n");
        Graph G;
        CreateEmptyGraph(&G);
        ELMT_GRAPH(G,5,6) = 1;
        ELMT_GRAPH(G,6,5) = 1;
        for(int i = 0; i < MAX_SIMPUL; i++){
            for(int j = 0; j < MAX_SIMPUL; j++){
                printf("%d", ELMT_GRAPH(G,i,j));
            }
        }
        printf("IsTeman User 1 with User 2: ", isTeman(G,0,1));
        printf("isTeman User 2 with User 1: ", isTeman(G,1,0));
        printf("IsTeman User 20 with User 19: ", isNoTeman(G,19,18));
        printf("IsTeman User 6 with User 7: ", isNoTeman(G,5,6));
        printf("IsTeman User 7 with User 6: ", isNoTeman(G,6,5));
        break;
    case 3:
        printf("Test case untuk jumlahTeman\n");
        Graph G;
        CreateEmptyGraph(&G);
        ELMT_GRAPH(G,5,6) = 1;
        ELMT_GRAPH(G,6,5) = 1;
        ELMT_GRAPH(G,5,7) = 1;
        ELMT_GRAPH(G,7,5) = 1;
        ELMT_GRAPH(G,5,8) = 1;
        ELMT_GRAPH(G,8,5) = 1;
        ELMT_GRAPH(G,5,9) = 1;
        ELMT_GRAPH(G,9,5) = 1;
        ELMT_GRAPH(G,6,10) = 1;
        ELMT_GRAPH(G,10,6) = 1;
        for(int i = 0; i < MAX_SIMPUL; i++){
            for(int j = 0; j < MAX_SIMPUL; j++){
                printf("%d", ELMT_GRAPH(G,i,j));
            }
        }
        printf("Jumlah teman user 1: %d\n ", jumlahTeman(G,0));
        printf("Jumlah teman user 2: %d\n", jumlahTeman(G,1));
        printf("Jumlah teman user 5: %d\n", jumlahTeman(G,4));
        printf("Jumlah teman user 6: %d\n", jumlahTeman(G,5));
        printf("Jumlah teman user 7: %d\n", jumlahTeman(G,6));
        printf("Jumlah teman user 8: %d\n", jumlahTeman(G,7));
        printf("Jumlah teman user 9: %d\n", jumlahTeman(G,8));
        printf("Jumlah teman user 10: %d\n", jumlahTeman(G,9));
        break;

        case 4:
        printf("Test case untuk sendRequest\n");
        Graph G;
        CreateEmptyGraph(&G);
        printf("Send request dari user 1 ke user 2\n"); 
        sendRequest(&G,0,1);
        printf("Send request dari user 3 ke user 4\n");
        sendRequest(&G,2,3);
        printf("Send request dari user 5 ke user 6\n");
        sendRequest(&G,4,5);
        for(int i = 0; i < MAX_SIMPUL; i++){
            for(int j = 0; j < MAX_SIMPUL; j++){
                printf("%d", ELMT_GRAPH(G,i,j));
            }
        }
        break;
        default : 
            printf("Test case tidak ada\n");
    }
}