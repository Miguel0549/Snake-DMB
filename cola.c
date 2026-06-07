/**
 * @file    cola.c
 * @brief   
 *
 * @author  Miguel López Rodríguez | Miguel Catalá Garrido
 * @date    2026
 */

#include "cola.h"
#include <stdlib.h>

/**
 * @brief   
 * @ingroup COLA
 *
 * @param[in] x 
 * @param[in] y 
 *
 * @return  
 */
Punto constructorPunto(uint8_t x, uint8_t y) {
  Punto p;
  p.x = x;
  p.y = y;
  return p;
}

/**
 * @brief   
 * @ingroup COLA
 *
 * @param[in] valor 
 *
 * @return  
 */
Nodo *crearNodo(Punto valor) {
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->valor = valor;
  nodo->sig = NULL;
  return nodo;
}

/**
 * @brief   
 * @ingroup COLA
 *
 * @return  
 */
Cola *crearColas() {
  Cola *n = (Cola *)malloc(sizeof(Cola));
  n->tamano = 0;
  n->frontal = NULL;
  n->final = NULL;
  return n;
}

/**
 * @brief   
 * @ingroup COLA
 *
 * @param[in,out] n    
 * @param[in]     nodo 
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
 * @brief   
 * @ingroup COLA
 *
 * @param[in,out] n 
 *
 * @return  
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
 * @brief   
 * @ingroup COLA
 *
 * @param[in] a 
 * @param[in] b 
 *
 * @return  
 */
Punto sumarPuntos(Punto a, Punto b) {
  Punto c;
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  return c;
}