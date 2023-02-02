#ifndef LIST_H
#define LIST_H

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

list *list_new();
void list_add(list *l, void *data);
void list_remove(list *l, void *data);
void* list_get(list *l, int index);
void list_set(list *l, int index, void *data);
void list_free(list *l);
void list_deleteAt(list *l, int index);
void list_insertAt(list *l, int index, void *data);
void list_clear(list *l);
int list_Lenght(list *l);
void list_print(list *l,char *format);
int list_indexOf(list *l, void *data);
void** list_toArray(list *l);


#endif