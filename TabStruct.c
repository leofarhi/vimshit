#include "MainUI.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabStruct.h"
#include "MenuBarFunc.h"
#include "list.h"

#include "Colorations/languageC.h"

char* GetExtension(char* filename)
{
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void DefaultSetTagColor(TabStruct *tabStruct)
{
    
}

void DefaultColorize(TabStruct *tabStruct)
{
    
}

void SetColoration(TabStruct *tabStruct)
{
    char *extension = GetExtension(tabStruct->filename);
    if (strcmp(extension, "c") == 0 || strcmp(extension, "h") == 0)
    {
        tabStruct->setTagColor = setTagColorC;
        tabStruct->colorize = colorizeC;
    }
    else
    {
        tabStruct->setTagColor = DefaultSetTagColor;
        tabStruct->colorize = DefaultColorize;
    }
}

void update_line_number(GtkTextBuffer *buffer, GtkLabel *line_number) {
    int line_count = gtk_text_buffer_get_line_count(buffer);
    //set the text of the label a number of line followed by a new line and the same number
    /*gchar *text = g_strdup_printf("%d\n%d", line_count, line_count);
    gtk_label_set_text(line_number, text);
    g_free(text);*/
    //mettre 1 puis 2 puis 3 dans gchar *text et le realloc a chaque fois
    gchar *text = (gchar*)malloc(1);
    text[0] = '\0';
    for (int i = 1; i <= line_count; i++)
    {
        char *tmp = (char*)malloc(10);
        sprintf(tmp, "%d\n", i);
        text = (gchar*)realloc(text, strlen(text) + strlen(tmp) + 1);
        strcat(text, tmp);
        free(tmp);
    }
    gtk_label_set_text(line_number, text);
    free(text);
}

TabStruct *createTabStruct(char *path, char *filename)
{
    GtkWidget *tab1, *textview, *scrollbar;
    TabStruct *tabStruct = (TabStruct*)malloc(sizeof(TabStruct));
    tabStruct->path = path;
    tabStruct->filename = filename;
    tab1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(notebook), tab1);

    /*textview = gtk_text_view_new();
    gtk_widget_set_hexpand(textview, TRUE);
    gtk_widget_set_vexpand(textview, TRUE);
    //gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD);

    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrollbar), textview);

    gtk_container_add(GTK_CONTAINER(tab1), scrollbar);*/

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
    textview = gtk_text_view_new_with_buffer(buffer);
    gtk_widget_set_hexpand(textview, TRUE);
    gtk_widget_set_vexpand(textview, TRUE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_NONE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), TRUE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview), TRUE);
    g_object_set(textview, "margin", 10, NULL);  // Set the margin

    GtkAdjustment *adj = gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(textview));

    GtkWidget *line_number = gtk_label_new("1");
    gtk_grid_attach(GTK_GRID(grid), line_number, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), textview, 1, 0, 1, 1);
    //label on the top left corner
    gtk_widget_set_halign(line_number, GTK_ALIGN_START);
    gtk_widget_set_valign(line_number, GTK_ALIGN_START);
    //set spacing vertically label with height of the textview
    gtk_widget_set_margin_top(line_number, 10);
    gtk_widget_set_margin_bottom(line_number, 10);
    //set spacing horizontally label with width of the textview
    gtk_widget_set_margin_start(line_number, 10);
    gtk_widget_set_margin_end(line_number, 10);


    g_signal_connect(adj, "value-changed", G_CALLBACK(update_line_number), line_number);

    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrollbar), grid);
    gtk_container_add(GTK_CONTAINER(tab1), scrollbar);

    g_signal_connect(buffer, "changed", G_CALLBACK(update_line_number), line_number);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    tabStruct->tab = tab1;
    tabStruct->textview = textview;
    tabStruct->scrollbar = scrollbar;
    tabStruct->undo_stack = NULL;
    tabStruct->redo_stack = NULL;
    tabStruct->HasChanged = 0;

    //change size of letters in textview
    PangoFontDescription *font_desc = pango_font_description_new();
    pango_font_description_set_size(font_desc, 12 * PANGO_SCALE);
    gtk_widget_override_font(textview, font_desc);
    //set line number font at same size
    gtk_widget_override_font(line_number, font_desc);
    pango_font_description_free(font_desc);
    //center le texte de line_number
    gtk_label_set_justify(GTK_LABEL(line_number), GTK_JUSTIFY_CENTER);
    
    list_add(tabList,tabStruct);

    //change tab name
    GtkWidget *label = gtk_label_new(filename);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), tab1, label);

    addKeyBinding(tabStruct);
    SetColoration(tabStruct);
    tabStruct->setTagColor(tabStruct);

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

