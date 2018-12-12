#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef struct point {
  short x;
  short y;
}Point;


typedef struct map {
  short lines;
  short columns;
  short numPoints;
  char objective;
  short **map;
  Point *points;
}Map;

typedef struct node{
  Point point;
  short Weight;
}Node;

typedef struct adjacencias{
  Point initPoint;
  Point finalPoint;
  Point * path;
  short pathCost;
  short pathSize;
}Adjacencias;

short horseJump(Point , Point );
Node * allHorseJumps(Map *, short , short , short *);
short checkPlay(short , short , short , short , Map *);
Point * djikstraTypeA(Map * map, Point initial, Point final, Point * st, unsigned short * wt, FILE * fout, int *_count, int printFlag);
void djikstraTypeB(Map * map, Point * st, unsigned short * wt, FILE * fout, int *tmpCost, int printFlag);
Point * createWalk(Map *map, Point * st, unsigned short *wt, Point initial, Point final, FILE *fout, int * _count);
void djikstraTypeC(Map * map, Point * st, unsigned short * wt, FILE * fout);
int* permute(int N, Adjacencias ** adj, int * permutation, int i, int * actualCost, Map * map, int* bestPermutation, int j);
void swapPoints(int *point1, int *point2);

void dijkstraC(Map * map, Point initial, Point final, Point * st, unsigned short * wt, FILE * fout, int *_count, int printFlag, int startingPointIdx);
int passedByPoints(unsigned short * wt, Point * points, int numPoints,int columns, int startingPointIdx);
Point * createWalkC(Map *map, Point * st, unsigned short *wt, Point initial, Point final, FILE *fout, int * _count);

#endif
