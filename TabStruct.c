#include "MainUI.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabStruct.h"
#include "MenuBarFunc.h"
#include "list.h"

TabStruct *createTabStruct(char *path, char *filename)
{
    GtkWidget *tab1, *textview, *scrollbar;
    TabStruct *tabStruct = (TabStruct*)malloc(sizeof(TabStruct));
    tabStruct->path = path;
    tabStruct->filename = filename;
    tab1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(notebook), tab1);

    textview = gtk_text_view_new();
    gtk_widget_set_hexpand(textview, TRUE);
    gtk_widget_set_vexpand(textview, TRUE);
    //gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);

    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrollbar), textview);

    gtk_container_add(GTK_CONTAINER(tab1), scrollbar);

    tabStruct->tab = tab1;
    tabStruct->textview = textview;
    tabStruct->scrollbar = scrollbar;
    tabStruct->undo_stack = NULL;
    tabStruct->redo_stack = NULL;
    
    list_add(tabList,tabStruct);

    //change tab name
    GtkWidget *label = gtk_label_new(filename);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), tab1, label);

    gtk_widget_show_all(tab1);
    return tabStruct;
}

void freeTabStruct(TabStruct *tabStruct)
{
    //remove tab from notebook
    gtk_container_remove(GTK_CONTAINER(notebook), tabStruct->tab);
    //remove tab from list
    list_remove(tabList,tabStruct);
    //free tabStruct
    free(tabStruct);
}



void save_state(TabStruct* tabStruct)
{
    if (g_list_length(tabStruct->undo_stack) >= MAX_UNDO_LEVEL)
    {
        g_free(g_list_nth_data(tabStruct->undo_stack, 0));
        tabStruct->undo_stack = g_list_delete_link(tabStruct->undo_stack, g_list_first(tabStruct->undo_stack));
    }

    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(tabStruct->buffer, &start);
    gtk_text_buffer_get_end_iter(tabStruct->buffer, &end);
    tabStruct->undo_stack = g_list_append(tabStruct->undo_stack, gtk_text_buffer_get_text(tabStruct->buffer, &start, &end, FALSE));
}

void undo_text(TabStruct* tabStruct)
{
    if (g_list_length(tabStruct->undo_stack) == 0)
        return;

    if (g_list_length(tabStruct->redo_stack) >= MAX_UNDO_LEVEL)
    {
        g_free(g_list_nth_data(tabStruct->redo_stack, 0));
        tabStruct->redo_stack = g_list_delete_link(tabStruct->redo_stack, g_list_first(tabStruct->redo_stack));
    }

    tabStruct->redo_stack = g_list_append(tabStruct->redo_stack, g_strdup(g_list_nth_data(tabStruct->undo_stack, g_list_length(tabStruct->undo_stack) - 1)));
    tabStruct->undo_stack = g_list_delete_link(tabStruct->undo_stack, g_list_last(tabStruct->undo_stack));
    gtk_text_buffer_set_text(tabStruct->buffer, g_list_nth_data(tabStruct->undo_stack, g_list_length(tabStruct->undo_stack) - 1), -1);
}

void redo_text(TabStruct* tabStruct)
{
    if (g_list_length(tabStruct->redo_stack) == 0)
        return;

    tabStruct->undo_stack = g_list_append(tabStruct->undo_stack, g_strdup(g_list_nth_data(tabStruct->redo_stack, g_list_length(tabStruct->redo_stack) - 1)));
    tabStruct->redo_stack = g_list_delete_link(tabStruct->redo_stack, g_list_last(tabStruct->redo_stack));
    gtk_text_buffer_set_text(tabStruct->buffer, g_list_nth_data(tabStruct->undo_stack, g_list_length(tabStruct->undo_stack) - 1), -1);
}

/*gboolean key_press_cb(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if ((event->state & GDK_CONTROL_MASK) && event->keyval == 'z')
    {
        if (event->state & GDK_SHIFT_MASK)
            redo_text();
        else
            undo_text();

        return TRUE;
    }

    save_state();
    return FALSE;
}*/