TabStruct * open_file(TabStruct *tab, char *AbsPath, char *filename)
{
    if (tab == NULL)
        tab = createTabStruct(AbsPath, filename);
    FILE *fp = fopen(AbsPath, "r");
    if(fp == NULL){
        printf("Error opening file\n");
        return NULL;
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
    clear_undo_redo(tab);
    save_state(tab);
    tab->colorize(tab);
    return tab;
}

void save_file(TabStruct *tab)
{
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
    tab->HasChanged = 0;
    g_free(text);
    //change tab name
    GtkWidget *label = gtk_label_new(tab->filename);
    gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), tab->tab, label);
    tab->colorize(tab);
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
    char *text = g_list_nth_data(tabStruct->undo_stack, g_list_length(tabStruct->undo_stack) - 1);
    if (text != NULL)
        gtk_text_buffer_set_text(tabStruct->buffer, (const char*)text, -1);
}

void redo_text(TabStruct* tabStruct)
{
    if (g_list_length(tabStruct->redo_stack) == 0)
        return;

    tabStruct->undo_stack = g_list_append(tabStruct->undo_stack, g_strdup(g_list_nth_data(tabStruct->redo_stack, g_list_length(tabStruct->redo_stack) - 1)));
    tabStruct->redo_stack = g_list_delete_link(tabStruct->redo_stack, g_list_last(tabStruct->redo_stack));
    gtk_text_buffer_set_text(tabStruct->buffer, g_list_nth_data(tabStruct->undo_stack, g_list_length(tabStruct->undo_stack) - 1), -1);
}

void clear_undo_redo(TabStruct* tabStruct)
{
    g_list_free_full(tabStruct->undo_stack, g_free);
    g_list_free_full(tabStruct->redo_stack, g_free);
    tabStruct->undo_stack = NULL;
    tabStruct->redo_stack = NULL;
}

//add tab function
//if a part of the file is selected, and the user press tab, the selected part will be indented
//if the user press tab and nothing is selected, the cursor will be indented
void addTab(TabStruct *tabStruct)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tabStruct->textview));
    GtkTextIter start, end;
    if (gtk_text_buffer_get_selection_bounds(buffer, &start, &end))
    {
        //get start foreache line and indent (start selection is not always at the beginning of a line)
        int NumbeOfLine = gtk_text_iter_get_line(&end) - gtk_text_iter_get_line(&start);
        do
        {
            //get start of line
            gtk_text_iter_set_line_offset(&start, 0);
            //indent
            gtk_text_buffer_insert(buffer, &start, "\t", 1);
            //next line
            gtk_text_iter_forward_line(&start);
            NumbeOfLine--;
        } while (NumbeOfLine >= 0);
    }
    else
    {
        gtk_text_buffer_insert_at_cursor(buffer, "\t", 1);
    }
}

//if a part of the file is selected, and the user press {, the selected part will be indented and { will be added at the beginning of each line
//and } will be added at the end of the selection
//if the user press { and nothing is selected, the cursor add {
void addBrace(TabStruct *tabStruct)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tabStruct->textview));
    GtkTextIter start, end;
    if (gtk_text_buffer_get_selection_bounds(buffer, &start, &end))
    {
        //get start foreache line and indent (start selection is not always at the beginning of a line)
        int NumbeOfLine = gtk_text_iter_get_line(&end) - gtk_text_iter_get_line(&start);

        //distance is a distance between the start of the selection and the start of the line
        int distance = gtk_text_iter_get_line_offset(&start);
        //add } at the end of the selection
        gtk_text_buffer_insert(buffer, &start, "{", 1);
        gtk_text_buffer_insert(buffer, &start, "\n", 1);
        for (int i = 0; i < distance; i++)
        {
            gtk_text_buffer_insert(buffer, &start, "\t", 1);
        }
        do
        {
            //get start of line
            gtk_text_iter_set_line_offset(&start, 0);
            //indent
            gtk_text_buffer_insert(buffer, &start, "\t", 1);
            //next line
            gtk_text_iter_forward_line(&start);
            NumbeOfLine--;
        } while (NumbeOfLine >= 0);
        //add } at the end of the selection
        gtk_text_buffer_insert(buffer, &start, "\n", 1);
        for (int i = 0; i < distance; i++)
        {
            gtk_text_buffer_insert(buffer, &start, "\t", 1);
        }
        gtk_text_buffer_insert(buffer, &start, "}", 1);
        gtk_text_buffer_insert(buffer, &start, "\n", 1);
    }
    else
    {
        gtk_text_buffer_insert_at_cursor(buffer, "{", 1);
    }
}

