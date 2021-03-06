#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "structs.h"
#include "heap.h"

#define INFINITY 65533

/* horseJump()
*  Checking if 2 points are connected by a horse jump
*/
short horseJump(Point init, Point final) {
  short x = final.x-init.x;
  short y = final.y-init.y;

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


Node * allHorseJumps(Map * map, short x, short y, short *size) {
  Node * array = (Node *)malloc(8 * sizeof(Node));
  short cost = 1000;
  short tmp = 0;

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

short checkPlay(short posX, short posY, short horizontal, short vertical, Map *play) {
  short finalPosX = posX + vertical;
  short finalPosY = posY + horizontal;


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
Point * djikstraTypeA(Map * map, Point initial, Point final, Point * st, unsigned short * wt, FILE * fout, int *_count, int printFlag) {
  int allocatedHeapSize = 100;
  int heapSize = 0;
  short toInsertSize = 0;
  Point currentPoint;
  Node * acervo = (Node *)malloc(100 * sizeof(Node));
  st[initial.x * (map->columns) + initial.y] = initial;
  wt[initial.x * (map->columns) + initial.y] = 0;
  currentPoint.x = initial.x;
  currentPoint.y = initial.y;
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
    if(wt[currentPoint.x * (map->columns) + currentPoint.y] != INFINITY){ //Check if the point hasn't been visited yet
      // We get all the adjacencies of the current point
      toInsert = allHorseJumps(map, currentPoint.x, currentPoint.y, &toInsertSize);
      for(int i=0; i<toInsertSize; i++) {
        if(wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] > wt[currentPoint.x * (map->columns) + currentPoint.y] + map->map[toInsert[i].point.x][toInsert[i].point.y]){
          wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] = wt[currentPoint.x * (map->columns) + currentPoint.y] + map->map[toInsert[i].point.x][toInsert[i].point.y];
          st[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] = currentPoint;
          toInsert[i].Weight = wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y];
          //Add the adjacencies one by one to the heap
          if(heapSize >= allocatedHeapSize) {
            acervo = (Node *)realloc(acervo, (allocatedHeapSize +100) * sizeof(Node));
            allocatedHeapSize+=100;
          }
          add(toInsert[i], acervo, &heapSize, &allocatedHeapSize);
          count++;
        }
      }
      free(toInsert);
    }
  }
  free(acervo);
  //If the final point was not removed from the heap, there is no path between the two points
  if((currentPoint.x != final.x && currentPoint.y != final.y)){
    if(printFlag)
      fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, -1, 0);
    *_count = -1;
    return NULL;
  }

  return createWalk(map, st, wt, initial, final, fout, _count);
}


Point * createWalk(Map *map, Point * st, unsigned short *wt, Point initial, Point final, FILE *fout, int * _count){
  Point tmp = final;
  Point * array = (Point*)malloc(sizeof(Point)* 100);
  int arraySize = 100;
  int count = 0;
  array[count] = final;

  //Iterate through the array in inverse order to count the points and add them to the array
  while(!((tmp.x == initial.x) && (tmp.y == initial.y)) ){
    if(count >= arraySize){
      array = (Point *)realloc(array, (arraySize + 100)*sizeof(Point));
      arraySize += 100;
    }
    count++;
    tmp = st[tmp.x * (map->columns) + tmp.y];
    array[count] = tmp;
  }

  *_count = count;
  return array;
}




