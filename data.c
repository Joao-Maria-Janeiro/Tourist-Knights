#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "data.h"
#include "heap.h"


void readFromFile(char * file_name) {
  Node *heap = NULL;
  int heapSize=0, allocatedHeapSize=0;
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
        //check if point can be accessed in a horse jump and if so only read the necessary lines
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
          numLines = lines;
          //Alocação para a matriz st (de pontos, para o caminho)
          Point **st = (Point**)malloc(sizeof(Point*)*lines);
          //Alocação para a matriz wt (de custos)
          int **wt = (int**)malloc(sizeof(int*)*lines);
          //Else read all the lines
          for(i = 0; i < lines; i++){
            st[i] = (Point*)malloc(sizeof(Point)*columns);
            wt[i] = (int*)malloc(sizeof(int)*columns);
            for(j = 0; j < columns; j++){
              lixinho = fscanf(fp, "%d ", &map->map[i][j]);
            }
          }
          //Começar a criar uma lista de adjacências a partir do ponto inicial
          // pointsVector = adjacencias(map, lines, columns, map->points[0]);
          // djikstra(map,lines, columns, st, wt);
        }
        break;
        case 'B':
        break;
        case 'C':
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

  heap = (Node*)malloc(sizeof(Node)*100);  //Alocacao de um tamanho "razoável"
  allocatedHeapSize = 100;
  //dijkstra(map, st, wt, heap, &heapSize, &allocatedHeapSize);


  //TODO Após a leitura do mapa, adicionar os pontos ao acervo
  /* TESTE DAS FUNCOES DO ACERVO
  heap = (Node*)malloc(sizeof(Node)*5);
  heapSize = 0;
  Node tmp1;
  tmp1.point.x=2;
  tmp1.point.y=3;
  tmp1.Weight = 10;
  add(tmp1, heap, &heapSize);
  printHeap(heapSize, heap);
  Node tmp2;
  tmp2.point.x=4;
  tmp2.point.y=5;
  tmp2.Weight = 11;
  add(tmp2, heap, &heapSize);
  printf("\n");
  printHeap(heapSize, heap);
  Node tmp3;
  tmp3.point.x=7;
  tmp3.point.y=7;
  tmp3.Weight = 9;
  add(tmp3, heap, &heapSize);
  printf("\n");
  printHeap(heapSize, heap);
  pop(&heapSize, heap);
  printf("\n");
  printHeap(heapSize, heap);*/

printf("\n\n");
printMap(map, numLines);


fclose(fp);
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
