#include <time.h>
#include <windows.h>
#include "snake.h"

// ===== VARIABLES DE JUEGO =====
SnakeQueue serpiente;
Punto comida;
int puntuacion = 0;
enum joystick_dir direccion_actual = JOYSTICK_DERECHA; 
bool juego_terminado = false;

// ===== PROTOTIPOS =====
void inicializar_juego(void);
void generar_comida(void);
void procesar_entrada(void);
void actualizar_logica(void);
void renderizar(void);
void dibujar_cuerpo(int x, int y, uint16_t color);
void dibujar_cabeza_flecha(int x, int y, enum joystick_dir dir, uint16_t color);
void volcar_vram_a_consola(void);

int main(void) {
    setvbuf(stdout, NULL, _IONBF, 0);
    
    srand((unsigned int)time(NULL));
    glcd_inicializar();
    inicializar_juego();

    printf("Controles ultra-sensibles activados. Usa WASD o Flechas.\n");

    // Bucle principal de juego
    while (!juego_terminado) {
        
        // --- SISTEMA DE MICRO-MUESTREO ULTRA RÁPIDO ---
        // Queremos esperar ~250ms en total para el movimiento de la serpiente.
        // Si dividimos 250ms entre pausas diminutas de 2ms, ¡hacemos 125 revisiones por fotograma!
        for (int i = 0; i < 13; i++) {
            
            // Leemos el estado del teclado en este microsegundo
            uint8_t tecla_detectada = joystick_read(); 
            
            // IMPORTANTE: Solo actualizamos si el jugador REALMENTE presionó un botón.
            // Esto evita que el estado "JOYSTICK_NADA" borre tu último comando.
            if (tecla_detectada != JOYSTICK_NADA) {
                if (tecla_detectada == JOYSTICK_CENTRAL) {guardar_vram_a_imagen("partida_snake.ppm");}
                if (tecla_detectada == JOYSTICK_ARRIBA && direccion_actual != JOYSTICK_ABAJO)     direccion_actual = JOYSTICK_ARRIBA;
                if (tecla_detectada == JOYSTICK_ABAJO && direccion_actual != JOYSTICK_ARRIBA)     direccion_actual = JOYSTICK_ABAJO;
                if (tecla_detectada == JOYSTICK_IZQUIERDA && direccion_actual != JOYSTICK_DERECHA) direccion_actual = JOYSTICK_IZQUIERDA;
                if (tecla_detectada == JOYSTICK_DERECHA && direccion_actual != JOYSTICK_IZQUIERDA) direccion_actual = JOYSTICK_DERECHA;
            }
            
            #ifdef _WIN32
            // Forzamos a Windows a procesar las señales de la cola de entrada del sistema operativo
            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            #endif
            
            // Dormimos el hilo solo 2 milisegundos y volvemos a preguntar
            Sleep(2); 
        }
        // ----------------------------------------------

        // Una vez terminadas las 125 micro-revisiones, movemos físicamente el juego
        actualizar_logica();
        renderizar();
    }

    // Pantalla de Game Over
    system("cls");
    printf("=================================\n");
    printf("           GAME OVER             \n");
    printf("=================================\n");
    printf(" Puntuacion Final: %d Puntos\n", puntuacion);
    printf("=================================\n");
    printf("Presiona ENTER para salir...");
    
    fflush(stdin);
    getchar();

    return 0;
}

void inicializar_juego(void) {
    puntuacion = 0;
    juego_terminado = false;
    direccion_actual = JOYSTICK_DERECHA; 
    
    initSnake(&serpiente); //
    
    // Forzar vaciado de seguridad de la cola circular
    serpiente.front = 0;
    serpiente.rear = -1;
    serpiente.size = 0;

    // Insertar cuerpo inicial en una zona segura
    Punto p1 = {3, 3};
    Punto p2 = {4, 3};
    Punto p3 = {5, 3}; // Cabeza inicial
    enqueue(&serpiente, p1); //
    enqueue(&serpiente, p2); //
    enqueue(&serpiente, p3); //

    generar_comida();
}

void generar_comida(void) {
    bool posicion_valida = false;
    while (!posicion_valida) {
        comida.x = rand() % COLUMNAS;
        comida.y = rand() % FILAS;

        posicion_valida = true;
        int idx = serpiente.front;
        for (int i = 0; i < serpiente.size; i++) {
            if (serpiente.body[idx].x == comida.x && serpiente.body[idx].y == comida.y) {
                posicion_valida = false;
                break;
            }
            idx = (idx + 1) % MAX_SNAKE_LENGTH; //
        }
    }
}

void procesar_entrada(void) {
    uint8_t tecla = joystick_read(); //
    
    if (tecla == JOYSTICK_ARRIBA && direccion_actual != JOYSTICK_ABAJO)     direccion_actual = JOYSTICK_ARRIBA;
    if (tecla == JOYSTICK_ABAJO && direccion_actual != JOYSTICK_ARRIBA)     direccion_actual = JOYSTICK_ABAJO;
    if (tecla == JOYSTICK_IZQUIERDA && direccion_actual != JOYSTICK_DERECHA) direccion_actual = JOYSTICK_IZQUIERDA;
    if (tecla == JOYSTICK_DERECHA && direccion_actual != JOYSTICK_IZQUIERDA) direccion_actual = JOYSTICK_DERECHA;
}

