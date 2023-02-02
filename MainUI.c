#include "MainUI.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabStruct.h"
#include "MenuBarFunc.h"

GtkWidget *window = NULL;
GtkWidget *notebook = NULL;
list *tabList = NULL;

void on_window_destroy(GtkWidget *widget, gpointer data) {
  GtkWidget *dialog;
  gint response;

  dialog = gtk_message_dialog_new(GTK_WINDOW(widget),
                                  GTK_DIALOG_MODAL,
                                  GTK_MESSAGE_QUESTION,
                                  GTK_BUTTONS_YES_NO,
                                  "Voulez-vous vraiment quitter ?");
  response = gtk_dialog_run(GTK_DIALOG(dialog));
  if (response == GTK_RESPONSE_YES) {
        list_free(tabList);
        gtk_main_quit();
  }
  gtk_widget_destroy(dialog);
}

void create_main_ui() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "VIMSHIT");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "delete-event", G_CALLBACK(on_window_destroy), NULL);
    tabList = list_new();

    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(G_OBJECT(settings), "gtk-application-prefer-dark-theme", TRUE, NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(vbox, TRUE);
    gtk_widget_set_vexpand(vbox, TRUE);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show(vbox);

    make_menu_bar(vbox);

    main_panel(vbox);

    gtk_widget_show_all(window);
}

void make_menu_bar(GtkWidget *vbox){

    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
    gtk_widget_show(menubar);

    GtkWidget *filemenu = gtk_menu_new();
    GtkWidget *file = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    gtk_widget_show(file);

    GtkWidget *new = gtk_menu_item_new_with_label("New");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), new);
    gtk_widget_show(new);
    g_signal_connect(new, "activate", G_CALLBACK(on_newFile_clicked), NULL);

    GtkWidget *open = gtk_menu_item_new_with_label("Open");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), open);
    gtk_widget_show(open);
    g_signal_connect(open, "activate", G_CALLBACK(on_openFile_clicked), NULL);

    GtkWidget *save = gtk_menu_item_new_with_label("Save");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
    gtk_widget_show(save);
    g_signal_connect(save, "activate", G_CALLBACK(on_saveFile_clicked), NULL);

    GtkWidget *saveas = gtk_menu_item_new_with_label("Save as");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveas);
    gtk_widget_show(saveas);
    g_signal_connect(saveas, "activate", G_CALLBACK(on_saveAsFile_clicked), NULL);

    GtkWidget *saveall = gtk_menu_item_new_with_label("Save all");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveall);
    gtk_widget_show(saveall);
    g_signal_connect(saveall, "activate", G_CALLBACK(on_saveAllFile_clicked), NULL);

    GtkWidget *closefile = gtk_menu_item_new_with_label("Close file");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), closefile);
    gtk_widget_show(closefile);
    g_signal_connect(closefile, "activate", G_CALLBACK(on_closeFile_clicked), NULL);

    GtkWidget *quit = gtk_menu_item_new_with_label("Quit");
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_widget_show(quit);
    g_signal_connect(quit, "activate", G_CALLBACK(on_quit_clicked), NULL);

    GtkWidget *editmenu = gtk_menu_new();
    GtkWidget *edit = gtk_menu_item_new_with_label("Edit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit), editmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit);
    gtk_widget_show(edit);

    GtkWidget *undo = gtk_menu_item_new_with_label("Undo");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), undo);
    gtk_widget_show(undo);
    //g_signal_connect(undo, "activate", G_CALLBACK(on_undo_clicked), NULL);

    GtkWidget *redo = gtk_menu_item_new_with_label("Redo");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), redo);
    gtk_widget_show(redo);
    //g_signal_connect(redo, "activate", G_CALLBACK(on_redo_clicked), NULL);

    GtkWidget *cut = gtk_menu_item_new_with_label("Cut");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), cut);
    gtk_widget_show(cut);
    g_signal_connect(cut, "activate", G_CALLBACK(on_cut_clicked), NULL);

    GtkWidget *copy = gtk_menu_item_new_with_label("Copy");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), copy);
    gtk_widget_show(copy);
    g_signal_connect(copy, "activate", G_CALLBACK(on_copy_clicked), NULL);

    GtkWidget *paste = gtk_menu_item_new_with_label("Paste");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), paste);
    gtk_widget_show(paste);
    g_signal_connect(paste, "activate", G_CALLBACK(on_paste_clicked), NULL);

    GtkWidget *delete = gtk_menu_item_new_with_label("Delete");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), delete);
    gtk_widget_show(delete);
    g_signal_connect(delete, "activate", G_CALLBACK(on_delete_clicked), NULL);

    GtkWidget *selectall = gtk_menu_item_new_with_label("Select all");
    gtk_menu_shell_append(GTK_MENU_SHELL(editmenu), selectall);
    gtk_widget_show(selectall);
    g_signal_connect(selectall, "activate", G_CALLBACK(on_selectAll_clicked), NULL);

    GtkWidget *helpmenu = gtk_menu_new();
    GtkWidget *help = gtk_menu_item_new_with_label("Help");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(help), helpmenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), help);
    gtk_widget_show(help);

    GtkWidget *about = gtk_menu_item_new_with_label("About");
    gtk_menu_shell_append(GTK_MENU_SHELL(helpmenu), about);
    gtk_widget_show(about);
}


void main_panel(GtkWidget *vbox){
  
  notebook = gtk_notebook_new();
  gtk_widget_set_hexpand(notebook, TRUE);
  gtk_widget_set_vexpand(notebook, TRUE);
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), TRUE);
  gtk_container_add(GTK_CONTAINER(vbox), notebook);

  gtk_widget_show(notebook);

  //createTabStruct("file1");
  
}

GtkWidget* GetCurTab(){
  return gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)));
}

GtkWidget* GetCurPage(){
  return gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook), gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook)));
}

GtkWidget* GetCurTextView(){
  return gtk_bin_get_child(GTK_BIN(gtk_bin_get_child(GTK_BIN(GetCurTab()))));
}

TabStruct* GetCurTabStruct(){
  for(list_node *node = tabList->head; node != NULL; node = node->next){
    if(((TabStruct*)node->data)->tab == GetCurTab()){
      return node->data;
    }
  }
  return NULL;
}

int AlreadyOpen(char *path){
  for(list_node *node = tabList->head; node != NULL; node = node->next){
    if(strcmp(((TabStruct*)node->data)->path, path) == 0){
      return 1;
    }
  }
  return 0;
}