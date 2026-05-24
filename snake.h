#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>


#define ESQ_SI 201
#define ESQ_SD 187
#define ESQ_II 200
#define ESQ_ID 188
#define BAR_H 205
#define BAR_V 186

#define N 468 //limite horizontal
#define M 256 //limite vertical

// Tablero 7 x 24 
// x (0-6)
// y (0-23)


#define MAX_SNAKE_LENGTH 168


typedef struct {
    int x;
    int y;
}Punto;

// Estructura de la Serpiente basada en una Cola
typedef struct {
    Punto body[MAX_SNAKE_LENGTH];
    int front;
    int rear;
    int size;
} SnakeQueue;


inline void initSnake(SnakeQueue *snake) {
    snake->front = 0;
    snake->rear = -1;
    snake->size = 0;
}


void enqueue(SnakeQueue *snake, Punto newHead);
Punto dequeue(SnakeQueue *snake);
void moveSnake(SnakeQueue *snake, Punto nextHead, bool ateFood);
void pintar_tablero();


#endif // SNAKE_H