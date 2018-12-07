#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "data.h"
#include "heap.h"

#define INFINIY 2147483647


void readFromFile(char * file_name) {
  int count = 0;
  Point * toPrint = NULL;
  //create necessary variables
  int lines=0, columns=0, numPoints=0, validMap = 0, i = 0, j = 0, lixinho = 0, numLines = 0;
  char objective = '0';
  Map * map = NULL;
  //read all the map info
  FILE * fp;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    exit(0);
  }


  char *outfile_name=(char*)calloc(1, (strlen(file_name))*sizeof(char));
  if(outfile_name == NULL){
    exit(0);
  }
  int len = strlen(file_name) - strlen(".cities");
  strncpy(outfile_name, file_name, len);
  strcat(outfile_name, ".walks");


  FILE *fout = fopen(outfile_name, "w");
  if(fout == NULL){
    exit(0);
  }

  while(fscanf(fp, "%d %d %c %d ", &lines, &columns, &objective, &numPoints) == 4){
    //verify if it's a valid map
    validMap=0;
    if(verifyMap(lines, columns, objective, numPoints) == 0){
      //We verify if the map is valid and, if so, assing 0 to validMap
      validMap = -1;
      fprintf(fout, "%d %d %c %d %d %d\n", lines, columns, objective, numPoints, -1, 0);
      fprintf(fout, "\n");
    }
    //read all points
    if(validMap != -1){
      map = (Map*)malloc(sizeof(Map));
      allocatePoints(map, lines, columns, objective, numPoints);
      for(i = 0; i < numPoints; i++){
        lixinho = fscanf(fp, "%d %d", &map->points[i].x, &map->points[i].y);
      }

      //If it's type A we check if it can be done with only one horse jump
      //check if point can be accessed in a horse jump and if so only read the necessary lines
        if(map->objective == 'A' && (horseJump(map->points[0], map->points[1]) == 1)){
          if(map->points[0].x > map->points[1].x){
            numLines = map->points[0].x + 1;
          }else{
            numLines = map->points[1].x + 1;
          }
          allocateMap(map, numLines, columns);

          //Read necessary lines for cost calcuations
          for(i = 0; i < numLines; i++){
            for(j = 0; j < columns; j++){
              lixinho = fscanf(fp, "%d ", &map->map[i][j]);
            }
          }
          //Move the pointer to the end of the map
          for(int i=numLines; i<lines; i++) {
            for(int x=0; x<columns; x++) {
              lixinho = fscanf(fp, "%d ", &lixinho);
            }
          }
          fprintf(fout, "%d %d %c %d %d %d\n", lines, columns, objective, numPoints, map->map[map->points[1].x][map->points[1].y], 1);
          fprintf(fout, "%d %d %d\n", map->points[1].x, map->points[1].y, map->map[map->points[1].x][map->points[1].y]);
          freeMap(map, numLines);
        }else{
          allocateMap(map, lines, columns);
          numLines = lines;
          //Alocação para a matriz st (de pontos, para o caminho)
          Point *st = (Point*)malloc(sizeof(Point)*(lines * columns));
          //Alocação para a matriz wt (de custos)
          int *wt = (int*)malloc(sizeof(int)*(lines * columns));
          Point empty;
          empty.x = -1;
          empty.y = -1;
          //Else read all the lines
          for(i = 0; i < lines; i++){
            // st[i] = (Point*)malloc(sizeof(Point)*columns);
            // wt[i] = (int*)malloc(sizeof(int)*columns);
            for(j = 0; j < columns; j++){
              wt[i*columns + j] = INFINIY;
              st[i*columns + j] = empty;
              lixinho = fscanf(fp, "%d ", &map->map[i][j]);
            }
          }
          //select the correct read function for the current objective
          switch (map->objective){
            case 'A':
              if(verifyPoints(map, numPoints)) {
                toPrint = djikstraTypeA(map, map->points[0], map->points[1], st, wt, fout, &count);
                if(toPrint != NULL){
                  fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, wt[(map->points[1].x *map->columns) + map->points[1].y], count);
                  for(int i=count -1; i>=0; i--) {
                    fprintf(fout, "%d %d %d\n", toPrint[i].x, toPrint[i].y, map->map[toPrint[i].x][toPrint[i].y]); //Print the path
                  }
                  free(toPrint);
                }
              }else {
                fprintf(fout, "%d %d %c %d %d %d\n", lines, columns, objective, numPoints, -1, 0);
              }
              free(st);
              free(wt);
              freeMap(map, map->lines);
            break;
            case 'B':
              if(verifyPoints(map, numPoints)) {
                djikstraTypeB(map, st, wt, fout, &lixinho, 1);
              }else {
                fprintf(fout, "%d %d %c %d %d %d\n", lines, columns, objective, numPoints, -1, 0);
              }
              free(st);
              free(wt);
              freeMap(map, map->lines);
            break;
            case 'C':
              if(verifyPoints(map, numPoints)) {
                djikstraTypeC(map, st, wt, fout);
              }else {
                fprintf(fout, "%d %d %c %d %d %d\n", lines, columns, objective, numPoints, -1, 0);
              }
              free(st);
              free(wt);
              freeMap(map, map->lines);
            break;
          }
        }
      fprintf(fout, "\n");
    }else{
      //Move the pointer to the end of the map
      for(int i=0; i<numPoints*2; i++) {
        lixinho = fscanf(fp, "%d ", &lixinho);
      }
      for(int i=0; i<lines; i++) {
        for(int x=0; x<columns; x++) {
          lixinho = fscanf(fp, "%d ", &lixinho);
        }
      }
    }
  }

