/**
 * @file    snake.c
 * @brief   Macros y funciones para jugar al snake en el LPC4088 Developer's Kit con joystick y la pantalla del kit
 *
 * @author  Miguel López Rodríguez | Miguel Catalá Garrido
 * @date    2026
 */

#include "snake.h"
#include <stdlib.h>

/**
 * @brief   Inicializa la serpiente, su posición, tamaño y futuros movimientos de la cola
 * @ingroup SNAKE
 *
 * @param[in,out] serpi			Puntero a la serpiente para inicializarla
 */
void initSnake(Snake *serpi) {

  serpi->cabeza = constructorPunto(3, 1);
  serpi->final = constructorPunto(1, 1);
  serpi->movs_pendientes = crearColas();
  Encolar(serpi->movs_pendientes, crearNodo(constructorPunto(1, 0)));
  Encolar(serpi->movs_pendientes, crearNodo(constructorPunto(1, 0)));
  serpi->tama = 3;
}

/**
 * @brief   Una vez se ha confirmado que se puede mover, se actualiza el tablero y la serpiente con sus nuevas posiciones
 * @ingroup SNAKE
 *
 * @param[in,out] snake     Puntero a la serpiente para moverla
 * @param[in,out] tab       Puntero al tablero para que tenga la nueva posición de la serpiente
 * @param[in]     direccion Dirección en la que se tendrá que mover la serpiente
 * @param[in]     ateFood   Bandera que indica si mover la cola o no en base a haber comido fruta este ciclo
 */
void moveSnake(Snake *snake, Tablero *tab, Punto direccion, bool ateFood) {
  snake->cabeza = sumarPuntos(snake->cabeza, direccion);
  if (!ateFood) {
    tab->t[snake->final.x][snake->final.y] = VACIA;
    snake->final =
        sumarPuntos(snake->final, Desencolar(snake->movs_pendientes));
  }
  Encolar(snake->movs_pendientes, crearNodo(direccion));
  tab->t[snake->cabeza.x][snake->cabeza.y] = SERPIENTE;
}

/**
 * @brief   Comprueba que la serpiente no se vaya a chocar con nada en el siguiente ciclo, eso incluye los bordes de la pantalla y a si misma
 * @ingroup SNAKE
 *
 * @param[in] snake       Serpiente para comprobar si la nueva posición sería donde está ahora su cola, lo cual sería posición válida 
 * porque la cola dejaría paso a la cabeza
 * @param[in] nuevaCabeza Posición del siguiente ciclo para comprobar las colisiones
 * @param[in] tab         Tablero para comprobar que hay en la nueva posición
 *
 * @return  
 */
bool verificarColisionCuerpo(Snake *snake, Punto nuevaCabeza, Tablero *tab) {
  if (nuevaCabeza.x == snake->final.x && nuevaCabeza.y == snake->final.y)
    return false;
  if (nuevaCabeza.x < 0 || nuevaCabeza.y < 0 || nuevaCabeza.x > 13 ||
      nuevaCabeza.y > 6) {
    return true;
  } else if (tab->t[nuevaCabeza.x][nuevaCabeza.y] == SERPIENTE)
    return true;
  return false;
}

/**
 * @brief   Inicializar todas las posiciones del tablero, incluyendo las de la serpiente y la generación de las frutas
 * @ingroup SNAKE
 *
 * @param[in]     snake Serpiente para la función de las frutas
 * @param[in,out] tab   Puntero al tablero a inicializar
 */
void initTablero(Snake *snake, Tablero *tab) {

  for (int i = 0; i < 14; ++i) {
    for (int j = 0; j < 7; j++) {
      tab->t[i][j] = VACIA;
    }
  }

  tab->t[1][1] = SERPIENTE;
  tab->t[2][1] = SERPIENTE;
  tab->t[3][1] = SERPIENTE;

  generar_comida(snake, tab);
  generar_comida(snake, tab);
  generar_comida(snake, tab);
}

/**
 * @brief   Inicializa todo el juego, incluyendo la serpiente, el tablero, los puntos, la última dirección elegida y la bandera de juego terminado
 * @ingroup SNAKE
 *
 * @param[in,out] serpiente        Puntero a la serpiente para inicializarla y usarla en la función del tablero
 * @param[out] tablero          	 Puntero al tablero para inicializarlo
 * @param[out] puntuacion       	 Puntero a la puntuación para inicializarla a 0
 * @param[out] direccion_actual 	 Puntero a la última dirección jugada para forzarla a derecha
 * @param[out] juego_terminado  	 Puntero a la bandera de juego terminado, que como acaba de empezar se pone a false
 */
