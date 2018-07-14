#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "linked_list.h"

int list_length = 0;

Node *create_node() {
    Node *node = malloc(sizeof(Node));
    assert(node != NULL);
    node->data = "";
    node->next = NULL;
    return node;
}

List *create_list() {
    List *list = malloc(sizeof(List));
    assert(list != NULL);
    Node *node = create_node();
    list->head = node;
    return list;
}

void destroy_list(List *list) {
    assert(list != NULL);
    Node *node = list->head;
    Node *next;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(list);
    list_length = 0;
}

void add(List *list, char *str) {
    assert(list != NULL);
    assert(str != NULL);
    Node *node = list->head;
    while (node->next != NULL)
        node = node->next;
    node->data = str;
    node->next = create_node();
    list_length++;
}

int length(List *list) {
    return list_length;
}

char **to_array(List *list) { // returns a NULL terminated array of strings, the command arguments
    assert(list != NULL);
    char **array = malloc((list_length + 1) * sizeof(char *));
    Node *node = list->head;
    for (int i = 0; i < list_length; ++i) {
        array[i] = node->data; // already allocated
        node = node->next;
    }
    array[list_length] = NULL;
    return array;
}

void print(List *list) {
    assert(list != NULL);
    printf("[");
    Node *node = list->head;
    while (node->next != NULL) {
        printf("%s", node->data);
        node = node->next;
        if (node->next != NULL)
            printf(", ");
    }
    printf("]\n");
}