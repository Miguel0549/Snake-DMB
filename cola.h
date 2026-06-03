#ifndef COLA_H
#define COLA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
 
 
/**
 * @brief   Estructura para guardar un punto (x,y) del tablero.
 *
 */ 
typedef struct {
    uint8_t x; 
    uint8_t y; 
} Punto;



/**
 * @brief   Estructura de cada elemento de la cola.
 *
 */
typedef struct tNodo{
    Punto valor;
    struct tNodo* sig;
}Nodo;
 


/**
 * @brief   Estructura de la cola.
 *
 */
typedef struct tCola{
    int tamano;
    Nodo* frontal;
    Nodo* final;
}Cola;




/**
 * @brief   Convierte las coordenadas x e y del tablero a una estructura Punto(x,y).
 *
 * @param[in]		x      Coordenada x del tablero
 * @param[in]		y      Coordenada y del tablero
 *
 * @return Devuelve el punto dado por las coordenadas x e y.
 */
Punto constructorPunto(uint8_t x, uint8_t y);




/**
 * @brief   Suma dos puntos.
 *
 * @param[in]		a      Punto a 
 * @param[in]		b      Punto b
 *
 * @return Devuelve la suma de los dos puntos (x1+x2,y1+y2).
 */
Punto sumarPuntos(Punto a, Punto b);
 
 
 
/**
 * @brief   Crea un nuevo elemento de la cola.
 *
 * @param[in]		valor      Punto(x,y) asociado al nuevo elemento.
 *
 * @return Devuelve un puntero al nuevo elemento.
 */ 
Nodo* crearNodo(Punto valor);
 


/**
 * @brief   Crea la cola
 *
 * @return Devuelve un puntero a la misma.
 */
Cola* crearColas();



/**
 * @brief   Mete al final de la cola el nodo dado.
 *
 * @param[in]		n      Puntero a la cola
 * @param[in]		nodo   Puntero al nodo a encolar.
 *
 */
void Encolar(Cola* n,Nodo* nodo);


/**
 * @brief   Saca el primer nodo de la cola
 *
 * @param[in]		n      Puntero a la cola
 *
 */
Punto Desencolar(Cola* n);








#endif