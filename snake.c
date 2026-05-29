#include "snake.h"
#include <stdlib.h>

void moveSnake(Snake *snake, Punto direccion, bool ateFood) {
    snake->cabeza=sumarPuntos(snake->cabeza, direccion)
    if (!ateFood) {
        snake->final=sumarPuntos(snake->final, Desencolar(snake->movs_pendientes));
    }
		Encolar(snake->movs_pendientes, crearNodo(direccion));
}

bool verificarColisionCuerpo(Snake *snake, Punto nuevaCabeza, Tablero t) {
    if (snake->size <= 4) return false;
		if (nuevaCabeza=snake->final) return false;
		if (nuevaCabeza.x<0 || nuevaCabeza.y<0 || nuevaCabeza.x>6 || nuevaCabeza.y>13){
			return true;
	  }elseif (t[nuevaCabeza.x][nuevaCabeza.y]=-1) return true;
    return false;
}

void initTablero(Snake *snake, Tablero* tab) {
	
		for( int i=0 ; i< 14 ; ++i ){
			for ( int j=0 ; j< 7 ; j++ ){
					tab->t[i][j] = 0;
			}
		}
		
		tab->t[1][3] = -1;
		tab->t[1][2] = -1;
		tab->t[1][1] = -1;
		
		generar_comida(snake, tab);
		generar_comida(snake, tab);
		generar_comida(snake, tab);
		
}

void inicializar_juego(Snake* serpiente,Tablero* tablero, uint16_t* puntuacion, enum joystick_dir *direccion_actual, bool* juego_terminado) {
    puntuacion = 0;
    juego_terminado = false;
    *direccion_actual = JOYSTICK_DERECHA; 
    
    initTablero(serpiente, tablero); 
		initSnake(snake);
}

void generar_comida(Snake* serpiente, Tablero* tab) {
    if (tab->n_frutas==FILAS*COLUMNAS-serpiente->tama) return;
		
		Punto p=constructorPunto(0,0); //corregir por número aleatorio
		while (tab->t[p.x][p.y]!=0){
			p=constructorPunto(0,0); //corregir por número aleatorio
		}
		tab->t[p.x][p.y]=1;
		tab->n_frutas++;
}

void procesar_entrada(enum joystick_dir *direccion_actual) {
    uint8_t tecla = joystick_leer();
    
    if (tecla == JOYSTICK_ARRIBA && *direccion_actual != JOYSTICK_ABAJO)     *direccion_actual = JOYSTICK_ARRIBA;
    if (tecla == JOYSTICK_ABAJO && *direccion_actual != JOYSTICK_ARRIBA)     *direccion_actual = JOYSTICK_ABAJO;
    if (tecla == JOYSTICK_IZQUIERDA && *direccion_actual != JOYSTICK_DERECHA) *direccion_actual = JOYSTICK_IZQUIERDA;
    if (tecla == JOYSTICK_DERECHA && *direccion_actual != JOYSTICK_IZQUIERDA) *direccion_actual = JOYSTICK_DERECHA;
}

Punto trans_joy_to_point(enum joystick_dir direccion_actual){
		Punto p;
		switch (direccion_actual){
			case JOYSTICK_ARRIBA:
				p=constructorPunto(0,1);
				break;
			case JOYSTICK_ABAJO:
				p=constructorPunto(0,-1);
				break;
			case JOYSTICK_IZQUIERDA:
				p=constructorPunto(-1,0);
				break;
			case JOYSTICK_DERECHA:
				p=constructorPunto(1,0);
				break;
			default:
				p=constructorPunto(1,0);
				break;
		}
		return p;
}

void actualizar_logica(Snake* serpiente, Tablero* tab, uint16_t* puntuacion, Punto direccion, bool* juego_terminado ) {
    Punto siguiente_cabeza = sumarPuntos(serpiente->cabeza, direccion);

    if (verificarColisionCuerpo(serpiente, siguiente_cabeza, tab) || serpiente->tama==MAX_SNAKE_LENGTH) { //
        *juego_terminado = true;
        return;
    }

    bool ha_comido = (tab->t[siguiente_cabeza.x][siguiente_cabeza.y]==1;);
    moveSnake(serpiente, direccion, ha_comido); //

    if (ha_comido) {
        *puntuacion += 20;
        generar_comida(tab);
    }
}

void renderizar(Snake* serpiente, Tablero* tab, uint16_t* puntuacion,enum joystick_dir *direccion_actual) {
    glcd_borrar(NEGRO); 
    glcd_rectangulo(OFFSET_X - 1, OFFSET_Y - 1, OFFSET_X + (COLUMNAS * TAM_BLOQUE)+1, OFFSET_Y + (FILAS * TAM_BLOQUE)+1, CIAN_OSCURO); //
    
		renderizarBucle(serpiente, tab, direccion_actual);
}

void renderizarBucle(Snake* snake, Tablero* tab, uint16_t* puntuacion, enum joystick_dir *direccion_actual){
	glcd_xprintf(OFFSET_X, 8, AMARILLO, NEGRO, FUENTE8X16, "SCORE: %05d", *puntuacion); 
	glcd_rectangulo_relleno(OFFSET_X, OFFSET_Y, OFFSET_X + (COLUMNAS * TAM_BLOQUE), OFFSET_Y + (FILAS * TAM_BLOQUE), NEGRO);
    for (int i = 0; i < 7; i++) { 
				for (int j=0; j < 14; j++){
					if (tab->t[i][j]==-1) {
						if(snake->cabeza.x==i && snake->cabeza.y==j){
							dibujar_cabeza_flecha(i, j, direccion_actual, OLIVA);
						}
							dibujar_cuerpo(i, j, OLIVA);
					} else if (tab->t[i][j]==1) {
							dibujar_fruta(i, j, ROJO);
					}
				}
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




// Dibuja la fruta
void dibujar_fruta (uint8_t x, uint8_t y, uint16_t color) {

}