void inicializar_juego(Snake *serpiente, Tablero *tablero, uint16_t *puntuacion,
                       enum joystick_dir *direccion_actual,
                       bool *juego_terminado) {
  *puntuacion = 0;

  juego_terminado = false;
  *direccion_actual = JOYSTICK_DERECHA;

	initSnake(serpiente);
  initTablero(serpiente, tablero);
}

/**
 * @brief   Generador aleatorio de comidas en el tablero. 
 * Queda como responsabilidad del programador llamar a srand antes que a esta función para generar una semilla como quiera
 * @ingroup SNAKE
 *
 * @param[in]     serpiente 	Puntero a la serpiente para ver según su tamaño si hay espacio para generar más frutas
 * @param[in,out] tab       	Puntero al tablero para ver si la posición generada está vacía y poner ahí la fruta
 */
void generar_comida(Snake *serpiente, Tablero *tab) {
  if (tab->n_frutas == MAX_SNAKE_LENGTH - serpiente->tama)
    return;

  Punto p = constructorPunto(rand() % FILAS, rand() % COLUMNAS);
  while (tab->t[p.x][p.y] != VACIA) {
    p.x = rand() % FILAS;
    p.y = rand() % COLUMNAS;
  }
  tab->t[p.x][p.y] = FRUTA;
  tab->n_frutas++;
}

/**
 * @brief   Lee el joystick y devuelve un valor dependiente del anterior, dado que la serpiente no puede darse media vuelta nunca
 * @ingroup SNAKE
 *
 * @param[in,out] direccion_actual 	Puntero a la última dirección elegida para comparar y si se puede actualizarla la recién leída
 */
void procesar_entrada(enum joystick_dir *direccion_actual) {
  uint8_t tecla = joystick_leer2();

  if (tecla == JOYSTICK_ARRIBA && *direccion_actual != JOYSTICK_ABAJO) {
    *direccion_actual = JOYSTICK_ARRIBA;
  }
  if (tecla == JOYSTICK_ABAJO && *direccion_actual != JOYSTICK_ARRIBA) {
    *direccion_actual = JOYSTICK_ABAJO;
  }
  if (tecla == JOYSTICK_IZQUIERDA && *direccion_actual != JOYSTICK_DERECHA) {
    *direccion_actual = JOYSTICK_IZQUIERDA;
  }
  if (tecla == JOYSTICK_DERECHA && *direccion_actual != JOYSTICK_IZQUIERDA) {
    *direccion_actual = JOYSTICK_DERECHA;
  }
}

/**
 * @brief   Transforma las direcciones del joycon en puntos, para poder sumar estos como direcciones y trabajar las funciones de movimiento
 * @ingroup SNAKE
 *
 * @param[in] direccion_actual 
 *
 * @retval   0,-1 si la dirección es arriba.
 * @retval   0, 1 si la dirección es abajo.
 * @retval  -1, 0 si la dirección es izquierda.
 * @retval   1, 0 si la dirección es derecha.
 * @retval   1, 0 si la dirección es cualquier otra, por seguridad.
 */
Punto trans_joy_to_point(enum joystick_dir direccion_actual) {
  Punto p;
  switch (direccion_actual) {
  case JOYSTICK_ARRIBA:
    p = constructorPunto(0, -1);
    break;
  case JOYSTICK_ABAJO:
    p = constructorPunto(0, 1);
    break;
  case JOYSTICK_IZQUIERDA:
    p = constructorPunto(-1, 0);
    break;
  case JOYSTICK_DERECHA:
    p = constructorPunto(1, 0);
    break;
  default:
    p = constructorPunto(1, 0);
    break;
  }
  return p;
}

/**
 * @brief   Avanzar en un ciclo la lógica de la partida
 * @ingroup SNAKE
 *
 * @param[in,out] serpiente      	Puntero a la serpiente
 * @param[in,out] tab             Puntero al tablero 
 * @param[in,out] puntuacion      Puntero a la puntuación
 * @param[in]     direccion       Dirección en la que pretende moverse la serpiente este ciclo
 * @param[out]    juego_terminado Puntero a la bandera de juego terminado
 */
void actualizar_logica(Snake *serpiente, Tablero *tab, uint16_t *puntuacion,
                       Punto direccion, bool *juego_terminado) {
  Punto siguiente_cabeza = sumarPuntos(serpiente->cabeza, direccion);

  if (verificarColisionCuerpo(serpiente, siguiente_cabeza, tab) ||
      serpiente->tama == MAX_SNAKE_LENGTH) { //
    *juego_terminado = true;
    return;
  }

  bool ha_comido = (tab->t[siguiente_cabeza.x][siguiente_cabeza.y] == FRUTA);
  moveSnake(serpiente, tab, direccion, ha_comido); //

  if (ha_comido) {
    *puntuacion += 20;
    generar_comida(serpiente, tab);
  }
}

