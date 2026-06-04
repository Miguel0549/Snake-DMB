#include "cola.h"
#include <stdlib.h>

Punto constructorPunto(uint8_t x, uint8_t y) {
  Punto p;
  p.x = x;
  p.y = y;
  return p;
}

Nodo *crearNodo(Punto valor) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->valor = valor;
  nodo->sig = NULL;
  return nodo;
}

Cola *crearColas() {
  Cola *n = (Cola *)malloc(sizeof(Cola));
  n->tamano = 0;
  n->frontal = NULL;
  n->final = NULL;
  return n;
}

void Encolar(Cola *n, Nodo *nodo) {
  if (n->frontal == NULL)
    n->frontal = nodo;
  else
    n->final->sig = nodo;
  n->final = nodo;
  n->tamano++;
}

Punto Desencolar(Cola *n) {
  if (n->tamano) {
    Punto returnValue;
    Nodo *aux = n->frontal;
    returnValue = aux->valor;
    n->frontal = n->frontal->sig;
    free(aux);
    n->tamano--;
    return returnValue;
  }
  Punto p = constructorPunto(-1, -1);
  return p; // Indicador de que no hay elementos
}

Punto sumarPuntos(Punto a, Punto b) {
  Punto c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return c;
}