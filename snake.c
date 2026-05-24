#include "glcd.h"
#include "uart_lpc40xx.h"
#include "snake.h"
#include <stdlib.h>


void pintar_tablero()
{
	glcd_inicializar();
	glcd_borrar(AZUL);
	
	/*int i,j;
	for ( i=16 ; i<N-15 ; i+=8 ){
		for ( j=32 ; j<M-31 ; j+=16 ){
			if ( i==16 || i== N-16 || j==32 || j== M-32){
				if (i==16 && j==32){
					glcd_caracter('/',i,j,YELLOW,BLUE,0);
				} else if (i==N-16 && j==32) {
					glcd_caracter('T',i,j,YELLOW,BLUE,0);
				} else if (i==16 && j==M-32) {
					glcd_caracter('L',i,j,YELLOW,BLUE,0);
				} else if (i==N-16 && j==M-32) {
					glcd_caracter('/',i,j,YELLOW,BLUE,0);
				} else if (i==16 || i==N-16){
					glcd_caracter('|',i,j,YELLOW,BLUE,0);
				} else {
					glcd_caracter('-',i,j,YELLOW,BLUE,0);
				}
			}
		}
	}*/
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

