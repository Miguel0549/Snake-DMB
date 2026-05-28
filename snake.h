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

void inicializar_juego(SnakeQueue* serpiente, Punto* comida, int* puntuacion,enum joystick_dir *direccion_actual, bool* juego_terminado );
void generar_comida(Punto* comida, SnakeQueue* serpiente);
void procesar_entrada(enum joystick_dir *direccion_actual);
void actualizar_logica(SnakeQueue* serpiente, Punto* comida, int* puntuacion,enum joystick_dir *direccion_actual, bool* juego_terminado);
void renderizar(SnakeQueue* serpiente, Punto* comida, int* puntuacion,enum joystick_dir *direccion_actual);
void dibujar_cuerpo(int x, int y, uint16_t color);
void dibujar_cabeza_flecha(int x, int y, enum joystick_dir dir, uint16_t color);

#endif // SNAKE_H