#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "structs.h"
#include "data.h"


void readFromFile(char * file_name) {
  //create necessary variables
  int lineCounter = 0, lines=0, columns=0, numPoints=0, validMap = 0, i = 0, j = 0, lixinho = 0, numLines = 0;
  char objective = '0';
  char linha[4];
  Map * map = NULL;
  Adjacencias * pointsVector;
  //read all the map info
  FILE * fp;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    printf("Error opening file\n");
    exit(0);
  }
  while(fscanf(fp, "%d %d %c %d ", &lines, &columns, &objective, &numPoints) == 4){
    //verify if it's a valid map
    validMap=0;
    if(verifyMap(lines, columns, objective, numPoints) == 0){
      //We verify if the map is valid and, if so, assing 0 to validMap
      validMap = -1;
    }
    //read all points
    if(validMap != -1){
      map = (Map*)malloc(sizeof(Map));
      allocatePoints(map, lines, columns, objective, numPoints);
      for(i = 0; i < numPoints; i++){
        lixinho = fscanf(fp, "%d %d", &map->points[i].x, &map->points[i].y);
      }
      //select the correct read function for the current objective
      switch (map->objective){
        //A :
        case 'A':
        //TODO check if point can be accessed in a horse jump and if so only read the necessary lines
        if(horseJump(map->points[0], map->points[1]) == 1){
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
          while(fgets(linha, 4, fp) != NULL) {
            //Move pointer until a empty line
            if(*linha == '\n')
              break;
          }
        }else{
          allocateMap(map, lines, columns);
          //Else read the rest of the lines
          for(i = 0; i < lines; i++){
            for(j = 0; j < columns; j++){
              lixinho = fscanf(fp, "%d ", &map->map[i][j]);
            }
          }
          //Começar a criar uma lista de adjacências a partir do ponto inicial
          pointsVector = adjacencias(map, lines, columns, map->points[0]);
          djikstra(pointsVector);
        }
        break;
      }
    }else{
      //Move the pointer to the end of the map
      while(fgets(linha, 4, fp) != NULL) {
        //Move pointer until a empty line
        if(*linha == '\n')
          break;
      }
    }
  }


printMap(map, numLines);

}


int verifyMap(int lines, int columns, char objective, int numPoints) {
  if(objective != 'A'  && objective != 'B'){
    return 0;
  }
  if(objective == 'A' && numPoints != 2) {
    return 0;
  }
  if(objective == 'B' && numPoints < 2){
    return 0;
  }
  return 1;
}

void allocatePoints(Map * newMap, int lines, int columns, char objective, int numPoints){
  int i = 0;
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