void djikstraTypeB(Map * map, Point * st, unsigned short * wt, FILE * fout, int * tmpCost, int printFlag){
  Point empty;
  empty.x = -1;
  empty.y = -1;
  int * counts = (int *)malloc( (map->numPoints - 1) * sizeof(int));
  int count = 0, size = 0, cost = 0;
  Point ** aux = (Point **)malloc((map->numPoints - 1) * sizeof(Point *));
  Point * array = (Point *)malloc( sizeof(Point));
  for(int i = 0; i < map->numPoints - 1; i++){
    //Check if the points can be connected with only one horse jump
    if(horseJump(map->points[i], map->points[i+1])) {
      aux[i] = (Point*)malloc(sizeof(Point));
      aux[i][0] = map->points[i+1];
      count = 1;
      counts[i] = count;
      size += count;
      cost += map->map[map->points[i+1].x][map->points[i+1].y];
      //Check if the next point is the same as the current point, so we don't have move
    }else if(map->points[i].x == map->points[i+1].x && map->points[i].y == map->points[i+1].y) {
      aux[i] = (Point*)malloc(sizeof(Point));
      aux[i][0] = map->points[i+1];
      count = 0;
      counts[i] = count;
      size += count;
      cost += 0;
      //If none of the above conditions are met simply run a Dijkstra to find the path between the two points
    } else {
      for(int j = 0; j < (map->columns * map->lines); j++){
        wt[j] = INFINITY;
        st[j] = empty;
      }
      aux[i] = djikstraTypeA(map, map->points[i], map->points[i+1], st, wt, fout, &count, 1);
      if(count == -1) {
        printFlag = 2;
      }
      counts[i] = count;
      size += count;
      cost += wt[map->points[i+1].x * (map->columns) + map->points[i+1].y];
    }
  }


  (*tmpCost) = cost;

  //Print the result to the file
  if(printFlag == 1) {
      if(cost >= 0){
      //Print the header
      fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, cost, size);
      for(int j=0; j < map->numPoints-1; j++) {
        for(int i=counts[j]-1; i>=0; i--) {
            fprintf(fout, "%d %d %d\n", aux[j][i].x, aux[j][i].y, map->map[aux[j][i].x][aux[j][i].y]); //Print the path
        }
      }
    }
  }



  free(array);
  free(counts);
  for(int i=0; i<map->numPoints - 1; i++) {
    free(aux[i]);
  }
  free(aux);

}


int passedByPoints(unsigned short * wt, Point * points, int numPoints,int columns, int startingPointIdx){
  //Iterate through all points and check if they have been passed by
  for(int i = startingPointIdx; i < numPoints; i++) {
    if(wt[points[i].x * columns + points[i].y] == INFINITY) {
      return 0;
    }
  }
  return 1;
}

Point * createWalkC(Map *map, Point * st, unsigned short *wt, Point initial, Point final, FILE *fout, int * _count){
  Point tmp = final;
  Point * array = (Point*)malloc(sizeof(Point)* 100);
  int arraySize = 100;
  int count = 0;
  array[count] = final;

  //Iterate through the array in inverse order to count the points and add them to the array
  while(!((tmp.x == initial.x) && (tmp.y == initial.y)) ){
    if(count >= arraySize){
      array = (Point *)realloc(array, (arraySize + 100)*sizeof(Point));
      arraySize += 100;
    }
    count++;
    tmp = st[tmp.x * (map->columns) + tmp.y];
    array[count] = tmp;
  }

  *_count = count;
  return array;
}



void dijkstraC(Map * map, Point initial, Point final, Point * st, unsigned short * wt, FILE * fout, int *_count, int printFlag, int startingPointIdx) {
  int allocatedHeapSize = 100;
  int heapSize = 0;
  short toInsertSize = 0;
  Point currentPoint;
  Node * acervo = (Node *)malloc((map->lines * map->columns) * sizeof(Node));
  st[initial.x * (map->columns) + initial.y] = initial;
  wt[initial.x * (map->columns) + initial.y] = 0;
  currentPoint.x = initial.x;
  currentPoint.y = initial.y;
  Node tmp;
  tmp.point = initial;
  tmp.Weight = map->map[initial.x][initial.y];
  add(tmp, acervo, &heapSize, &allocatedHeapSize);
  int count = 0;

  int** heapPositions = (int**)malloc(map->lines * sizeof(int*));
  for(int i=0; i<map->lines; i++) {
    heapPositions[i] = (int*)malloc(map->columns * sizeof(int));
    for(int x=0; x<map->columns; x++)
      heapPositions[i][x] = -1;
  }

  while(passedByPoints(wt, map->points, map->numPoints, map->columns, startingPointIdx) == 0 && (heapSize != 0)){
    Node *toInsert= NULL;
    //We get the smallest value from the heap removing it from the array
    currentPoint = popC(&heapSize ,acervo, heapPositions).point;
    //printf("%d %d %d\n", currentPoint.x, currentPoint.y, map->map[currentPoint.x][currentPoint.y]);
    if(wt[currentPoint.x * (map->columns) + currentPoint.y] != INFINITY){ //Check if the point hasn't been visited yet
      // We get all the adjacencies of the current point
      toInsert = allHorseJumps(map, currentPoint.x, currentPoint.y, &toInsertSize);
      for(int i=0; i<toInsertSize; i++) {
        //Check if the adjacencie cost in wt is smaller than the parent cost plus the adjacencie cost in the map
        if(wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] > wt[currentPoint.x * (map->columns) + currentPoint.y] + map->map[toInsert[i].point.x][toInsert[i].point.y]){
          wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] = wt[currentPoint.x * (map->columns) + currentPoint.y] + map->map[toInsert[i].point.x][toInsert[i].point.y];
          st[toInsert[i].point.x*(map->columns)+toInsert[i].point.y] = currentPoint;
          toInsert[i].Weight = wt[toInsert[i].point.x*(map->columns)+toInsert[i].point.y];
          //If it's a new point add to the heap
          if(heapPositions[toInsert[i].point.x][toInsert[i].point.y] == -1) {
            addC(toInsert[i], acervo, &heapSize, &allocatedHeapSize, heapPositions);
          }else {
            //Otherwise simply update it's value
            acervo[heapPositions[toInsert[i].point.x][toInsert[i].point.y]].Weight = toInsert[i].Weight;
          }
          count++;
        }
      }
      free(toInsert);
    }
  }
  free(acervo);
  for(int i=0; i<map->lines; i++) {
    free(heapPositions[i]);
  }
  free(heapPositions);

  //Check if all the points have been passed by, if not there's no path
  if(passedByPoints(wt, map->points, map->numPoints, map->columns, startingPointIdx) == 0){
    if(printFlag)
      fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, -1, 0);

    *_count = -1;
    return;
  }

  return;
}

