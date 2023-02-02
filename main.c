#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MainUI.h"

int main(int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  create_main_ui();

  gtk_main();

  return 0;
}