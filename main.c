#include "snake.h"
//#include <stdlib.h>
#include <LPC407x_8x_177x_8x.h>
#include "timer_lpc40xx.h"

//Prototipos de funciones
void bajo_consumo(void);

int main(void) { 
		
	  bajo_consumo();
		glcd_inicializar();
	  __enable_irq();
	
		glcd_xprintf(0,0,WHITE,BLACK,0,"glcd_inicializar();");
	
	  SnakeQueue serpiente;
		Punto comida;
		int puntuacion = 0;
		enum joystick_dir direccion_actual = JOYSTICK_DERECHA; 
		bool juego_terminado = false;
	
	  glcd_xprintf(0,0,WHITE,BLACK,0,"Variables iniciales");
	
	  //srand(120); 
      inicializar_juego(&serpiente,&comida,&puntuacion,&direccion_actual,&juego_terminado);
	
		glcd_xprintf(0,0,WHITE,BLACK,0,"inicializar_juego");

		while(1){
			
			while (!juego_terminado) {
				glcd_xprintf(0,0,WHITE,BLACK,0,"entra whhile juego");
			  procesar_entrada(&direccion_actual);
			
				glcd_xprintf(0,0,WHITE,BLACK,0,"mirar teclado");
				
        actualizar_logica(&serpiente,&comida,&puntuacion,&direccion_actual,&juego_terminado);
				glcd_xprintf(0,0,WHITE,BLACK,0,"Mover serpiente");
        renderizar(&serpiente,&comida,&puntuacion,&direccion_actual);
				glcd_xprintf(0,0,WHITE,BLACK,0,"pintar serpiente");
      }

      // Pantalla de Game Over
		
		
		}
   

    return 0;
}


void bajo_consumo(void){
  //---------------------------------- UART1  I2C1  I2C2
  LPC_SC->PCONP &= (LPC_SC->PCONP & ~((1<<4)|(1<<19)|(1<<26)));
  LPC_SC->PCONP1 = 0;//Comparador
}