free(outfile_name);
fclose(fp);
fclose(fout);
}

void freeMap(Map* map, int lines) {
  free(map->points);
  for(int i=0; i<lines; i++) {
    free(map->map[i]);
  }
  free(map->map);
  free(map);
}

/*Se algum dos pontos a percorrer é igual a 0, mapa invalido
*/
int verifyPoints(Map *map, int numPoints) {
  for(int i=0; i<numPoints; i++) {
    if(map->points[i].x < 0 || map->points[i].y < 0 || map->points[i].y >= map->columns || map->points[i].x >= map->lines) {
      return 0;
    }
    if(map->map[map->points[i].x][map->points[i].y] == 0) {
      return 0;
    }
  }
  return 1;
}

int verifyMap(int lines, int columns, char objective, int numPoints) {
  if(objective != 'A'  && objective != 'B' && objective != 'C'){
    return 0;
  }
  if(objective == 'A' && numPoints != 2) {
    return 0;
  }
  if((objective == 'B' || objective == 'C') && numPoints < 2){
    return 0;
  }
  return 1;
}

void allocatePoints(Map * newMap, int lines, int columns, char objective, int numPoints){
  newMap->numPoints = numPoints;
  newMap->lines = lines;
  newMap->columns = columns;
  newMap->objective = objective;
  //Memory alocation for Points
  newMap->points =(Point*)malloc(newMap->numPoints * sizeof(Point));
  if(newMap->points == NULL){
    printf("No memmory for points allocation\n");
  }
}

void allocateMap(Map * map, int numLines, int numColumns) {
  map->map = (int**)malloc(sizeof(int*) * numLines);
  for(int i=0; i<numLines; i++) {
    map->map[i] = (int*)malloc(sizeof(int) * numColumns);
  }
}


void printMap(Map* newMap, int linesToPrint) {
  printf("\n%d %d %c %d\n", newMap->lines, newMap->columns, newMap->objective, newMap->numPoints);
  for(int i=0; i<newMap->numPoints; i++){
    printf("(%d, %d)\n", newMap->points[i].x, newMap->points[i].y);
  }
  for(int i=0; i<linesToPrint; i++) {
    for(int x=0; x<newMap->columns; x++) {
      printf("%d ", newMap->map[i][x]);
    }
    printf("\n");
  }
}
