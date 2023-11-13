#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main()
{
    User user1;
    User user2;
    User user3;
    Graph graph;
    createGraph(&graph, 20);
    createUser(&user1, "user1", 100);
    createUser(&user2, "user2", 200);
    createUser(&user3, "user3", 300);

    addTeman(&graph, INDEX_USER(user1), INDEX_USER(user2));
    addTeman(&graph, INDEX_USER(user1), INDEX_USER(user3));
    hapusTeman(&graph, INDEX_USER(user1), INDEX_USER(user2));

    printTeman(graph, user1, INDEX_USER(user1));
    printf("====================================\n");
    printTeman(graph, user2, INDEX_USER(user2));
    printf("====================================\n");
    boolean tes = isNoTeman(graph, INDEX_USER(user1));
    printf("%d\n", tes);
    printf("====================================\n");
    tes = isTeman(graph, INDEX_USER(user1), INDEX_USER(user3));
    printf("%d\n", tes);

    return 0;
}