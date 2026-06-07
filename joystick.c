/**
 * @file    joystick.c
 * @brief   Función básica de lectura del joystick integrado en la tarjeta Embedded Artist LPC4088.
 *
 * @details Los pulsadores del joystick son activos a nivel bajo: cuando se pulsan ponen el
 * correspondiente pin del microcontrolador a 0 y cuando están sin pulsar ponen el
 * correspondiente pin a 1. Las conexiones entre el joystick el microcontrolador son:
 *
 * Interno
 *
 * Pin uC | Dirección
 * ------ | ---------
 * P2[25] | ARRIBA
 * P2[27] | ABAJO
 * P2[23] | IZQUIERDA
 * P2[26] | DERECHA
 * P2[22] | CENTRAL
 *
 * Externo (leer2)
 *
 * Pin uC | Dirección
 * ------ | ---------
 * P0[24] | ARRIBA
 * P0[23] | ABAJO
 * P2[21] | IZQUIERDA
 * P1[18] | DERECHA
 * P0[27] | CENTRAL
 *
 * @author
 * @date
 * @version
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "joystick.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "leds.h"

// ===== Joystick - Funciones Publicas =====
 
void joystick_inicializar(){
	
	LPC_IOCON->P0_23 = (LPC_IOCON->P0_23 & ~0x9F) | (1 << 7) | (2 << 3); 
  LPC_IOCON->P0_24 = (LPC_IOCON->P0_24 & ~0x9F) | (1 << 7) | (2 << 3);
    
  LPC_IOCON->P0_27 = (LPC_IOCON->P0_27 & ~0x1F) | (2 << 3);

  LPC_IOCON->P1_18 = (LPC_IOCON->P1_18 & ~0x1F) | (2 << 3);

  LPC_IOCON->P2_21 = (LPC_IOCON->P2_21 & ~0x1F) | (2 << 3);
	
	LPC_GPIO0->DIR &= ~((1<<24)|(1<<23)|(1<<27));
	LPC_GPIO1->DIR &= ~(1<<18);
	LPC_GPIO2->DIR &= ~(1<<21);
}

/**
 * @brief   Leer el joystick del kit y retornar un número diferente según la dirección que se esté pulsando.
 * @ingroup Joystick
 *
 * @retval  JOYSTICK_NADA/0 si no se está pulsando ningúna dirección.
 * @retval  JOYSTICK_ARRIBA/1 si el joystick está pulsado hacia ARRIBA.
 * @retval  JOYSTICK_ABAJO/2 si el joystick está pulsado hacia ABAJO.
 * @retval  JOYSTICK_IZQUIERDA/3 si el joystick está pulsado hacia la IZQUIERDA.
 * @retval  JOYSTICK_DERECHA/4 si el joystick está pulsado hacia la DERECHA.
 * @retval  JOYSTICK_CENTRO/5 si el joystick está pulsado hacia el CENTRO.
 */ 
uint8_t joystick_leer(void) {
	leds_apagar(LED1);
	leds_apagar(LED2);
	leds_apagar(LED3);
	leds_apagar(LED4);
	if (!(LPC_GPIO2->PIN & (1<<25))){
		leds_encender(LED2);
		return JOYSTICK_ARRIBA;
	}
	else if(!(LPC_GPIO2->PIN & (1<<27))){
		leds_encender(LED4);
		return JOYSTICK_ABAJO;
	}
	else if(!(LPC_GPIO2->PIN & (1<<23))){
		leds_encender(LED1);
		return JOYSTICK_IZQUIERDA;
	}
	else if(!(LPC_GPIO2->PIN & (1<<26))){
		leds_encender(LED3);
		return JOYSTICK_DERECHA;
	}
	else if(!(LPC_GPIO2->PIN & (1<<22))){
		leds_encender(LED2);
		leds_encender(LED4);
		leds_encender(LED1);
		leds_encender(LED3);
		return JOYSTICK_CENTRO;
	}
	else{
		return JOYSTICK_NADA;
	}
}

/**
 * @brief   Leer el joystick externo y retornar un número diferente según la dirección que se esté pulsando.
 * @ingroup Joystick
 *
 * @retval  JOYSTICK_NADA/0 si no se está pulsando ningúna dirección.
 * @retval  JOYSTICK_ARRIBA/1 si el joystick está pulsado hacia ARRIBA.
 * @retval  JOYSTICK_ABAJO/2 si el joystick está pulsado hacia ABAJO.
 * @retval  JOYSTICK_IZQUIERDA/3 si el joystick está pulsado hacia la IZQUIERDA.
 * @retval  JOYSTICK_DERECHA/4 si el joystick está pulsado hacia la DERECHA.
 * @retval  JOYSTICK_CENTRO/5 si el joystick está pulsado hacia el CENTRO.
 */
uint8_t joystick_leer2(void){
	leds_apagar(LED1);
	leds_apagar(LED2);
	leds_apagar(LED3);
	leds_apagar(LED4);
	if (!(LPC_GPIO0->PIN & (1<<24))){
		leds_encender(LED2);
		return JOYSTICK_ARRIBA;
	}
	else if(!(LPC_GPIO0->PIN & (1<<23))){
		leds_encender(LED4);
		return JOYSTICK_ABAJO;
	}
	else if(!(LPC_GPIO2->PIN & (1<<21))){
		leds_encender(LED1);
		return JOYSTICK_IZQUIERDA;
	}
	else if(!(LPC_GPIO1->PIN & (1<<18))){
		leds_encender(LED3);
		return JOYSTICK_DERECHA;
	}
	else if(!(LPC_GPIO0->PIN & (1<<27))){
		leds_encender(LED2);
		leds_encender(LED4);
		leds_encender(LED1);
		leds_encender(LED3);
		return JOYSTICK_CENTRO;
	}
	else{
		return JOYSTICK_NADA;
	}
}
