#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structs.h"
#include "heap.h"

#define INFINIY 2147483647

/* horseJump()
*  Checking if 2 points are connected by a horse jump
*/
int horseJump(Point init, Point final) {
  int x = final.x-init.x;
  int y = final.y-init.y;

  //Check the horse jump
  if(abs(x) == 2 && abs(y) == 1){
    //Horizontal 2 and vertical 1
    return 1;
  }else if(abs(x) == 1 && abs(y) == 2){
    //Horizontal 1 and vertical 2
    return 1;
  }
  return 0;
}

Adjacencias * insertNode(Adjacencias * head, Node * inserted){
  if(head == NULL){
    Adjacencias * new = (Adjacencias *)malloc(sizeof(Adjacencias));
    new->adjacencia = inserted;
    new->next = NULL;
    return new;
  }
  Adjacencias * new = (Adjacencias *)malloc(sizeof(Adjacencias));
  new->adjacencia = inserted;
  new->next = head->next;
  head->next = new;
  return head;
}

Node * allHorseJumps(Map * map, int x, int y, int *size) {
  Node * array = (Node *)malloc(8 * sizeof(Node));
  int cost = 1000;
  int tmp = 0;
  int isZero = 0;

  (*size) = 0;

  if(x >= map->lines || y >= map->columns || x < 0 || y < 0 ) {
    return NULL;
  }
  if(map->map[x][y] == 0) {
    return NULL;
  }


  if(((tmp = checkPlay(x, y, 2, 1, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x + 1;
    node1.point.y = y + 2;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  if(((tmp = checkPlay(x, y, 2, -1, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x - 1;
    node1.point.y = y + 2;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  if(((tmp = checkPlay(x, y, -2, 1, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x + 1;
    node1.point.y = y - 2;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  if(((tmp = checkPlay(x, y, -2, -1, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x - 1;
    node1.point.y = y - 2;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  if(((tmp = checkPlay(x, y, 1, 2, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x + 2;
    node1.point.y = y + 1;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }

  if(((tmp = checkPlay(x, y, 1, -2, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x - 2;
    node1.point.y = y + 1;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  if(((tmp = checkPlay(x, y, -1, 2, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x + 2;
    node1.point.y = y - 1;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  if(((tmp = checkPlay(x, y, -1, -2, map)) <= cost) && tmp != -1) {
    Node node1;
    node1.point.x = x - 2;
    node1.point.y = y - 1;
    node1.Weight = tmp;
    array[(*size)] = node1;
    (*size)++;
  }
  return array;
}

int checkPlay(int posX, int posY, int horizontal, int vertical, Map *play) {
  int finalPosX = posX + vertical;
  int finalPosY = posY + horizontal;


  if(finalPosX < 0 || finalPosX >= play->lines){
    return -1;
  }
  if(finalPosY < 0 || finalPosY >= play->columns) {
    return -1;
  }

  if(play->map[finalPosX][finalPosY] == 0) {
    return -1;
  }


  return play->map[finalPosX][finalPosY];
}



/*A matriz st tem o tamanho do mapa original, mas em cada index st[i][j] guarda o ponto PAI. A ideia é ir voltando para trás do ponto final para o ponto inicial
*
*/
Point * djikstraTypeA(Map * map, Point initial, Point final, Point * st, int * wt, FILE * fout, int *_count) {
  int allocatedHeapSize = 100;
  int heapSize = 0;
  int toInsertSize = 0;
  Point currentPoint;
  Node * acervo = (Node *)malloc(100 * sizeof(Node));
  st[initial.x * (map->columns) + initial.y] = initial;
  //wt[initial.x][initial.y] = 0;
  wt[initial.x * (map->columns) + initial.y] = 0;
  currentPoint.x = initial.x;
  currentPoint.y = initial.y;
  Adjacencias * adj;
  Node tmp;
  tmp.point = initial;
  tmp.Weight = map->map[initial.x][initial.y];
  add(tmp, acervo, &heapSize, &allocatedHeapSize);
  int count = 0;

  //We iterate until the point that comes out of the heap is the last point
  while(!(((currentPoint.x == final.x) && (currentPoint.y == final.y))) && heapSize != 0){
    Node *toInsert= NULL;
    //We get the smallest value from the heap removing it from the array
    currentPoint = pop(&heapSize ,acervo).point;
    if(wt[currentPoint.x * (map->columns) + currentPoint.y] != INFINIY){ //Check if the point hasn't been visited yet
      // We get all the adjacencies of the current point
      toInsert = allHorseJumps(map, currentPoint.x, currentPoint.y, &toInsertSize);
      for(int i=0; i<toInsertSize; i++) {
        if(wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] > wt[currentPoint.x * (map->columns) + currentPoint.y] + map->map[toInsert[i].point.x][toInsert[i].point.y]){
          wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] = wt[currentPoint.x * (map->columns) + currentPoint.y] + map->map[toInsert[i].point.x][toInsert[i].point.y];
          st[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] = currentPoint;
          toInsert[i].Weight = wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y];
          //Add the adjacencies one by one to the heap
          add(toInsert[i], acervo, &heapSize, &allocatedHeapSize);
          count++;
        }
      }
      free(toInsert);
    }
  }
  free(acervo);
  if((currentPoint.x != final.x && currentPoint.y != final.y) || heapSize == 0){
    fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, -1, 0);
    return NULL;
  }

  return createWalk(map, st, wt, initial, final, fout, _count);
}


Point * createWalk(Map *map, Point * st, int *wt, Point initial, Point final, FILE *fout, int * _count){
  Point tmp = final;
  Point * array = (Point*)malloc(sizeof(Point)* 100);
  int arraySize = 100;
  int count = 0;
  array[count] = final;

  //Iterate through the array in inverse order to count the points and add them to the array
  while(!((tmp.x == initial.x) && (tmp.y == initial.y))){
    if(count > arraySize){
      array = (Point *)realloc(array, (arraySize + 100)*sizeof(Point));
      arraySize += 100;
    }
    count++;
    tmp = st[tmp.x * (map->columns) + tmp.y];
    array[count] = tmp;
  }

  *_count = count;
  return array;
  //
  // //Print the header
  // fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, wt[final.x * (map->columns) + final.y], count);
  // for(int i=count-1; i>=0; i--) {
  //   fprintf(fout, "%d %d %d\n", array[i].x, array[i].y, map->map[array[i].x][array[i].y]); //Print the path
  // }
}




void djikstraTypeB(Map * map, Point * st, int * wt, FILE * fout){
  Point empty;
  empty.x = -1;
  empty.y = -1;
  int * counts = (int *)malloc( (map->numPoints - 1) * sizeof(int));
  int count = 0, size = 0, cost = 0;
  Point ** aux = (Point **)malloc((map->numPoints - 1) * sizeof(Point *));
  Point * array = (Point *)malloc( sizeof(Point));
  for(int i = 0; i < map->numPoints - 1; i++){
    for(int j = 0; j < (map->columns * map->lines); j++){
      wt[j] = INFINIY;
      st[j] = empty;
    }
    if(horseJump(map->points[i], map->points[i+1])) {
      aux[i] = (Point*)malloc(sizeof(Point));
      aux[i][0] = map->points[i+1];
      count = 1;
      counts[i] = count;
      size += count;
      cost += map->map[map->points[i+1].x][map->points[i+1].y];
    }else {
      aux[i] = djikstraTypeA(map, map->points[i], map->points[i+1], st, wt, fout, &count);
      counts[i] = count;
      size += count;
      cost += wt[map->points[i+1].x * (map->columns) + map->points[i+1].y];
    }
  }

  //Print the header
  fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, cost, size);
  for(int j=0; j < map->numPoints-1; j++) {
    for(int i=counts[j]-1; i>=0; i--) {
      fprintf(fout, "%d %d %d\n", aux[j][i].x, aux[j][i].y, map->map[aux[j][i].x][aux[j][i].y]); //Print the path
    }
  }
  free(array);
  free(counts);
  for(int i=0; i<map->numPoints - 1; i++) {
    free(aux[i]);
  }
  free(aux);
}

// void printWalk(Point ** st, Point initial, Point tmp, FILE *fout, int * count) {
//   if(((tmp.x == initial.x) && (tmp.y == initial.y))) {
//     (*count)++;
//     return;
//   }
//   if(*count == 0){
//     fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, wt[final.x][final.y], (*count));
//   }
//   printWalk(st, initial, st[tmp.x][tmp.y], &count);
//   fprintf(fout, "(%d %d)\n", tmp.x, tmp.y);
//
// }
