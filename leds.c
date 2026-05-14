/**
 * @file    leds.c
 * @brief   Funciones para manejar cuatro de los LEDs de la tarjeta Embedded Artist LPC4088.
 *
 * @details Los LEDs son activos a nivel bajo: cuando uno de estos pines del microcontrolador se
 * pone a 1 el correspondiente LED se apaga y cuando se pone a 0 el LED se enciende. Las conexiones
 * entre los LEDs de la tarjeta y el microcontrolador son las siguientes:
 *
 * Pin uC | Nombre | Color
 * ------ | ------ | ------
 * P1[5]  | LED1   | ROJO
 * P0[14] | LED2   | VERDE
 * P0[13] | LED3   | VERDE
 * P1[18] | LED4   | VERDE
 *
 * @author
 * @date
 * @version
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "leds.h"
#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "error.h"
#include "gpio_lpc40xx.h"

/**
 * @brief   Configura como salida los pines del microcontrolador a los que están conectados a los
 * LEDs y los apaga.
 * @ingroup LEDs
 */
void leds_inicializar(void) {

  // Ajustar la dirección de los pines de los LEDs como salida
  // ===== COMPLETAR =====

  // Inicializar el valor de los leds
  // ===== COMPLETAR =====
}

/**
 * @brief   Enciende un LED.
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a encender. Debe estar entre 1 y 4.
 */
void leds_encender(uint8_t numero_led) {
  // ===== COMPLETAR =====
}

/**
 * @brief   Apaga un LED.
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a apagar. Debe estar entre 1 y 4.
 */
void leds_apagar(uint8_t numero_led) {
  // ===== COMPLETAR =====
}

/**
 * @brief   Invierte el estado de un LED.
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a invertir. Debe estar entre 1 y 4.
 */
void leds_invertir(uint8_t numero_led) {
  // ===== COMPLETAR =====
}

/**
 * @brief   Ajusta el estado de un LED
 * @ingroup LEDs
 *
 * @param[in]   numero_led  Número del LED a ajustar. Debe estar entre 1 y 4.
 * @param[in]   estado      Estado que debe adoptar el LED. TRUE => encendido, FALSE => apagado.
 */
void leds_ajustar(uint8_t numero_led, bool_t estado) {
  // ===== COMPLETAR =====
}