#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#include "structs.h"


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
  Adjacencias * new = (Adjacencias *)malloc(sizeof(Adjacencias));
  new->adjacencia = node;
  inserted->next = head->next;
  head->next = inserted;
  return head;
}

Adjacencias * allHorseJumps(Map * map, int x, int y) {
  Adjacencias * new = NULL;
  int cost = 1000;
  int tmp = 0;
  int isZero = 0;

  if(x >= map->lines || y >= map->columns || x < 0 || y < 0 ) {
    return new;
  }

  if(play->map[x][y] == 0) {
    return new;
  }

  new = (Adjacencias *)malloc(sizeof(Adjacencias));
  //Gerar a adjacencia inicial(ponto que estamos a contabilizar) e po-lo como a head
  Node initPoint = (Node*)malloc(sizeof(Node));
  initPoint->point->x = x;
  initPoint->point->y = y;
  new->adjacencia = initPoint;


  if(((tmp = checkPlay(x, y, 2, 1, map)) <= cost) && tmp != -1) {
    Node node1 = (Node *)malloc(sizeof(Node));
    node1->point->x = x + 2;
    node1->point->y = y + 1;
    new = insertNode(new, node1);
    // new[1].point = point1;
  }
  if(((tmp = checkPlay(x, y, 2, -1, play)) <= cost) && tmp != -1) {
    Node node1 = (Node *)malloc(sizeof(Node));
    node1->point->x = x + 2;
    node1->point->y = y + -1;
    new = insertNode(new, node1);
  }
  if(((tmp = checkPlay(play->points[0].x, play->points[0].y, -2, 1, play)) <= cost) && tmp != -1) {

  }
  if(((tmp = checkPlay(play->points[0].x, play->points[0].y, -2, -1, play)) <= cost) && tmp != -1) {

  }
  if(((tmp = checkPlay(play->points[0].x, play->points[0].y, 1, 2, play)) <= cost) && tmp != -1) {

  }
  if(((tmp = checkPlay(play->points[0].x, play->points[0].y, 1, -2, play)) <= cost) && tmp != -1) {

  }
  if(((tmp = checkPlay(play->points[0].x, play->points[0].y, -1, 2, play)) <= cost) && tmp != -1) {

  }
  if(((tmp = checkPlay(play->points[0].x, play->points[0].y, -1, -2, play)) <= cost) && tmp != -1) {

  }

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

Adjacencias * adjacencias(Map * map, int lines, int columns, Point init) {
  Adjacencias * head = NULL;
  int counter = 0;
  Adjacencias * array = (Adjacencias *)malloc(sizeof(Adjacencias) * lines * columns);
  for(int i = 0; i < lines; i++){
    for(int j = 0; j < columns; j++){
      if(map[i][j] != 0){
        head = allHorseJumps(map, i, j);
        array[counter] = head;
        counter++;
      }
    }
  }

}

//TODO Parte A remake
//TODO ter um vetor que guarde os pontos visitados, alocação dinâmica
//TODO criar um vetor com os pontos não visitados
//TODO

/*A matriz st tem o tamanho do mapa original, mas em cada index st[i][j] guarda o ponto PAI. A ideia é ir voltando para trás do ponto final para o ponto inicial
*
*/


int dijkstra(Map** mapa, int numLines, int numColumns, Points** st, int** wt, Point initial, Point final) {
  for(int i = 0; i < numLines; i++){
    for(int j = 0; j < numColumns; j++){
      wt[i][j] = MAX_INT;
      st[i][j] = -1;
    }
  }
  int x = -1; int y = -1;
  Point v;

  wt[initial->x][initial->y] = 0;

  while(x != final->x && y != final->y){
    v->x = acervo[0].x;
    v->y = acervo[0].y;
    if(wt[v->x][v->y] != MAX_INT){
      //TODO remover este primeiro vertice da fila
      //TODO fazer um ciclo for que itera por todas as adjacencias do vertice atual(o que foi tirado da fila)
    }
  }


}



//TODO Parte A
//TODO receber a matriz e os pontos inicial e final
//TODO pegar no primeiro ponto ver as adjacencias e fazer um acervo com as adjacencias
//TODO pegar no elemento do acervo com menor custo e fazer as adjacencias dele, adiciona-las ao acervo
//TODO tirar o elemento de menor custo e ver as suas adjacencias
//TODO repetir este processo até que o elemento de mentor custo seja o ponto final, encontramos o caminho mais curto entre os 2 pontos




//TODO Parte B
//TODO receber a matriz e os diversos pontos
//TODO pegar no primeiro ponto e preencher o acervo com as adjacencias
//TODO assim que chegarmos ao ponto seguinte recomeçar o processo começando no ponto seguinte
