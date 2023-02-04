#ifndef TABSTRUCT_H
#define TABSTRUCT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_UNDO_LEVEL 200
typedef struct TabStruct TabStruct;

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
    int HasChanged;

    void (*setTagColor)(TabStruct*);
    void (*colorize)(TabStruct*);
} TabStruct;

TabStruct *createTabStruct(char *path, char *filename);
void freeTabStruct(TabStruct *tabStruct);
void clear_undo_redo(TabStruct* tabStruct);

TabStruct * open_file(TabStruct *tab, char *AbsPath, char *filename);
void save_file(TabStruct *tab);

void save_state(TabStruct* tabStruct);
void undo_text(TabStruct* tabStruct);
void redo_text(TabStruct* tabStruct);

void addKeyBinding(TabStruct *tabStruct);
void addTab(TabStruct *tabStruct);
void removeTab(TabStruct *tabStruct);
void setTagColor(GtkTextBuffer *buffer);
void colorize(GtkTextBuffer *buffer);



#endif // TABSTRUCT_H