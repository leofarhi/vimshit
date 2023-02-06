#ifndef COLORATION_LANGUAGE_C_H
#define COLORATION_LANGUAGE_C_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../TabStruct.h"
#include <regex.h>
#include "../list.h"

void setTagColorC(TabStruct *tabStruct);
void colorizeC(TabStruct *tabStruct);

typedef struct Coloration
{
    char *color;//tag name
    char *regex_word;
} Coloration;

extern list* ColorationListC;

list* AllWordsC();


#endif