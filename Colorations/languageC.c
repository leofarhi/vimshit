#include "languageC.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TabStruct.h"
#include <regex.h>
#include "../list.h"

list* ColorationListC = NULL;

list* AllWordsC(){
    list* l = list_new();
    Coloration* c;
    char* c_Word_blue[] = { "int", "double", "char", "float", "void", "short", "long", "unsigned", "signed", "struct", "union", "enum", "typedef", "static", "extern", "auto", "register", "const", "volatile", "inline", "restrict" };
    char* c_Word_pink[] = { "NULL","if", "elif", "else", "#endif", "error", "line", "#defined", "switch", "case", "default", "break", "continue", "goto", "return", "sizeof", "alignof", "alignas", "while", "do", "for", "goto", "asm", "typeof", "_Alignof", "_Alignas", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};
    for(int i = 0; i < 21; i++){
        c = malloc(sizeof(Coloration));
        //add \\b before and after the word to match only the word
        char* word = malloc(strlen(c_Word_blue[i]) + 3);
        strcpy(word, "\\b");
        strcat(word, c_Word_blue[i]);
        strcat(word, "\\b");
        c->regex_word = word;
        c->color = "blue";
        list_add(l, c);
    }

    //special case for #include <...>
    c = malloc(sizeof(Coloration));
    c->regex_word = "#include\\s+(<[^>]*>)";
    c->color = "orange";
    list_add(l, c);

    //special case for #include "..."
    c = malloc(sizeof(Coloration));
    c->regex_word = "#include\\s+(\"[^\"]*\")";
    c->color = "orange";
    list_add(l, c);

    //special case for #define and #undef and #ifdef and #ifndef and #if and #else and #elif and #endif
    c = malloc(sizeof(Coloration));
    c->regex_word = "#(define|undef|ifdef|ifndef|if|else|elif|endif)\\s+([a-zA-Z0-9_]+)";
    c->color = "blue";
    list_add(l, c);

    //special case for #error and #pragma and #line
    c = malloc(sizeof(Coloration));
    c->regex_word = "#(error|pragma|line)\\s+([a-zA-Z0-9_]+)";
    c->color = "blue";
    list_add(l, c);

    //add # to the regex
    c = malloc(sizeof(Coloration));
    c->regex_word = "#[a-zA-Z0-9_]*";
    c->color = "pink";
    list_add(l, c);
    for(int i = 0; i < 34; i++){
        c = malloc(sizeof(Coloration));
        //add \\b before and after the word to match only the word
        char* word = malloc(strlen(c_Word_pink[i]) + 3);
        strcpy(word, "\\b");
        strcat(word, c_Word_pink[i]);
        strcat(word, "\\b");
        c->regex_word = word;
        c->color = "pink";
        list_add(l, c);
    }

    //color for : struct|union|enum <name>
    c = malloc(sizeof(Coloration));
    c->regex_word = "(struct|union|enum)\\s+([a-zA-Z0-9_]+)";
    c->color = "lightgreen";
    list_add(l, c);
    //color for : } <name>;
    c = malloc(sizeof(Coloration));
    c->regex_word = "\\}\\s+([a-zA-Z0-9_]+);";
    c->color = "lightgreen";
    list_add(l, c);

    //color for : <name>(
    c = malloc(sizeof(Coloration));
    c->regex_word = "([a-zA-Z0-9_]+)\\(";
    c->color = "yellow";
    list_add(l, c);
    //color for : )
    c = malloc(sizeof(Coloration));
    c->regex_word = "\\)";
    c->color = "yellow";
    list_add(l, c);

    //add regex for string
    c = malloc(sizeof(Coloration));
    c->regex_word = "\"[^\"]*\"";
    c->color = "orange";
    list_add(l, c);
    //add regex for char
    c = malloc(sizeof(Coloration));
    c->regex_word = "\'.\'";
    c->color = "orange";
    list_add(l, c);
    //add regex for numbers
    c = malloc(sizeof(Coloration));
    c->regex_word = "\\b[0-9]+\\b";
    c->color = "pink";
    list_add(l, c);

    //add regex for comments
    c = malloc(sizeof(Coloration));
    c->regex_word = "//[^\n]*";
    c->color = "green";
    list_add(l, c);
    c = malloc(sizeof(Coloration));
    c->regex_word = "/\\*([^*]|\\*[^/])*\\*/";
    c->color = "green";
    list_add(l, c);
    
    return l;

}


//set tag color for the textview (red, blue, green, black) with Hexadecimal color
void setTagColorC(TabStruct *tabStruct)
{
    GtkTextBuffer *buffer = tabStruct->buffer;
    GtkTextTag *tag;
    tag = gtk_text_buffer_create_tag(buffer, "red", "foreground", "#FF0000", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "lightblue", "foreground", "#60BEFE", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "lightgreen", "foreground", "#4EC9B0", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "yellow", "foreground", "#DCC471", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "blue", "foreground", "#337CD6", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "orange", "foreground", "#CE7B50", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "pink", "foreground", "#CE70CA", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "green", "foreground", "#6A9951", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "black", "foreground", "#000000", NULL);
    tag = gtk_text_buffer_create_tag(buffer, "white", "foreground", "#FFFFFF", NULL);
    //default color is white
    tag = gtk_text_buffer_create_tag(buffer, "default", "foreground", "#FFFFFF", NULL);

    if (ColorationListC == NULL)
    {
        ColorationListC = AllWordsC();
    }
}

//change color of word "void" to red else default color
//check all occurence of "void" and change the color
void colorizeC(TabStruct *tabStruct){
    //return; //TODO: fix this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    GtkTextBuffer *buffer = tabStruct->buffer;
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    //remove all tags
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);

    for(int i = 0; i < ColorationListC->size; i++){
        Coloration* c = (Coloration*)list_get(ColorationListC, i);
        regex_t regex;
        char *pos = text;
        if (regcomp(&regex, c->regex_word, REG_EXTENDED) != 0)
        {
            printf("Error compiling regex\n");
            return;
        }
        while (regexec(&regex, pos, 0, NULL, 0) == 0)
        {
            regmatch_t matchptr[1];
            regexec(&regex, pos, 1, matchptr, 0);
            int st = matchptr[0].rm_so;
            int ed = matchptr[0].rm_eo;
            //printf("start: %d, end: %d, word: %s\n", start, end, c->regex_word);
            gtk_text_buffer_get_iter_at_offset(buffer, &start, st + (pos - text));
            gtk_text_buffer_get_iter_at_offset(buffer, &end, ed + (pos - text));
            gtk_text_buffer_apply_tag_by_name(buffer, c->color, &start, &end);
            pos += ed;
        }
        regfree(&regex);
    }
}

/*
void colorizeC(TabStruct *tabStruct){
    //return; //TODO: fix this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    GtkTextBuffer *buffer = tabStruct->buffer;
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    //remove all tags
    gtk_text_buffer_remove_all_tags(buffer, &start, &end);

    for(int i = 0; i < ColorationListC->size; i++){
        Coloration* c = (Coloration*)list_get(ColorationListC, i);
        char *word = c->regex_word;
        char *pos = text;
        while ((pos = strstr(pos, word)) != NULL)
        {
            gtk_text_buffer_get_iter_at_offset(buffer, &start, pos - text);
            gtk_text_buffer_get_iter_at_offset(buffer, &end, pos - text + strlen(word));
            gtk_text_buffer_apply_tag_by_name(buffer, c->color, &start, &end);
            pos += strlen(word);
        }
    }
}
*/