void actualizar_logica(void) {
    Punto cabeza_actual = serpiente.body[serpiente.rear];
    Punto siguiente_cabeza = cabeza_actual;

    switch (direccion_actual) {
        case JOYSTICK_ARRIBA:    siguiente_cabeza.y--; break;
        case JOYSTICK_ABAJO:     siguiente_cabeza.y++; break;
        case JOYSTICK_IZQUIERDA: siguiente_cabeza.x--; break;
        case JOYSTICK_DERECHA:   siguiente_cabeza.x++; break;
        default: break;
    }

    if (siguiente_cabeza.x < 0 || siguiente_cabeza.x >= COLUMNAS ||
        siguiente_cabeza.y < 0 || siguiente_cabeza.y >= FILAS) {
        juego_terminado = true;
        return;
    }

    if (verificarColisionCuerpo(&serpiente, siguiente_cabeza)) { //
        juego_terminado = true;
        return;
    }

    bool ha_comido = (siguiente_cabeza.x == comida.x && siguiente_cabeza.y == comida.y);
    moveSnake(&serpiente, siguiente_cabeza, ha_comido); //

    if (ha_comido) {
        puntuacion += 10;
        generar_comida();
    }
}

void renderizar(void) {
    glcd_borrar(NEGRO); //

    // 1. Cabecera gráfica
    glcd_xprintf(OFFSET_X, 8, AMARILLO, NEGRO, FUENTE8X16, "SCORE: %05d", puntuacion); //
    glcd_rectangulo(OFFSET_X - 1, OFFSET_Y - 1, OFFSET_X + (COLUMNAS * TAM_BLOQUE), OFFSET_Y + (FILAS * TAM_BLOQUE), CIAN_OSCURO); //
    
    // Comida
    int comida_centro_x = OFFSET_X + (comida.x * TAM_BLOQUE) + (TAM_BLOQUE / 2);
    int comida_centro_y = OFFSET_Y + (comida.y * TAM_BLOQUE) + (TAM_BLOQUE / 2);
    glcd_circulo(comida_centro_x, comida_centro_y, (TAM_BLOQUE / 2) - 4, ROJO); //

    // 2. Recorrer y renderizar la serpiente
    int idx = serpiente.front;
    for (int i = 0; i < serpiente.size; i++) {
        if (idx == serpiente.rear) {
            // Es la cabeza: Dibujamos la Flecha Vectorial orientada
            dibujar_cabeza_flecha(serpiente.body[idx].x, serpiente.body[idx].y, direccion_actual, OLIVA);
        } else {
            // Es el cuerpo: Dibujamos un Bloque Cuadrado relleno
            dibujar_cuerpo(serpiente.body[idx].x, serpiente.body[idx].y, VERDE);
        }
        idx = (idx + 1) % MAX_SNAKE_LENGTH; //
    }

    // 3. Volcar todo a la salida visual activa (Consola)
    volcar_vram_a_consola();
}

// Dibuja el cuerpo como un cuadrado regular relleno
void dibujar_cuerpo(int x, int y, uint16_t color) {
    int x0 = OFFSET_X + (x * TAM_BLOQUE) + 2; 
    int y0 = OFFSET_Y + (y * TAM_BLOQUE) + 2;
    int x1 = x0 + TAM_BLOQUE - 4;
    int y1 = y0 + TAM_BLOQUE - 4;
    glcd_rectangulo_relleno(x0, y0, x1, y1, color); //
}

// Dibuja la cabeza como una punta de flecha (Triángulo apuntando a la dirección del movimiento)
void dibujar_cabeza_flecha(int x, int y, enum joystick_dir dir, uint16_t color) {
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

// Imprime el juego de manera exacta usando caracteres de texto dedicados
void volcar_vram_a_consola(void) {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    printf("=====================================\n");
    printf(" SCORE: %05d       SNAKE 14x7 MATRIX\n", puntuacion);
    printf("=====================================\n");

    printf("#");
    for (int c = 0; c < COLUMNAS; c++) printf("--");
    printf("#\n");

    for (int f = 0; f < FILAS; f++) {
        printf("|");
        for (int c = 0; c < COLUMNAS; c++) {
            
            if (comida.x == c && comida.y == f) {
                printf("O "); 
                continue;
            }

            bool es_serpiente = false;
            int idx = serpiente.front;
            for (int i = 0; i < serpiente.size; i++) {
                if (serpiente.body[idx].x == c && serpiente.body[idx].y == f) {
                    if (idx == serpiente.rear) {
                        // Cambiar dinámicamente el carácter ASCII según la dirección del movimiento
                        switch (direccion_actual) {
                            case JOYSTICK_ARRIBA:    printf("^ "); break;
                            case JOYSTICK_ABAJO:     printf("v "); break;
                            case JOYSTICK_IZQUIERDA: printf("< "); break;
                            case JOYSTICK_DERECHA:   printf("> "); break;
                            default:                 printf("@ "); break;
                        }
                    } else {
                        printf("o "); // Cuerpo cuadrado estándar
                    }
                    es_serpiente = true;
                    break;
                }
                idx = (idx + 1) % MAX_SNAKE_LENGTH; //
            }

            if (!es_serpiente) {
                printf(". "); 
            }
        }
        printf("|\n");
    }

    printf("#");
    for (int c = 0; c < COLUMNAS; c++) printf("--");
    printf("#\n");
    printf(" Controles activos: W A S D / Flechas \n");
}