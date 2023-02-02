#ifndef MENUBARFUNC_H
#define MENUBARFUNC_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void on_newFile_clicked(GtkWidget *widget, gpointer data);
void on_openFile_clicked(GtkWidget *widget, gpointer data);
void on_saveFile_clicked(GtkWidget *widget, gpointer data);
void on_saveAsFile_clicked(GtkWidget *widget, gpointer data);
void on_saveAllFile_clicked(GtkWidget *widget, gpointer data);
void on_closeFile_clicked(GtkWidget *widget, gpointer data);
void on_quit_clicked(GtkWidget *widget, gpointer data);
void on_undo_clicked(GtkWidget *widget, gpointer data);
void on_redo_clicked(GtkWidget *widget, gpointer data);
void on_cut_clicked(GtkWidget *widget, gpointer data);
void on_copy_clicked(GtkWidget *widget, gpointer data);
void on_paste_clicked(GtkWidget *widget, gpointer data);
void on_delete_clicked(GtkWidget *widget, gpointer data);
void on_selectAll_clicked(GtkWidget *widget, gpointer data);
#endif