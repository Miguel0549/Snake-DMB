/**
 * @file    joystick.c
 * @brief   Función básica de lectura del joystick integrado en la tarjeta Embedded Artist LPC4088.
 *
 * @details Los pulsadores del joystick son activos a nivel bajo: cuando se pulsan ponen el
 * correspondiente pin del microcontrolador a 0 y cuando están sin pulsar ponen el
 * correspondiente pin a 1. Las conexiones entre el joystick el microcontrolador son:
 *
 * Pin uC | Dirección
 * ------ | ---------
 * P2[25] | ARRIBA
 * P2[27] | ABAJO
 * P2[23] | IZQUIERDA
 * P2[26] | DERECHA
 * P2[22] | CENTRAL
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
#include "gpio_lpc40xx.h"
#include "leds.h"

// ===== Joystick - Funciones Publicas =====
/**
 * @brief   Leer el joystick y retornar un número diferente según la dirección que se esté pulsando.
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
  // ===== COMPLETAR =====
}
