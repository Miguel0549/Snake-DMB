#include "snake.h"
//#include <stdlib.h>
#include <LPC407x_8x_177x_8x.h>
#include "timer_lpc40xx.h"

//Prototipos de funciones
void bajo_consumo(void);

int main(void) { 
		
	  bajo_consumo();
		glcd_inicializar();
	  timer_inicializar(TIMER0);
	  __enable_irq();
	
		
	  Snake serpiente;
		Tablero tab;
		uint16_t puntuacion = 0;
		enum joystick_dir direccion_actual = JOYSTICK_DERECHA; 
		bool juego_terminado = false;
	
		
	  //srand(120); 
    inicializar_juego(&serpiente,&tab,&puntuacion,&direccion_actual,&juego_terminado);
		
		//inicializar ciclos del timer
	
	  timer_iniciar_ciclos_ms(TIMER0,700);
		
		while(1){
			renderizar(&serpiente,&tab,&puntuacion,&direccion_actual);
			
			while (!juego_terminado) {
				
				procesar_entrada(&direccion_actual);
				
				Punto direccion= trans_joy_to_point(direccion_actual);
				
        actualizar_logica(&serpiente,&tab,&puntuacion, direccion, &juego_terminado);
				glcd_xprintf(0,0,WHITE,BLACK,0,"Mover serpiente");
        renderizarBucle(&serpiente,&tab,&puntuacion, &direccion_actual);
				glcd_xprintf(0,0,WHITE,BLACK,0,"pintar serpiente");
				
				timer_esperar_fin_ciclo(TIMER0);
      }

      if (serpiente.tama==MAX_SNAKE_LENGTH){
				pantalla_victoria(&puntuacion);
			} else {
				pantalla_derrota(&puntuacion);
			}
			
			timer_retardo_ms(TIMER0,2000);
			
			pantalla_continuar();
			while (joystick_leer() != JOYSTICK_CENTRO){}
				
		}
   

    return 0;
		
}


void bajo_consumo(void){
  //---------------------------------- UART1  I2C1  I2C2
  LPC_SC->PCONP &= (LPC_SC->PCONP & ~((1<<4)|(1<<19)|(1<<26)));
  LPC_SC->PCONP1 = 0;//Comparador
}

void _ttywrch(int ch) {
    // Se deja vacía porque no tenemos consola real
    (void)ch; 
}