/**
 * @file snake.h
 * @brief Definición de funciones y estructuras para el juego Snake.
 */
#ifndef SNAKE_H
#define SNAKE_H

#include "cola.h"
#include "glcd.h"
#include "joystick.h"
#include <stdbool.h>

/**
 * @brief   Tamano maximo de la serpiente.
 *
 */
#define MAX_SNAKE_LENGTH 168

/**
 * @brief   Casilla en la que se encuentra cualquier parte de la serpiente.
 *
 */
#define SERPIENTE 1

/**
 * @brief   Casilla vacia.
 *
 */
#define VACIA 0

/**
 * @brief   Casilla en la que se encuentra una fruta.
 *
 */
#define FRUTA 2

/**
 * @brief   Numero de filas del tablero.
 *
 */
#define FILAS 7

/**
 * @brief   Numero de columnas del tablero.
 *
 */
#define COLUMNAS 14

/**
 * @brief   Tamano en pixeles de cada casilla del tablero ( NxN ).
 *
 */
#define TAM_BLOQUE 32

/**
 * @brief   Espacio en x par.
 *
 */
#define OFFSET_X 16
#define OFFSET_Y 32

/**
 * @brief   Direcciones posibles de la serpiente.
 *
 */
typedef enum { ARRIBA, ABAJO, IZQUIERDA, DERECHA } DIR;

/**
 * @brief   Estructura del tablero.
 *
 */
typedef struct {
  uint8_t t[14][7];
  uint8_t n_frutas;
} Tablero;

/**
 * @brief   Estructura de la serpiente.
 *
 */
typedef struct {
  Punto cabeza;
  Punto final;
  Cola *movs_pendientes;
  uint8_t tama;
} Snake;

/**
 * @brief   Inicializala la serpiente.
 *
 * @param[in]   serpi      Direccion de la serpiente
 */
void initSnake(Snake *serpi);

/**
 * @brief   Mueve la serpiente en la direccion especificada.
 *
 * @param[in]		snake      	 Direccion de la serpiente
 * @param[in]   tablero   	 Direccion del tablero
 * @param[in]   direccion    Direccion en la que se movera la serpiente
 * @param[in]   ateFood      Booleano que indica si la serpiente comeria o no al
 * realizar el movimiento
 */
void moveSnake(Snake *snake, Tablero *tab, Punto direccion, bool ateFood);

/**
 * @brief   Comprueba si la serpiente colisiona con el borde del tablero o con
 * su propio cuerpo.
 *
 * @param[in]		snake      	  Direccion de la serpiente
 * @param[in]   nuevaCabeza   Direccion del tablero
 * @param[in]   t    					Direccion en la que se
 * movera la serpiente
 *
 *
 * @return Devuelve True si la serpiente chocaria con el limite del tablero o su
 * cuerpo y False en caso contrario
 */
bool verificarColisionCuerpo(Snake *snake, Punto nuevaCabeza, Tablero *t);

/**
 * @brief   Inicia el tablero con las posiciones iniciales de las serpiente y
 * las frutas.
 *
 * @param[in]		snake      	 Direccion de la serpiente
 * @param[in]   tablero   	 Direccion del tablero
 */
void initTablero(Snake *snake, Tablero *tab);

/**
 * @brief   Empieza la partida inicializando la puntuacion , el tablero y la
 * serpiente.
 *
 * @param[in]		snake      	 Direccion de la serpiente
 * @param[in]   tablero   	 Direccion del tablero
 * @param[in]   direccion    Direccion en la que se movero la serpiente
 * @param[in]   ateFood      Booleano que indica si la serpiente comeroa o no al
 * realizar el movimiento
 *
 * @note Esta funcion llama a initSnake e initTablero para inicializarlo.
 */
void inicializar_juego(Snake *serpiente, Tablero *tablero, uint16_t *puntuacion,
                       enum joystick_dir *direccion_actual,
                       bool *juego_terminado);

/**
 * @brief   Genera una fruta en una posicion aleatoria del tablero.
 *
 * @param[in]		snake      	 Direccion de la serpiente
 * @param[in]   tablero   	 Direccion del tablero
 *
 */
void generar_comida(Snake *serpiente, Tablero *tab);

/**
 * @brief   Lee la entrada del joystick
 *
 * @param[in]		direccion_actual     Direccion de la variable que guarda
 * la direccion actual de la serpiente.
 *
 * @note Modifica el valor apuntado por direccion_actual
 */
