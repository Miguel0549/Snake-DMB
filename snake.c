#include "glcd.h"
#include "snake.h"


void pintar_tablero()
{
	glcd_inicializar();
	glcd_borrar(AZUL);
	
	int i,j;
	for ( i=0 ; i<N+2 ; ++i ){
		for ( j=0 ; j<N+2 ; ++j ){
			if ( i==0 || i== N+1 ){
				switch(j){
					case 0 :  if (i==0) glcd_caracter(ESQ_SI,i,j,0xFF,WHITE,1); else if (i== N+1) glcd_caracter(ESQ_SD,i,j,0xFF,WHITE,1);
					break;
					case N+1 : if (i==0) glcd_caracter(ESQ_II,i,j,0xFF,WHITE,1); else if (i== N+1) glcd_caracter(ESQ_ID,i,j,0xFF,WHITE,1);
					break;
					default : glcd_caracter(BAR_V,i,j,0xFF,WHITE,1);
					break;
				}
			} else glcd_caracter(BAR_H,i,j,0xFF,WHITE,1);
		}
	}

}

