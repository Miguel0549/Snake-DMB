/**
 * @file    snake.h
 * @brief   Macros y funciones para jugar al snake en el LPC4088 Developer's Kit con joystick y la pantalla del kit. 
 * Empiezas con una serpiente de 3 unidades de longitud, según comes frutas, de las cuales habrá siempre máximo 3, creces y ganas puntos.
 * El objetivo es crecer al tamaño de la pantalla completa, que es de 14*7 unidades
 *
 * @author  Miguel López Rodríguez | Miguel Catalá Garrido
 * @date    2026
 */

#ifndef SNAKE_H
#define SNAKE_H

#include "cola.h"
#include "glcd.h"
#include "joystick.h"
#include <stdbool.h>

/**
 * @defgroup  SNAKE_Macros_Publicas SNAKE - Macros Públicas
 * @ingroup   SNAKE
 * @brief     Constantes varias para lógica y tamaños
 * @{
 */
#define MAX_SNAKE_LENGTH 168

#define SERPIENTE 1
#define VACIA 0
#define FRUTA 2

#define FILAS 14
#define COLUMNAS 7
#define TAM_BLOQUE 32

#define OFFSET_X 16
#define OFFSET_Y 32
//!@}

/**
 * @brief Direcciones a las que se puede mover la serpiente
 * @ingroup SNAKE
 */
typedef enum { ARRIBA, ABAJO, IZQUIERDA, DERECHA } DIR;

/**
 * @brief Estructura del tablero
 * @ingroup SNAKE
 */
typedef struct {
  uint8_t t[14][7];
  uint8_t n_frutas;
} Tablero;

/**
 * @brief Estructura de la serpiente
 * @ingroup SNAKE
 */
typedef struct {
  Punto cabeza;
  Punto final;
  Cola *movs_pendientes;
  uint8_t tama;
} Snake;

// ===== SNAKE - Funciones Publicas =====
void initSnake(Snake *serpi);
void moveSnake(Snake *snake, Tablero *tab, Punto direccion, bool ateFood);
bool verificarColisionCuerpo(Snake *snake, Punto nuevaCabeza, Tablero *t);
void initTablero(Snake *snake, Tablero *tab);
void inicializar_juego(Snake *serpiente, Tablero *tablero, uint16_t *puntuacion,
                       enum joystick_dir *direccion_actual,
                       bool *juego_terminado);
void generar_comida(Snake *serpiente, Tablero *tab);
void procesar_entrada(enum joystick_dir *direccion_actual);
Punto trans_joy_to_point(enum joystick_dir direccion_actual);
void actualizar_logica(Snake *serpiente, Tablero *tab, uint16_t *puntuacion,
                       Punto direccion, bool *juego_terminado);
void renderizar(Snake *serpiente, Tablero *tab, uint16_t *puntuacion,
                enum joystick_dir *direccion_actual);
void renderizarBucle(Snake *snake, Tablero *tab, uint16_t *puntuacion,
                     enum joystick_dir *direccion_actual);
void dibujar_cuerpo(uint8_t x, uint8_t y, uint16_t color);
void dibujar_cabeza_flecha(uint8_t x, uint8_t y, enum joystick_dir dir,
                           uint16_t color);
void dibujar_fruta(uint8_t x, uint8_t y, uint16_t color);
void pantalla_victoria(uint16_t *puntuacion);
void pantalla_derrota(uint16_t *puntuacion);
void pantalla_continuar();
void pantalla_iniciar();

#endif // SNAKE_H