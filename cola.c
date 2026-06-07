/**
 * @file    cola.c
 * @brief   Tipos de datos necesarios para el snake. Adaptación de la cola de c++ a c usando memoria dinámica. Es importante tener activada esta memoria en el kit.
 *
 * @author  Miguel López Rodríguez | Miguel Catalá Garrido
 * @date    2026
 */

#include "cola.h"
#include <stdlib.h>

/**
 * @brief   Devuelve un punto con un valor x y uno y para inicializar otros
 * @ingroup COLA
 *
 * @param[in] x Posición x para el punto
 * @param[in] y Posición y para el punto
 *
 * @return  Punto inicializado
 */
Punto constructorPunto(uint8_t x, uint8_t y) {
  Punto p;
  p.x = x;
  p.y = y;
  return p;
}

/**
 * @brief   Creas un nodo para la cola
 * @ingroup COLA
 *
 * @param[in] valor Punto usado como valor del nodo
 *
 * @return  Nodo generado para la cola
 */
Nodo *crearNodo(Punto valor) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->valor = valor;
  nodo->sig = NULL;
  return nodo;
}

/**
 * @brief   Inicializa la cola, la memoria y los punteros
 * @ingroup COLA
 *
 * @return  La cola ya inicializada
 */
Cola *crearColas() {
  Cola *n = (Cola *)malloc(sizeof(Cola));
  n->tamano = 0;
  n->frontal = NULL;
  n->final = NULL;
  return n;
}

/**
 * @brief   Inserta nodo en la cola, push
 * @ingroup COLA
 *
 * @param[in,out] n    	Puntero de la cola
 * @param[in]     nodo 	Puntero del nodo
 */
void Encolar(Cola *n, Nodo *nodo) {
  if (n->frontal == NULL)
    n->frontal = nodo;
  else
    n->final->sig = nodo;
  n->final = nodo;
  n->tamano++;
}

/**
 * @brief   Saca el primer nodo de la cola, pop
 * @ingroup COLA
 *
 * @param[in,out] n Puntero de la cola
 *
 * @return El valor del nodo
 */
Punto Desencolar(Cola *n) {
  if (n->tamano) { // Si el tamaño no es 0
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

/**
 * @brief   Devuelve la suma de dos puntos
 * @ingroup COLA
 *
 * @param[in] a Primer punto a sumar
 * @param[in] b Segundo punto a sumar
 *
 * @return  El punto (a.x + b.x, a.y + b.y)
 */
Punto sumarPuntos(Punto a, Punto b) {
  Punto c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return c;
}