void djikstraTypeC(Map * map, Point * st, unsigned short * wt, FILE * fout) {
  Point empty;
  empty.x = -1;
  empty.y = -1;
  int totalSteps = 0;

  int * bestPermutation = NULL;

  int finalCost = INFINITY;


  int * permutation = (int *)malloc((map->numPoints) * sizeof(int));
  int count = 0;

  Adjacencias ** adj = (Adjacencias **)malloc((map->numPoints -1) * sizeof(Adjacencias*));


  for(int i=0; i<map->numPoints -1; i++) {
    adj[i] = (Adjacencias*)malloc((map->numPoints) * sizeof(Adjacencias));
  }
  Point * dijkstraPath = NULL;

  //Iterate through all points
  for(int i = 0; i < map->numPoints - 1; i++){
    count = 0;
    //After each point is done reset st and wt
    for(int x = 0; x < (map->columns * map->lines); x++){
      wt[x] = INFINITY;
      st[x] = empty;
    }
    //Iterate through the remaning points in order to get all adjacencies
    for(int j = i + 1; j < map->numPoints; j++){
      count = 0;
      // If we already have a cost on the point j coming from the point i we don't need to run dijkstra again, we only need the path
      if(wt[map->points[j].x * (map->columns) + map->points[j].y] != INFINITY){
        dijkstraPath = createWalk(map, st, wt, map->points[i], map->points[j], fout, &count);
      }else{
        for(int x = 0; x < (map->columns * map->lines); x++){
          wt[x] = INFINITY;
          st[x] = empty;
        }
        dijkstraC(map, map->points[i], map->points[j], st, wt, fout, &count, 0, i);
        if(count != -1)
          dijkstraPath = createWalk(map, st, wt, map->points[i], map->points[j], fout, &count);
      }
      adj[i][j].path = dijkstraPath;
      adj[i][j].pathSize =  count;
      adj[i][j].pathCost = wt[map->points[j].x * (map->columns) + map->points[j].y];
      adj[i][j].initPoint = map->points[i];
      adj[i][j].finalPoint = map->points[j];
    }
  }

  int cost = 0;
  int valid = 0;
  for (int i = 0; i < map->numPoints -1; i++) {
    for (int j = i + 1; j < map->numPoints; j++) {
      if(adj[i][j].pathSize != -1){
        valid = 1;
      }
    }
  }

  //If there's a path
  if(valid == 1){
    for(int i = 0; i < map->numPoints; i++){
      permutation[i] = i;
    }

    //Memory allocation for the best permutation
    bestPermutation = (int *)malloc(map->numPoints * sizeof(int));

    //Get the permutation with the smallest cost
    bestPermutation = permute(map->numPoints, adj, permutation, 1, &finalCost, map, bestPermutation, 0);
    for(int i = 0; i < map->numPoints-1; i++){
      if(bestPermutation[i] > bestPermutation[i+1]){
        totalSteps += adj[bestPermutation[i + 1]][bestPermutation[i]].pathSize;
        cost += adj[bestPermutation[i + 1]][bestPermutation[i]].pathCost + map->map[adj[bestPermutation[i+1]][bestPermutation[i]].initPoint.x][adj[bestPermutation[i+1]][bestPermutation[i]].initPoint.y] - map->map[adj[bestPermutation[i+1]][bestPermutation[i]].finalPoint.x][adj[bestPermutation[i+1]][bestPermutation[i]].finalPoint.y];
      }else{
        totalSteps += adj[bestPermutation[i]][bestPermutation[i+1]].pathSize;
        cost += adj[bestPermutation[i]][bestPermutation[i+1]].pathCost;
      }
    }
  }

  if(cost > 0 && valid == 1){
    //Print the output file header
    fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, cost, totalSteps);

    for(int i = 0; i < map->numPoints - 1; i++){
      // printf("%d %d\n", bestPermutation[i], bestPermutation[i+1]);
      if(bestPermutation[i] > bestPermutation[i+1]){
        for(int j = 1; j <= adj[bestPermutation[i + 1]][bestPermutation[i]].pathSize ; j++){
          if(j == adj[bestPermutation[i + 1]][bestPermutation[i]].pathSize){
            fprintf(fout, "%d %d %d\n", adj[bestPermutation[i+1]][bestPermutation[i]].initPoint.x, adj[bestPermutation[i+1]][bestPermutation[i]].initPoint.y, map->map[adj[bestPermutation[i+1]][bestPermutation[i]].initPoint.x][adj[bestPermutation[i+1]][bestPermutation[i]].initPoint.y]);
          }else {
            fprintf(fout, "%d %d %d\n", adj[bestPermutation[i+1]][bestPermutation[i]].path[j].x, adj[bestPermutation[i+1]][bestPermutation[i]].path[j].y, map->map[adj[bestPermutation[i+1]][bestPermutation[i]].path[j].x][adj[bestPermutation[i+1]][bestPermutation[i]].path[j].y]);
          }
        }
      }else{
        for(int j = adj[bestPermutation[i]][bestPermutation[i+1]].pathSize - 1; j >= 0 ; j--){
          if(j == 0){
            fprintf(fout, "%d %d %d\n", adj[bestPermutation[i]][bestPermutation[i+1]].finalPoint.x, adj[bestPermutation[i]][bestPermutation[i+1]].finalPoint.y, map->map[adj[bestPermutation[i]][bestPermutation[i+1]].finalPoint.x][adj[bestPermutation[i]][bestPermutation[i+1]].finalPoint.y]);
          }else{
            fprintf(fout, "%d %d %d\n", adj[bestPermutation[i]][bestPermutation[i+1]].path[j].x, adj[bestPermutation[i]][bestPermutation[i+1]].path[j].y, map->map[adj[bestPermutation[i]][bestPermutation[i+1]].path[j].x][adj[bestPermutation[i]][bestPermutation[i+1]].path[j].y]);
          }
        }
      }
    }
  }else{
    fprintf(fout, "%d %d %c %d %d %d\n", map->lines, map->columns, map->objective, map->numPoints, -1, 0);
  }

  free(permutation);
  free(bestPermutation);
  for(int i = 0; i < map->numPoints - 1; i++) {
    for(int j = i + 1; j < map->numPoints; j++){
      free(adj[i][j].path);
    }
    free(adj[i]);
  }
  free(adj);
}


