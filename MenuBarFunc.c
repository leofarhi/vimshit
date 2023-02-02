#include "MainUI.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabStruct.h"
#include "MenuBarFunc.h"

const char* getFileNameFromPath(const char* path)
    {
        if(path != NULL)
        {
            for(size_t i = strlen(path);  i > 0; --i)
            {
                if (path[i-1] == '/')
                {
                    return &path[i];
                }
            }
        }
    
        return path;
    }

//button New
void on_newFile_clicked(GtkWidget *widget, gpointer data){
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	gtk_file_chooser_set_filename(chooser, "newfile.txt");
	//set last directory to current directory
    gtk_file_chooser_set_current_folder(chooser, g_get_current_dir());
    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT){
        char *AbsPath;
        char *filename;
        AbsPath = gtk_file_chooser_get_filename(chooser);
        filename = g_path_get_basename(AbsPath);//gtk_file_chooser_get_current_name(chooser);
        //printf("File selected: %s\n", filename);
        //printf("File selected: %s\n", AbsPath);
        //printf("File selected: %s\n", g_get_current_dir());
        //printf("File selected: %s\n", g_get_home_dir());
        TabStruct * tab = createTabStruct(AbsPath, filename);
        FILE *fp = fopen(AbsPath, "w");
        fclose(fp);
    }
    gtk_widget_destroy(dialog);
}

void on_openFile_clicked(GtkWidget *widget, gpointer data){
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
	gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT){
        char *AbsPath;
        char *filename;
        GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
        AbsPath = gtk_file_chooser_get_filename(chooser);
        if (AlreadyOpen(AbsPath)) {
            g_free(AbsPath);
            gtk_widget_destroy(dialog);
            return;
        }
        filename = g_path_get_basename(AbsPath);
        //printf("File selected: %s\n", filename);
        //printf("File selected: %s\n", AbsPath);
        //printf("File selected: %s\n", g_get_current_dir());
        //printf("File selected: %s\n", g_get_home_dir());
        TabStruct * tab = createTabStruct(AbsPath, filename);
        FILE *fp = fopen(AbsPath, "r");
        if(fp == NULL){
            printf("Error opening file\n");
            return;
        }
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
        while ((read = getline(&line, &len, fp)) != -1) {
            gtk_text_buffer_insert_at_cursor(buffer, line, -1);
        }
        fclose(fp);
        if (line)
            free(line);
    }
    gtk_widget_destroy(dialog);
}

void on_saveFile_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    FILE *fp = fopen(tab->path, "w");
    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    fprintf(fp, "%s", text);
    fclose(fp);
}

void on_saveAsFile_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkWidget* dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
    gtk_file_chooser_set_filename(chooser, "newfile.txt");
    //set last directory to current directory
    gtk_file_chooser_set_current_folder(chooser, g_get_current_dir());
    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT){
        char *AbsPath;
        char *filename;
        AbsPath = gtk_file_chooser_get_filename(chooser);
        filename = g_path_get_basename(AbsPath);//gtk_file_chooser_get_current_name(chooser);
        //printf("File selected: %s\n", filename);
        //printf("File selected: %s\n", AbsPath);
        //printf("File selected: %s\n", g_get_current_dir());
        //printf("File selected: %s\n", g_get_home_dir());
        //TabStruct * tab = GetCurTabStruct();
        FILE *fp = fopen(AbsPath, "w");
        if(fp == NULL){
            printf("Error opening file\n");
            return;
        }
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(buffer, &start);
        gtk_text_buffer_get_end_iter(buffer, &end);
        char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        fprintf(fp, "%s", text);
        fclose(fp);
    }
    gtk_widget_destroy(dialog);
}

void on_saveAllFile_clicked(GtkWidget *widget, gpointer data){
    for(list_node *node = tabList->head; node != NULL; node = node->next){
        TabStruct * tab = (TabStruct *)node->data;
        FILE *fp = fopen(tab->path, "w");
        if(fp == NULL){
            printf("Error opening file\n");
            return;
        }
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
        GtkTextIter start, end;
        gtk_text_buffer_get_start_iter(buffer, &start);
        gtk_text_buffer_get_end_iter(buffer, &end);
        char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        fprintf(fp, "%s", text);
        fclose(fp);
    }
}

void on_closeFile_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    freeTabStruct(tab);
}

void on_quit_clicked(GtkWidget *widget, gpointer data){
    on_window_destroy(window, NULL);
}

/*void on_undo_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    gtk_text_buffer_undo(buffer);
}

void on_redo_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    gtk_text_buffer_redo(buffer);
}*/

void on_cut_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    gtk_text_buffer_cut_clipboard(buffer, gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), TRUE);
}

void on_copy_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    gtk_text_buffer_copy_clipboard(buffer, gtk_clipboard_get(GDK_SELECTION_CLIPBOARD));
}

void on_paste_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    gtk_text_buffer_paste_clipboard(buffer, gtk_clipboard_get(GDK_SELECTION_CLIPBOARD), NULL, TRUE);
}

void on_delete_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_selection_bounds(buffer, &start, &end);
    gtk_text_buffer_delete(buffer, &start, &end);
}

void on_selectAll_clicked(GtkWidget *widget, gpointer data){
    TabStruct * tab = GetCurTabStruct();
    if (tab == NULL) return;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tab->textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_select_range(buffer, &start, &end);
}