/**
 * @brief   Imprime el escenario inicial por pantalla
 * @ingroup SNAKE
 *
 * @param[in] serpiente        Puntero a la serpiente
 * @param[in] tab              Puntero al tablero
 * @param[in] puntuacion       Puntero a la puntuación actual
 * @param[in] direccion_actual Dirección para la cabeza de la serpiente
 */
void renderizar(Snake *serpiente, Tablero *tab, uint16_t *puntuacion,
                enum joystick_dir *direccion_actual) {
  glcd_borrar(NEGRO);
  glcd_rectangulo(OFFSET_X - 1, OFFSET_Y - 1,
                  OFFSET_X + (FILAS * TAM_BLOQUE) + 1,
                  OFFSET_Y + (COLUMNAS * TAM_BLOQUE) + 1, CIAN_OSCURO); //

  renderizarBucle(serpiente, tab, puntuacion, direccion_actual);
}

/**
 * @brief   Imprime las partes que cambian cada ciclo del escenario, como el interior del tablero o el valor de la puntuación
 * @ingroup SNAKE
 *
 * @param[in] snake         		Puntero a la serpiente   
 * @param[in] tab              	Puntero al tablero
 * @param[in] puntuacion       	Puntero a la puntuación actual
 * @param[in] direccion_actual 	Dirección para la cabeza de la serpiente
 */
void renderizarBucle(Snake *snake, Tablero *tab, uint16_t *puntuacion,
                     enum joystick_dir *direccion_actual) {
  glcd_xprintf(OFFSET_X, 8, AMARILLO, NEGRO, FUENTE8X16, "SCORE: %05d",
               *puntuacion);
  glcd_rectangulo_relleno(OFFSET_X, OFFSET_Y, OFFSET_X + (FILAS * TAM_BLOQUE),
                          OFFSET_Y + (COLUMNAS * TAM_BLOQUE), NEGRO);
  for (int i = 0; i < 14; i++) {
    for (int j = 0; j < 7; j++) {
      if (tab->t[i][j] == SERPIENTE) {
        if (snake->cabeza.x == i && snake->cabeza.y == j) {
          dibujar_cabeza_flecha(i, j, *direccion_actual, OLIVA);
        } else {
          dibujar_cuerpo(i, j, OLIVA);
        }
      } else if (tab->t[i][j] == FRUTA) {
        dibujar_fruta(i, j, ROJO);
      }
    }
  }
}

/**
 * @brief   Imprime una celda del cuerpo de la serpiente
 * @ingroup SNAKE
 *
 * @param[in] x     Posición x en el tablero de la celda
 * @param[in] y     Posición y en el tablero de la celda
 * @param[in] color Color para imprimir el cuerpo
 */
void dibujar_cuerpo(uint8_t x, uint8_t y, uint16_t color) {
  int x0 = OFFSET_X + (x * TAM_BLOQUE) + 2;
  int y0 = OFFSET_Y + (y * TAM_BLOQUE) + 2;
  int x1 = x0 + TAM_BLOQUE - 4;
  int y1 = y0 + TAM_BLOQUE - 4;
  glcd_rectangulo_relleno(x0, y0, x1, y1, color); //
}

/**
 * @brief   Imprime la cabeza de la serpiente mirando en dirección correcta
 * @ingroup SNAKE
 *
 * @param[in] x     Posición x en el tablero de la cabeza
 * @param[in] y     Posición y en el tablero de la cabeza
 * @param[in] dir   Dirección para la cabeza
 * @param[in] color Color para imprimir la cabeza
 */
