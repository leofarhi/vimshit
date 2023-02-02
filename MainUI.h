#ifndef MAINUI_H
#define MAINUI_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

extern GtkWidget *window;
extern GtkWidget *notebook;

typedef struct TabStruct TabStruct;

extern list *tabList;

void on_window_destroy(GtkWidget *widget, gpointer data);

void create_main_ui();

void make_menu_bar(GtkWidget *vbox);

void main_panel(GtkWidget *vbox);

GtkWidget* GetCurTab();

GtkWidget* GetCurPage();

GtkWidget* GetCurTextView();

TabStruct* GetCurTabStruct();
int AlreadyOpen(char *path);

#endif