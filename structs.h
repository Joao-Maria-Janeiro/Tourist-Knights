#ifndef _STRUCTS_H
#define _STRUCTS_H

#include "defs.h"

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

typedef struct Struct_adjacencias {
  Node * adjacencia;
  struct Struct_adjacencias * next;
}Adjacencias;

int horseJump(Point init, Point final);

#endif
