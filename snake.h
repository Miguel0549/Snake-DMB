#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "glcd.h"       
#include "joystick.h"   
#include <stdint.h>

#define MAX_SNAKE_LENGTH 168

#define SERPIENTE -1
#define VACIA 0
#define FRUTA 2

#define FILAS 7
#define COLUMNAS 14
#define TAM_BLOQUE 32

#define OFFSET_X 16
#define OFFSET_Y 32

typedef enum {
		ARRIBA,
		ABAJO,
		IZQUIERDA,
		DERECHA
}DIR;

typedef struct {
    uint8_t x; 
    uint8_t y; 
} Punto;

typedef struct{
		uint8_t t[7][14];
} Tablero;

typedef struct {
    DIR body[MAX_SNAKE_LENGTH];
    Punto front;
    Punto rear;
    uint8_t size;
} SnakeQueue;

void initTablero(SnakeQueue *snake,Tablero* tablero);
void enqueue(SnakeQueue *snake, Punto newHead);
Punto dequeue(SnakeQueue *snake);
void moveSnake(SnakeQueue *snake, Punto nextHead, bool ateFood);
bool verificarColisionCuerpo(SnakeQueue *snake, Punto punto);

void inicializar_juego(SnakeQueue* serpiente,Tablero* tablero, Punto* comida, uint16_t* puntuacion,enum joystick_dir *direccion_actual, bool* juego_terminado );
void generar_comida(Punto* comida, SnakeQueue* serpiente);
void procesar_entrada(enum joystick_dir *direccion_actual);
void actualizar_logica(SnakeQueue* serpiente, Punto* comida, uint16_t* puntuacion,enum joystick_dir *direccion_actual, bool* juego_terminado);
void renderizar(SnakeQueue* serpiente, Punto* comida, uint16_t* puntuacion,enum joystick_dir *direccion_actual);
void dibujar_cuerpo(uint8_t x, uint8_t y, uint16_t color);
void dibujar_cabeza_flecha(uint8_t x, uint8_t y, enum joystick_dir dir, uint16_t color);

#endif // SNAKE_H