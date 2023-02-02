#ifndef TABSTRUCT_H
#define TABSTRUCT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_UNDO_LEVEL 20

typedef struct TabStruct
{
    GtkWidget *tab;
    GtkWidget *textview;
    GtkWidget *scrollbar;
    char *path;
    char *filename;

    GtkTextBuffer *buffer;
    GList *undo_stack;
    GList *redo_stack;
} TabStruct;

TabStruct *createTabStruct(char *path, char *filename);
void freeTabStruct(TabStruct *tabStruct);

void save_state(TabStruct* tabStruct);
void undo_text(TabStruct* tabStruct);
void redo_text(TabStruct* tabStruct);



#endif // TABSTRUCT_H