#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "glcd.h"       
#include "joystick.h"   
#include "cola.h"

#define MAX_SNAKE_LENGTH 168

#define SERPIENTE 1
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

typedef struct{
		uint8_t t[14][7];
		uint8_t n_frutas;
}Tablero;

typedef struct{
	Punto cabeza;
	Punto final;
	Cola* movs_pendientes;
	uint8_t tama;
} Snake;


void initSnake(Snake *serpi);
void moveSnake(Snake *snake, Tablero* tab, Punto direccion, bool ateFood);
bool verificarColisionCuerpo(Snake *snake, Punto nuevaCabeza, Tablero* t);
void initTablero(Snake *snake, Tablero* tab);
void inicializar_juego(Snake* serpiente,Tablero* tablero, uint16_t* puntuacion, enum joystick_dir *direccion_actual, bool* juego_terminado);
void generar_comida(Snake* serpiente, Tablero* tab);
void procesar_entrada(enum joystick_dir *direccion_actual);
Punto trans_joy_to_point(enum joystick_dir direccion_actual);
void actualizar_logica(Snake* serpiente, Tablero* tab, uint16_t* puntuacion, Punto direccion, bool* juego_terminado );
void renderizar(Snake* serpiente, Tablero* tab, uint16_t* puntuacion,enum joystick_dir *direccion_actual);
void renderizarBucle(Snake* snake, Tablero* tab, uint16_t* puntuacion, enum joystick_dir *direccion_actual);
void pantalla_victoria(uint16_t* puntuacion);
void pantalla_derrota(uint16_t* puntuacion);
void pantalla_continuar();
void dibujar_cuerpo(uint8_t x, uint8_t y, uint16_t color);
void dibujar_cabeza_flecha(uint8_t x, uint8_t y, enum joystick_dir dir, uint16_t color);
void dibujar_fruta (uint8_t x, uint8_t y, uint16_t color);
void pantalla_victoria(uint16_t* puntuacion);
void pantalla_derrota(uint16_t* puntuacion);
void pantalla_continuar();


#endif // SNAKE_H