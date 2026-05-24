#include "glcd.h"
#include "uart_lpc40xx.h"
#include "snake.h"
#include <stdlib.h>


void pintar_tablero()
{
	glcd_inicializar();
	glcd_borrar(AZUL);

	glcd_xprintf(4,4, WHITE, BLUE, 0, "Puntuación: ");
	
	glcd_linea(11, 31, N+1, 31, WHITE);
	glcd_linea(N+1, 31, N+1, M+1, WHITE);
	glcd_linea(N+1, M+1, 11, M+1, WHITE);
	glcd_linea(11, M+1, 11, 31, WHITE);
	
	glcd_linea(9, 29, N+3, 29, WHITE);
	glcd_linea(N+3, 29, N+3, M+3, WHITE);
	glcd_linea(N+3, M+3, 9, M+3, WHITE);
	glcd_linea(9, M+3, 9, 29, WHITE);
	
	glcd_rectangulo_relleno(12,32,44,64,GREEN);
}


// ENQUEUE: Añade la nueva cabeza al final (Rear)
void enqueue(SnakeQueue *snake, Punto newHead) {
    if (snake->size == MAX_SNAKE_LENGTH) {
        // La serpiente alcanzó el tamaño máximo (¡Ganaste el juego!)
        return; 
    }

    // Avanzamos el 'rear' de forma circular
    snake->rear = (snake->rear + 1) % MAX_SNAKE_LENGTH;
    
    // Guardamos la nueva posición
    snake->body[snake->rear] = newHead;
    
    // Incrementamos el tamaño actual de la serpiente
    snake->size++;
}

// DEQUEUE: Elimina la punta de la cola al frente (Front)
Punto dequeue(SnakeQueue *snake) {
    // Guardamos el punto que va a salir (útil para saber qué pixel borrar en pantalla)
    Punto removedPoint = snake->body[snake->front];

    // Avanzamos el 'front' de forma circular
    snake->front = (snake->front + 1) % MAX_SNAKE_LENGTH;
    
    // Reducimos el tamaño
    snake->size--;

    return removedPoint;
}


void moveSnake(SnakeQueue *snake, Punto nextHead, bool ateFood) {
	
    enqueue(snake, nextHead);
	
    // Pintar nueva cabeza
    // ------------------------------------------------

    if (!ateFood) {
        // Si no comió, sacamos el último trozo de cola...
        Point tailToClear = dequeue(snake);
        // Borrar cola 
				// ------------------------------------------------
        drawCharacter(tailToClear.x, tailToClear.y, ' ');
    } else {
        // Si comió, NO hacemos dequeue. La serpiente crece y la manzana desaparece.
        generateNewFood();
    }
}
