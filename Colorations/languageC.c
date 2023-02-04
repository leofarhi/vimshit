#include "languageC.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TabStruct.h"


//set tag color for the textview (red, blue, green, black) with Hexadecimal color
void setTagColorC(TabStruct *tabStruct)
{
    GtkTextBuffer *buffer = tabStruct->buffer;
    GtkTextTag *tag;
    tag = gtk_text_buffer_create_tag(buffer, "red", "foreground", "#FF0000", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "blue", "foreground", "#0000FF", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "green", "foreground", "#00FF00", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "black", "foreground", "#000000", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "white", "foreground", "#FFFFFF", NULL);
    //default color is white
    tag = gtk_text_buffer_create_tag(buffer, "default", "foreground", "#FFFFFF", NULL);
}

//change color of word "void" to red else default color
//check all occurence of "void" and change the color
void colorizeC(TabStruct *tabStruct){
    return; //TODO: fix this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    GtkTextBuffer *buffer = tabStruct->buffer;
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    for(int i = 0; i < c_Word_blue_size; i++){
        char *word = c_Word_blue[i];
        char *pos = text;
        while ((pos = strstr(pos, word)) != NULL)
        {
            gtk_text_buffer_get_iter_at_offset(buffer, &start, pos - text);
            gtk_text_buffer_get_iter_at_offset(buffer, &end, pos - text + strlen(word));
            gtk_text_buffer_apply_tag_by_name(buffer, "blue", &start, &end);
            pos += strlen(word);
        }
    }

    for(int i = 0; i < c_Word_purple_size; i++){
        char *word = c_Word_purple[i];
        char *pos = text;
        while ((pos = strstr(pos, word)) != NULL)
        {
            gtk_text_buffer_get_iter_at_offset(buffer, &start, pos - text);
            gtk_text_buffer_get_iter_at_offset(buffer, &end, pos - text + strlen(word));
            gtk_text_buffer_apply_tag_by_name(buffer, "red", &start, &end);
            pos += strlen(word);
        }
    }
}