//remove tab function
//if the user press ctrl+tab, remove the tab at the start of the line where the cursor is
void removeTab(TabStruct *tabStruct)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tabStruct->textview));
    GtkTextIter start, end;
    if (gtk_text_buffer_get_selection_bounds(buffer, &start, &end))
    {
        //get start foreache line and indent (start selection is not always at the beginning of a line)
        int NumbeOfLine = gtk_text_iter_get_line(&end) - gtk_text_iter_get_line(&start);
        do
        {
            //get start of line
            gtk_text_iter_set_line_offset(&start, 0);
            //check if the line start with a tab
            if (gtk_text_iter_get_char(&start) == '\t')
            {
                //remove first char of the line
                //set end at the start + 1
                GtkTextIter next = start;
                gtk_text_iter_forward_chars(&next, 1);
                //remove the char
                gtk_text_buffer_delete(buffer, &start, &next);
            }
            //next line
            gtk_text_iter_forward_line(&start);
            NumbeOfLine--;
        } while (NumbeOfLine >= 0);
    }
    else
    {
        gtk_text_buffer_get_iter_at_mark(buffer, &start, gtk_text_buffer_get_insert(buffer));
        gtk_text_iter_set_line_offset(&start, 0);
        gtk_text_buffer_get_iter_at_mark(buffer, &end, gtk_text_buffer_get_insert(buffer));
        gtk_text_iter_forward_chars(&end, 1);
        if (gtk_text_iter_get_char(&start) == '\t')
        {
            gtk_text_buffer_delete(buffer, &start, &end);
        }
    }
}

//if the user press enter, the line will be indented
void addNewLine(TabStruct *tabStruct)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tabStruct->textview));
    GtkTextIter start, end;
    if (gtk_text_buffer_get_selection_bounds(buffer, &start, &end)){
        //remove the selection and add a new line
        gtk_text_buffer_delete(buffer, &start, &end);
        gtk_text_buffer_insert_at_cursor(buffer, "\n", 1);
    }
    else
    {
        //dist is the number of tab at the start of the line
        int dist = 0;
        gtk_text_buffer_get_iter_at_mark(buffer, &start, gtk_text_buffer_get_insert(buffer));
        gtk_text_buffer_get_iter_at_mark(buffer, &end, gtk_text_buffer_get_insert(buffer));
        gtk_text_iter_set_line_offset(&start, 0);
        while (gtk_text_iter_get_char(&start) == '\t')
        {
            gtk_text_iter_forward_chars(&start, 1);
            dist++;
        }
        gtk_text_buffer_insert_at_cursor(buffer, "\n", 1);
        for (int i = 0; i < dist; i++)
        {
            gtk_text_buffer_insert_at_cursor(buffer, "\t", 1);
        }
    }
}

char* get_text(TabStruct *tabStruct)
{
    //get text of textview
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tabStruct->textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    return text;
}


gboolean key_press_cb(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    TabStruct *tabStruct = (TabStruct*)user_data;
    //if key is only special key but not change the text return false
    if (event->keyval == GDK_KEY_Control_L || event->keyval == GDK_KEY_Control_R || event->keyval == GDK_KEY_Shift_L || event->keyval == GDK_KEY_Shift_R || event->keyval == GDK_KEY_Alt_L || event->keyval == GDK_KEY_Alt_R)
    {
        return FALSE;
    }
    if (!tabStruct->HasChanged){
        tabStruct->HasChanged = 1;
        //change tab name
        char *name = malloc(strlen(tabStruct->filename) + 2);
        strcpy(name, tabStruct->filename);
        strcat(name, "*");
        GtkWidget *label = gtk_label_new(name);
        gtk_notebook_set_tab_label(GTK_NOTEBOOK(notebook), tabStruct->tab, label);
        free(name);
    }
    if (event->state & GDK_CONTROL_MASK)
    {
        switch (event->keyval)
        {
        case GDK_KEY_s:
            save_file(tabStruct);
            return TRUE;
        case GDK_KEY_z:
            undo_text(tabStruct);
            return TRUE;
        case GDK_KEY_y:
            redo_text(tabStruct);
            return TRUE;
        case GDK_KEY_Tab:
            removeTab(tabStruct);
            return TRUE;
        case GDK_KEY_w:
            freeTabStruct(tabStruct);
            return TRUE;
        }
    }
    //printf("event->keyval = %d\n", event->keyval);
    switch (event->keyval)
    {
    case GDK_KEY_Tab:
        addTab(tabStruct);
        return TRUE;
    case GDK_KEY_braceleft:
        addBrace(tabStruct);
        return TRUE;
    case GDK_KEY_braceright:
        addBrace(tabStruct);
        return TRUE;
    case GDK_KEY_Return:
        addNewLine(tabStruct);
        return TRUE;
    }

    tabStruct->colorize(tabStruct);

    //////////////////////////
    save_state(tabStruct);
    return FALSE;

}


void addKeyBinding(TabStruct *tabStruct)
{
    tabStruct->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tabStruct->textview));
    g_signal_connect(tabStruct->textview, "key-press-event", G_CALLBACK(key_press_cb), tabStruct);
}