void dibujar_cabeza_flecha(uint8_t x, uint8_t y, enum joystick_dir dir,
                           uint16_t color) {
  int bx = OFFSET_X + (x * TAM_BLOQUE);
  int by = OFFSET_Y + (y * TAM_BLOQUE);

  int x_centro = bx + (TAM_BLOQUE / 2);
  int y_centro = by + (TAM_BLOQUE / 2);

  int px1, py1, px2, py2, px3, py3;

  switch (dir) {
  case JOYSTICK_ARRIBA:
    px1 = x_centro;
    py1 = by + 4; // Punta superior
    px2 = bx + 6;
    py2 = by + TAM_BLOQUE - 6; // Esquina inferior izq
    px3 = bx + TAM_BLOQUE - 6;
    py2 = by + TAM_BLOQUE - 6; // Esquina inferior der
    py3 = py2;
    break;
  case JOYSTICK_ABAJO:
    px1 = x_centro;
    py1 = by + TAM_BLOQUE - 4; // Punta inferior
    px2 = bx + 6;
    py2 = by + 6; // Esquina superior izq
    px3 = bx + TAM_BLOQUE - 6;
    py3 = by + 6;
    py2 = py3;
    break;
  case JOYSTICK_IZQUIERDA:
    px1 = bx + 4;
    py1 = y_centro; // Punta izquierda
    px2 = bx + TAM_BLOQUE - 6;
    py2 = by + 6; // Esquina superior der
    px3 = bx + TAM_BLOQUE - 6;
    py3 = by + TAM_BLOQUE - 6; // Esquina inferior der
    break;
  case JOYSTICK_DERECHA:
  default:
    px1 = bx + TAM_BLOQUE - 4;
    py1 = y_centro; // Punta derecha
    px2 = bx + 6;
    py2 = by + 6; // Esquina superior izq
    px3 = bx + 6;
    py3 = by + TAM_BLOQUE - 6; // Esquina inferior izq
    break;
  }

  glcd_linea(px1, py1, px2, py2, color);
  glcd_linea(px2, py2, px3, py3, color);
  glcd_linea(px3, py3, px1, py1, color);

  glcd_rectangulo_relleno(x_centro - 2, y_centro - 2, x_centro + 2,
                          y_centro + 2, color); // Ojo
}

/**
 * @brief   Imprime la fruta
 * @ingroup SNAKE
 *
 * @param[in] x     Posición x en el tablero de la fruta
 * @param[in] y     Posición y en el tablero de la fruta
 * @param[in] color Color para imprimir la fruta
 */
void dibujar_fruta(uint8_t x, uint8_t y, uint16_t color) {
  int comida_centro_x = OFFSET_X + (x * TAM_BLOQUE) + (TAM_BLOQUE / 2);
  int comida_centro_y = OFFSET_Y + (y * TAM_BLOQUE) + (TAM_BLOQUE / 2);
  glcd_circulo(comida_centro_x, comida_centro_y, (TAM_BLOQUE / 2) - 4, ROJO);
}

/**
 * @brief   Pantalla de victoria, llamar al ganar la partida
 * @ingroup SNAKE
 *
 * @param[in] puntuacion Puntero a la puntuación final de la partida
 */
void pantalla_victoria(uint16_t *puntuacion) {
  glcd_borrar(NEGRO);
  glcd_xprintf((OFFSET_X * 7 + (FILAS * TAM_BLOQUE) + 1) / 4,
               (OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4, VERDE, NEGRO,
               FUENTE16X32, "¡HAS GANADO!", *puntuacion);
  glcd_xprintf((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 4,
               ((OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4) + 64, AMARILLO, NEGRO,
               FUENTE12X24, "Tu puntuación: %05d", *puntuacion);
}

/**
 * @brief   Pantalla de derrota, llamar cuando pierdes la partida
 * @ingroup SNAKE
 *
 * @param[in] puntuacion Puntero a la puntuación final de la partida
 */
void pantalla_derrota(uint16_t *puntuacion) {
  glcd_borrar(NEGRO);
  glcd_xprintf((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 4,
               (OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4, ROJO, NEGRO,
               FUENTE16X32, "¡TE HAS CHOCADO!", *puntuacion);
  glcd_xprintf((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 4,
               ((OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4) + 64, AMARILLO, NEGRO,
               FUENTE12X24, "Tu puntuación: %05d", *puntuacion);
}

/**
 * @brief   Pantalla que te insta a continuar pulsando el botón central
 * @ingroup SNAKE
 */
void pantalla_continuar() {
  glcd_borrar(NEGRO);
  glcd_xprintf((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 4,
               (OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4, ROJO, NEGRO,
               FUENTE16X32, "¿Nueva partida?");
  glcd_xprintf((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 6,
               ((OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4) + 64, AMARILLO, NEGRO,
               FUENTE8X16, "Presiona el botón central para continuar");
}

/**
 * @brief   Pantalla de bienvenida al juego que te insta a pulsar el botón central para continuar
 * @ingroup SNAKE
 */
void pantalla_iniciar() {
  glcd_borrar(NEGRO);
  glcd_xprintf(((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 2) - 40,
               (OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4, OLIVA, NEGRO,
               FUENTE16X32, "SNAKE");
  glcd_xprintf((OFFSET_X + (FILAS * TAM_BLOQUE) + 1) / 6,
               ((OFFSET_Y + (COLUMNAS * TAM_BLOQUE)) / 4) + 64, AMARILLO, NEGRO,
               FUENTE8X16, "Presiona el botón central para continuar");
}