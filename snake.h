#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "glcd.h"       
#include "joystick.h"   

#define MAX_SNAKE_LENGTH 168

#define FILAS 7
#define COLUMNAS 14
#define TAM_BLOQUE 32

#define OFFSET_X 16
#define OFFSET_Y 32

typedef struct {
    int x; 
    int y; 
} Punto;

typedef struct {
    Punto body[MAX_SNAKE_LENGTH];
    int front;
    int rear;
    int size;
} SnakeQueue;

void initSnake(SnakeQueue *snake);
void enqueue(SnakeQueue *snake, Punto newHead);
Punto dequeue(SnakeQueue *snake);
void moveSnake(SnakeQueue *snake, Punto nextHead, bool ateFood);
bool verificarColisionCuerpo(SnakeQueue *snake, Punto punto);

#endif // SNAKE_H