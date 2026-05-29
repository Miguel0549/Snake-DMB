#include "snake.h"
#include <stdlib.h>

void enqueue(SnakeQueue *snake, Punto newHead) {
    if (snake->size == MAX_SNAKE_LENGTH) return; 
    snake->rear = newHead;
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

void initTablero(SnakeQueue *snake, Tablero* tablero) {
	
		for( int i=0 ; i<7 ; ++i ){
			for ( int j=0 ; j<14 ; j++ ){
					tablero->t[i][j] = 0;
			}
		}
	
		tablero->t[snake->front.x][snake->front.y] = -1;
		tablero->t[snake->rear.x][snake->rear.y] = -1;
		
    snake->front = (Punto){2, 3};
    snake->rear = (Punto){3, 3};
    snake->size = 0;
}

void inicializar_juego(SnakeQueue* serpiente,Tablero* tablero, Punto* comida, uint16_t* puntuacion,enum joystick_dir *direccion_actual, bool* juego_terminado) {
    puntuacion = 0;
    juego_terminado = false;
    *direccion_actual = JOYSTICK_DERECHA; 
    
    initTablero(serpiente); //
    
    // Forzar vaciado de seguridad de la cola circular
    serpiente->front = 0;
    serpiente->rear = -1;
    serpiente->size = 0;

    // Insertar cuerpo inicial en una zona segura
    Punto p1 = {3, 3};
    Punto p2 = {4, 3};
    Punto p3 = {5, 3}; // Cabeza inicial
    enqueue(serpiente, p1); //
    enqueue(serpiente, p2); //
    enqueue(serpiente, p3); //

    //generar_comida(comida,serpiente);
}

void generar_comida(Punto* comida,SnakeQueue* serpiente) {
    bool posicion_valida = false;
    while (!posicion_valida) {
        comida->x = rand() % COLUMNAS;
        comida->y = rand() % FILAS;

        posicion_valida = true;
        int idx = serpiente->front;
        for (int i = 0; i < serpiente->size; i++) {
            if (serpiente->body[idx].x == comida->x && serpiente->body[idx].y == comida->y) {
                posicion_valida = false;
                break;
            }
            idx = (idx + 1) % MAX_SNAKE_LENGTH; //
        }
    }
}

void procesar_entrada(enum joystick_dir *direccion_actual) {
    uint8_t tecla = joystick_leer();
    
    if (tecla == JOYSTICK_ARRIBA && *direccion_actual != JOYSTICK_ABAJO)     *direccion_actual = JOYSTICK_ARRIBA;
    if (tecla == JOYSTICK_ABAJO && *direccion_actual != JOYSTICK_ARRIBA)     *direccion_actual = JOYSTICK_ABAJO;
    if (tecla == JOYSTICK_IZQUIERDA && *direccion_actual != JOYSTICK_DERECHA) *direccion_actual = JOYSTICK_IZQUIERDA;
    if (tecla == JOYSTICK_DERECHA && *direccion_actual != JOYSTICK_IZQUIERDA) *direccion_actual = JOYSTICK_DERECHA;
}

void actualizar_logica(SnakeQueue* serpiente, Punto* comida, uint16_t* puntuacion,enum joystick_dir *direccion_actual, bool* juego_terminado ) {
    Punto cabeza_actual = serpiente->body[serpiente->rear];
    Punto siguiente_cabeza = cabeza_actual;

    switch (*direccion_actual) {
        case JOYSTICK_ARRIBA:    siguiente_cabeza.y--; break;
        case JOYSTICK_ABAJO:     siguiente_cabeza.y++; break;
        case JOYSTICK_IZQUIERDA: siguiente_cabeza.x--; break;
        case JOYSTICK_DERECHA:   siguiente_cabeza.x++; break;
        default: break;
    }

    if (siguiente_cabeza.x < 0 || siguiente_cabeza.x >= COLUMNAS ||
        siguiente_cabeza.y < 0 || siguiente_cabeza.y >= FILAS) {
        *juego_terminado = true;
        return;
    }

    if (verificarColisionCuerpo(serpiente, siguiente_cabeza)) { //
        *juego_terminado = true;
        return;
    }

    bool ha_comido = (siguiente_cabeza.x == comida->x && siguiente_cabeza.y == comida->y);
    moveSnake(serpiente, siguiente_cabeza, ha_comido); //

    if (ha_comido) {
        *puntuacion += 10;
        //generar_comida(comida,serpiente);
    }
}

void renderizar(SnakeQueue* serpiente, Punto* comida, uint16_t* puntuacion,enum joystick_dir *direccion_actual) {
    glcd_borrar(NEGRO); //

    // 1. Cabecera gráfica
    glcd_xprintf(OFFSET_X, 8, AMARILLO, NEGRO, FUENTE8X16, "SCORE: %05d", *puntuacion); //
    glcd_rectangulo(OFFSET_X - 1, OFFSET_Y - 1, OFFSET_X + (COLUMNAS * TAM_BLOQUE), OFFSET_Y + (FILAS * TAM_BLOQUE), CIAN_OSCURO); //
    
    // Comida
    int comida_centro_x = OFFSET_X + (comida->x * TAM_BLOQUE) + (TAM_BLOQUE / 2);
    int comida_centro_y = OFFSET_Y + (comida->y * TAM_BLOQUE) + (TAM_BLOQUE / 2);
    glcd_circulo(comida_centro_x, comida_centro_y, (TAM_BLOQUE / 2) - 4, ROJO); //

    // 2. Recorrer y renderizar la serpiente
    int idx = serpiente->front;
    for (int i = 0; i < serpiente->size; i++) {
        if (idx == serpiente->rear) {
            // Es la cabeza: Dibujamos la Flecha Vectorial orientada
            dibujar_cabeza_flecha(serpiente->body[idx].x, serpiente->body[idx].y, *direccion_actual, OLIVA);
        } else {
            // Es el cuerpo: Dibujamos un Bloque Cuadrado relleno
            dibujar_cuerpo(serpiente->body[idx].x, serpiente->body[idx].y, VERDE);
        }
        idx = (idx + 1) % MAX_SNAKE_LENGTH; //
    }
}

// Dibuja el cuerpo como un cuadrado regular relleno
void dibujar_cuerpo(uint8_t x, uint8_t y, uint16_t color) {
    int x0 = OFFSET_X + (x * TAM_BLOQUE) + 2; 
    int y0 = OFFSET_Y + (y * TAM_BLOQUE) + 2;
    int x1 = x0 + TAM_BLOQUE - 4;
    int y1 = y0 + TAM_BLOQUE - 4;
    glcd_rectangulo_relleno(x0, y0, x1, y1, color); //
}

// Dibuja la cabeza como una punta de flecha (Triángulo apuntando a la dirección del movimiento)
void dibujar_cabeza_flecha(uint8_t x, uint8_t y, enum joystick_dir dir, uint16_t color) {
    // Calcular la caja del bloque actual
    int bx = OFFSET_X + (x * TAM_BLOQUE);
    int by = OFFSET_Y + (y * TAM_BLOQUE);

    int x_centro = bx + (TAM_BLOQUE / 2);
    int y_centro = by + (TAM_BLOQUE / 2);

    // Vértices del triángulo de la flecha
    int px1, py1, px2, py2, px3, py3;

    switch (dir) {
        case JOYSTICK_ARRIBA:
            px1 = x_centro;                  py1 = by + 4;                  // Punta superior
            px2 = bx + 6;                    py2 = by + TAM_BLOQUE - 6;     // Esquina inferior izq
            px3 = bx + TAM_BLOQUE - 6;       py2 = by + TAM_BLOQUE - 6;     // Esquina inferior der
            py3 = py2;
            break;
        case JOYSTICK_ABAJO:
            px1 = x_centro;                  py1 = by + TAM_BLOQUE - 4;     // Punta inferior
            px2 = bx + 6;                    py2 = by + 6;                  // Esquina superior izq
            px3 = bx + TAM_BLOQUE - 6;       py3 = by + 6;
            py2 = py3;
            break;
        case JOYSTICK_IZQUIERDA:
            px1 = bx + 4;                    py1 = y_centro;                // Punta izquierda
            px2 = bx + TAM_BLOQUE - 6;       py2 = by + 6;                  // Esquina superior der
            px3 = bx + TAM_BLOQUE - 6;       py3 = by + TAM_BLOQUE - 6;     // Esquina inferior der
            break;
        case JOYSTICK_DERECHA:
        default:
            px1 = bx + TAM_BLOQUE - 4;       py1 = y_centro;                // Punta derecha
            px2 = bx + 6;                    py2 = by + 6;                  // Esquina superior izq
            px3 = bx + 6;                    py3 = by + TAM_BLOQUE - 6;     // Esquina inferior izq
            break;
    }

    // Dibujar el contorno y silueta de la flecha mediante líneas vectoriales
    glcd_linea(px1, py1, px2, py2, color); //
    glcd_linea(px2, py2, px3, py3, color); //
    glcd_linea(px3, py3, px1, py1, color); //

    // Dibujar un pequeño núcleo central relleno para darle robustez visual a la flecha
    glcd_rectangulo_relleno(x_centro - 2, y_centro - 2, x_centro + 2, y_centro + 2, color); //
}