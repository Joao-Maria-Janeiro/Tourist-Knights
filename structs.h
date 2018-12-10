#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef struct point {
  int x;
  int y;
}Point;


typedef struct map {
  int lines;
  int columns;
  int numPoints;
  char objective;
  int **map;
  Point *points;
}Map;


typedef struct result {
  int lines;
  int columns;
  int numPoints;
  char objective;
  int isValid;
  int cost;
}Result;

typedef struct node{
  Point point;
  int Weight;
}Node;

typedef struct adjacencias{
  Point initPoint;
  Point finalPoint;
  Point * path;
  int pathCost;
  int pathSize;
}Adjacencias;

int horseJump(Point , Point );
Node * allHorseJumps(Map *, int , int , int *);
int checkPlay(int , int , int , int , Map *);
Point * djikstraTypeA(Map * map, Point initial, Point final, Point * st, int * wt, FILE * fout, int *_count);
void djikstraTypeB(Map * map, Point * st, int * wt, FILE * fout, int *tmpCost, int printFlag);
Point * createWalk(Map *map, Point * st, int *wt, Point initial, Point final, FILE *fout, int * _count);
void djikstraTypeC(Map * map, Point * st, int * wt, FILE * fout);
int* permute(int N, Adjacencias ** adj, int * permutation, int i, int * actualCost, Map * map, int* bestPermutation, int j);
void swapPoints(int *point1, int *point2);

#endif
