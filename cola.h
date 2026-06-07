/**
 * @file    cola.h
 * @brief   
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
 * @brief 
 */
typedef struct {
  uint8_t x;
  uint8_t y;
} Punto;

/**
 * @brief 
 */
typedef struct tNodo {
  Punto valor;
  struct tNodo *sig;
} Nodo;

/**
 * @brief 
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