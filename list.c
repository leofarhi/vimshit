#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    void *data;
} list_node;

typedef struct list {
    list_node *head;
    list_node *tail;
    int size;
} list;
*/

list *list_new() {
    list *l = malloc(sizeof(list));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}
void list_add(list *l, void *data) {
    list_node *node = malloc(sizeof(list_node));
    node->data = data;
    node->next = NULL;
    node->prev = l->tail;
    if (l->tail != NULL) {
        l->tail->next = node;
    }
    l->tail = node;
    if (l->head == NULL) {
        l->head = node;
    }
    l->size++;
}
void list_remove(list *l, void *data) {
    list_node *node = l->head;
    while (node != NULL) {
        if (node->data == data) {
            if (node->prev != NULL) {
                node->prev->next = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            if (node == l->head) {
                l->head = node->next;
            }
            if (node == l->tail) {
                l->tail = node->prev;
            }
            free(node);
            l->size--;
            return;
        }
        node = node->next;
    }
}
void* list_get(list *l, int index) {
    list_node *node = l->head;
    int i = 0;
    while (node != NULL) {
        if (i == index) {
            return node->data;
        }
        i++;
        node = node->next;
    }
    return NULL;
}

void list_set(list *l, int index, void *data){
    list_node *node = l->head;
    int i = 0;
    while (node != NULL) {
        if (i == index) {
            node->data = data;
            return;
        }
        i++;
        node = node->next;
    }
}
void list_free(list *l) {
    list_node *node = l->head;
    while (node != NULL) {
        list_node *next = node->next;
        free(node);
        node = next;
    }
    free(l);
}
void list_deleteAt(list *l, int index) {
    list_node *node = l->head;
    int i = 0;
    while (node != NULL) {
        if (i == index) {
            if (node->prev != NULL) {
                node->prev->next = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            if (node == l->head) {
                l->head = node->next;
            }
            if (node == l->tail) {
                l->tail = node->prev;
            }
            free(node);
            l->size--;
            return;
        }
        i++;
        node = node->next;
    }
}
void list_insertAt(list *l, int index, void *data) {
    list_node *node = l->head;
    int i = 0;
    while (node != NULL) {
        if (i == index) {
            list_node *newNode = malloc(sizeof(list_node));
            newNode->data = data;
            newNode->next = node;
            newNode->prev = node->prev;
            if (node->prev != NULL) {
                node->prev->next = newNode;
            }
            node->prev = newNode;
            if (node == l->head) {
                l->head = newNode;
            }
            l->size++;
            return;
        }
        i++;
        node = node->next;
    }
}
void list_clear(list *l) {
    list_node *node = l->head;
    while (node != NULL) {
        list_node *next = node->next;
        free(node);
        node = next;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}
int list_Lenght(list *l) {
    return l->size;
}
void list_print(list *l,char *format) {
    list_node *node = l->head;
    printf("[");
    while (node != NULL) {
        printf(format,node->data);
        if (node->next != NULL) {
            printf(",");
        }
        node = node->next;
    }
    printf("]\n");
}
int list_indexOf(list *l, void *data){
    list_node *node = l->head;
    int i = 0;
    while (node != NULL) {
        if (node->data == data) {
            return i;
        }
        i++;
        node = node->next;
    }
    return -1;
}

void** list_toArray(list *l){
    void **array = malloc(sizeof(void*)*l->size);
    list_node *node = l->head;
    int i = 0;
    while (node != NULL) {
        array[i] = node->data;
        i++;
        node = node->next;
    }
    return array;
}