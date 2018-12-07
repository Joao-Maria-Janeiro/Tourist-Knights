#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  FILE * fp;
  fp = fopen(argv[1], "r");
  if(fp == NULL) {
    printf("Error opening file\n");
    exit(0);
  }

  int lines=0, columns=0, numPoints=0, cost = 0, steps = 0, calculatedValue = 0, aux = 0;
  char objective = '0';

  while(fscanf(fp, "%d %d %c %d %d %d", &lines, &columns, &objective, &numPoints, &cost, &steps) == 6){
    if(cost != -1){
      for(int i = 0; i < steps; i++){
        fscanf(fp, "%d %d %d", &lines, &columns, &aux);
        calculatedValue += aux;
      }

      if(calculatedValue == cost){
        printf("The points sum equals to the header cost value\n");
      }else {
	printf("Values dont match\n");
      }
      cost = 0;
      calculatedValue = 0;
    }
  }

return 0;
}