void swapPoints(int *point1, int *point2) {
    int tmp = *point1;
    *point1 = *point2;
    *point2 = tmp;
}

/*
*/

int * permute(int N, Adjacencias ** adj, int * array, int i, int *bestPermutationCost, Map * map, int* bestPermutation, int cost) {
  static int counter = 0;
  //Avoid the fist time we enter the function
  if(i != 1) {
    if(array[i-2] > array[i-1]){
      cost += adj[array[i -1]][array[i-2]].pathCost + map->map[adj[array[i-1]][array[i-2]].initPoint.x][adj[array[i-1]][array[i-2]].initPoint.y] - map->map[adj[array[i-1]][array[i-2]].finalPoint.x][adj[array[i-1]][array[i-2]].finalPoint.y];
    }else{
      cost += adj[array[i-2]][array[i-1]].pathCost;
    }
  }
  //Check it it's a worthless permutation
  if(cost >= *bestPermutationCost && *bestPermutationCost != INFINITY){
    return NULL;
  }

  //Verify if we have reached the final point in the current permutation
  if(i == N){
    if(*bestPermutationCost > cost ) {
      *bestPermutationCost = cost;
      memcpy(bestPermutation, array, N*sizeof(int));
    }
    return NULL;
  }
  counter++;

  //Iterate through all points and swap them to create the different permutations
    for (int j = i; j < N; j++) {
      if(i == j) {
        permute(N, adj, array, i+1, bestPermutationCost, map, bestPermutation, cost);
      } else {
        swapPoints(array+i,array+j);
        permute(N, adj, array, i+1, bestPermutationCost, map, bestPermutation, cost);
        swapPoints(array+i,array+j);
      }
    }
    return bestPermutation;
}
