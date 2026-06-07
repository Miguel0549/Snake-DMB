/**
 * @file    cola.h
 * @brief   Tipos de datos necesarios para el snake. Adaptación de la cola de c++ a c usando memoria dinámica. Es importante tener activada esta memoria en el kit.
 *
 * @author  Miguel López Rodríguez | Miguel Catalá Garrido
 * @date    2026
 */

#ifndef COLA_H
#define COLA_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 	Estructura de punto de coordenadas para guardar posiciones en el tablero y direcciones
 */
typedef struct {
  uint8_t x;
  uint8_t y;
} Punto;

/**
 * @brief 	Nodo de la cola enlazada
 */
typedef struct tNodo {
  Punto valor;
  struct tNodo *sig;
} Nodo;

/**
 * @brief 	Cola enlazada con memoria dinámica
 */
typedef struct tCola {
  int tamano;
  Nodo *frontal;
  Nodo *final;
} Cola;

// ===== COLA - Funciones Publicas =====
Punto constructorPunto(uint8_t x, uint8_t y);

Punto sumarPuntos(Punto a, Punto b);

Nodo *crearNodo(Punto valor);

Cola *crearColas();

void Encolar(Cola *n, Nodo *nodo);

Punto Desencolar(Cola *n);

#endif