void procesar_entrada(enum joystick_dir *direccion_actual);

/**
 * @brief   Convierte la entrada del joystick a direcciones en forma de puntos
 * (x,y).
 *
 * @param[in]		direccion_actual      Direccion actual de la serpiente
 *
 *
 * @return Devuelve la direccion del joystick
 */
Punto trans_joy_to_point(enum joystick_dir direccion_actual);

/**
 * @brief  Actualiza el juego, tanto el moviemiento de la serpiente como la
 * generacion de frutas.
 *
 * @param[in]		serpiente    			 Direccion de la
 * serpiente
 * @param[in]		tab Direccion del tablero
 * @param[in]		puntuacion    	   Direccion de la puntuacion del juego
 * @param[in]		direccion     	 	 Direccion a la que se movera la
 * serpiente
 * @param[in]		juego_terminado    Indica si el juego ha terminado o no
 *
 */
void actualizar_logica(Snake *serpiente, Tablero *tab, uint16_t *puntuacion,
                       Punto direccion, bool *juego_terminado);

/**
 * @brief  Pinta en la pantalla LCD el tablero y la puntuacion.
 *
 * @param[in]		serpiente    			 Direccion de la
 * serpiente
 * @param[in]		tab                Direccion del tablero
 * @param[in]		puntuacion    	   Direccion de la puntuacion del juego
 * @param[in]		direccion_actual   Direccion a la que se movera la
 * serpiente
 *
 */
void renderizar(Snake *serpiente, Tablero *tab, uint16_t *puntuacion,
                enum joystick_dir *direccion_actual);

/**
 * @brief  Pinta en la pantalla LCD la serpiente y las frutas.
 *
 * @param[in]		serpiente    			 Direccion de la
 * serpiente
 * @param[in]		tab                Direccion del tablero
 * @param[in]		puntuacion    	   Direccion de la puntuacion del juego
 * @param[in]		direccion_actual   Direccion a la que se movera la
 * serpiente
 *
 * @note Esta funcion se ejecuta cada iteracion del bucle del juego
 */
void renderizarBucle(Snake *snake, Tablero *tab, uint16_t *puntuacion,
                     enum joystick_dir *direccion_actual);

/**
 * @brief  Muestra en la pantalla LCD un texto de victoria junto a la puntuacion
 * conseguida.
 *
 * @param[in]		puntuacion    	   Direccion de la puntuacion del juego
 *
 */
void pantalla_victoria(uint16_t *puntuacion);

/**
 * @brief  Muestra en la pantalla LCD un texto de derrota junto a la puntuacion
 * conseguida.
 *
 * @param[in]		puntuacion    	   Direccion de la puntuacion del juego
 *
 */
void pantalla_derrota(uint16_t *puntuacion);

/**
 * @brief  Muestra en la pantalla LCD un texto para preguntar si empezar otra
 * partida o no.
 *
 */
void pantalla_continuar();
void pantalla_iniciar();

/**
 * @brief  Pinta en la pantalla LCD el cuerpo de la serpiente, representado
 * por un cuadrado.
 *
 * @param[in]		x    	   	   Coordenada x del tablero
 * @param[in]		y    	       Coordenada y del tablero
 * @param[in]		color    	   Color del cuadrado
 *
 */
void dibujar_cuerpo(uint8_t x, uint8_t y, uint16_t color);

/**
 * @brief  Pinta en la pantalla LCD la cabeza de la serpiente, representada por
 * una flecha.
 *
 * @param[in]		x    	   	   Coordenada x del tablero
 * @param[in]		y    	       Coordenada y del tablero
 * @param[in]		dir    	     Direccion actual de la serpiente
 * @param[in]		color    	   Color de la flecha
 *
 * @note La direccion de flecha dependera de la direccion de la serpiente
 *
 */
void dibujar_cabeza_flecha(uint8_t x, uint8_t y, enum joystick_dir dir,
                           uint16_t color);

/**
 * @brief  Pinta en la pantalla LCD una fruta, representada por un circulo
 *
 * @param[in]		x    	   	   Coordenada x del tablero
 * @param[in]		y    	       Coordenada y del tablero
 * @param[in]		color    	   Color de la fruta
 *
 */
void dibujar_fruta(uint8_t x, uint8_t y, uint16_t color);

#endif // SNAKE_H