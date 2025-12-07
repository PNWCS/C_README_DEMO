#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

typedef struct Node {
    char* ip;
    struct Node* next;
} Node;

static Node* table[TABLE_SIZE];

void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
}

static unsigned int hash(const char* str) {
    unsigned int h = 5381;
    int c;
    while ((c = *str++)) {
        h = ((h << 5) + h) + c;
    }
    return h % TABLE_SIZE;
}

bool insert_ip(const char* ip) {
    unsigned int index = hash(ip);

    Node* cur = table[index];
    while (cur) {
        if (strcmp(cur->ip, ip) == 0) {
            return false;
        }
        cur = cur->next;
    }

    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    new_node->ip = strdup(ip);
    if (!new_node->ip) {
        fprintf(stderr, "strdup failed\n");
        exit(1);
    }
    new_node->next = table[index];
    table[index] = new_node;

    return true;
}

void free_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* cur = table[i];
        while (cur) {
            Node* temp = cur;
            cur = cur->next;
            free(temp->ip);
            free(temp);
        }
        table[i] = NULL;
    }
}
