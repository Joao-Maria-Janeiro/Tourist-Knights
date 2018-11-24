#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void checkExtension(char *, int);


int main(int argc, char *argv[]) {
  checkExtension(argv[1], argc);
  readFromFile(argv[1]);
  return 0;
}


void checkExtension(char * file_name, int argc) {
  if(argc == 1){
    printf("You must provide a input file\n");
    exit(1);
  }
  if(strstr(file_name, "cities") == 0) {
    printf("Wrong file extension");
    exit(1);
  }
}
