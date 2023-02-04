#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MainUI.h"
#include "TabStruct.h"

int main(int argc, char *argv[]) {

  gtk_init(&argc, &argv);

  create_main_ui();

  for (int i = 1; i < argc; i++) {
    //get absolute path of file passed in as argument, if not already absolute
    //if file does not exist, create it
    char *AbsPath = realpath(argv[i], NULL);
    if (AbsPath == NULL) {
      printf("File does not exist, creating file %s\n", argv[i]);
      AbsPath = argv[i];
      FILE *fp = fopen(AbsPath, "w");
      fclose(fp);
    }
    char *filename = g_path_get_basename(AbsPath);
    TabStruct * tab = open_file(NULL, AbsPath, filename);
  }

  gtk_main();

  return 0;
}