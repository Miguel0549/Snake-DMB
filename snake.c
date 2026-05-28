#include "snake.h"

void enqueue(SnakeQueue *snake, Punto newHead) {
    if (snake->size == MAX_SNAKE_LENGTH) return; 
    snake->rear = (snake->rear + 1) % MAX_SNAKE_LENGTH;
    snake->body[snake->rear] = newHead;
    snake->size++;
}

Punto dequeue(SnakeQueue *snake) {
    Punto removedPoint = snake->body[snake->front];
    snake->front = (snake->front + 1) % MAX_SNAKE_LENGTH;
    snake->size--;
    return removedPoint;
}

void moveSnake(SnakeQueue *snake, Punto nextHead, bool ateFood) {
    enqueue(snake, nextHead);
    if (!ateFood) {
        dequeue(snake);
    }
}

bool verificarColisionCuerpo(SnakeQueue *snake, Punto punto) {
    if (snake->size <= 4) return false;
    int idx = snake->front;
    for (int i = 0; i < snake->size - 1; i++) {
        if (snake->body[idx].x == punto.x && snake->body[idx].y == punto.y) {
            return true;
        }
        idx = (idx + 1) % MAX_SNAKE_LENGTH;
    }
    return false;
}


void initSnake(SnakeQueue *snake) {
    snake->front = 0;
    snake->rear = -1;
    snake->size = 0;

    enqueue(snake, (Punto){2, 3}); 
    enqueue(snake, (Punto){3, 3}); 
    enqueue(snake, (Punto){4, 3}); 
}