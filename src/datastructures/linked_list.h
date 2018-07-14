#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<stdlib.h>

typedef struct NodeTag {
    char *data;
    struct NodeTag *next;
} Node;

typedef struct ListTag {
    struct NodeTag *head;
} List;

Node *create_node();

List *create_list();

void destroy_list(List *list);

void add(List *list, char *str);

int length(List *list);

char **to_array(List *list);

void print(List *list);

#endif
