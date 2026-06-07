#include "snake.h"
#include <LPC407x_8x_177x_8x.h>
#include "timer_lpc40xx.h"

void bajo_consumo(void);

int main(void) { 
		
	  bajo_consumo();
		glcd_inicializar();
		timer_inicializar(TIMER0);
		timer_inicializar(TIMER1);
	  __enable_irq();
		joystick_inicializar();
		
		
	  Snake serpiente;
		Tablero tab;
		uint16_t puntuacion = 0;
		enum joystick_dir direccion_actual = JOYSTICK_DERECHA; 
		bool juego_terminado = false;
		 
		pantalla_iniciar();
		timer_iniciar_conteo_ms(TIMER1);
		while (joystick_leer2() != JOYSTICK_CENTRO){}
		uint32_t seed=timer_leer(TIMER1);
	  srand(seed);
	
		while(1){
			timer_iniciar_ciclos_ms (TIMER0, 500);
			inicializar_juego(&serpiente,&tab,&puntuacion,&direccion_actual,&juego_terminado);
			renderizar(&serpiente,&tab,&puntuacion,&direccion_actual);
			juego_terminado=false;
			while (!juego_terminado) {
				while (timer_fin_ciclo(TIMER0)){ 
						procesar_entrada(&direccion_actual);
				}
				timer_esperar_fin_ciclo(TIMER0);
				
				Punto direccion= trans_joy_to_point(direccion_actual);
				
        actualizar_logica(&serpiente,&tab,&puntuacion, direccion, &juego_terminado);
        renderizarBucle(&serpiente,&tab,&puntuacion, &direccion_actual);
				glcd_xprintf(200,5,WHITE,BLACK,0,"pintar serpiente");
      }

      if (serpiente.tama==MAX_SNAKE_LENGTH){
				pantalla_victoria(&puntuacion);
			} else {
				pantalla_derrota(&puntuacion);
			}
			timer_retardo_ms(TIMER1, 5000);
			pantalla_continuar();
			while (joystick_leer2() != JOYSTICK_CENTRO){}
				
		}
   

    return 0;
		
}


void bajo_consumo(void){
  LPC_SC->PCONP &= (LPC_SC->PCONP & ~((1<<4)|(1<<19)|(1<<26)));
  LPC_SC->PCONP1 = 0;
}

void _ttywrch(int ch) {
    (void)ch; 
}