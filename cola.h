#ifndef COLA_H
#define COLA_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t x;
  uint8_t y;
} Punto;

typedef struct tNodo {
  Punto valor;
  struct tNodo *sig;
} Nodo;

typedef struct tCola {
  int tamano;
  Nodo *frontal;
  Nodo *final;
} Cola;

Punto constructorPunto(uint8_t x, uint8_t y);

Punto sumarPuntos(Punto a, Punto b);

Nodo *crearNodo(Punto valor);

Cola *crearColas();

void Encolar(Cola *n, Nodo *nodo);

Punto Desencolar(Cola *n);

#endif