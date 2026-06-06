/**
 * @file    leds.h
 * @brief   Funciones para manejar cuatro de los LEDs de la tarjeta Embedded
 * Artist LPC4088.
 *
 * @details Los LEDs son activos a nivel bajo: cuando uno de estos pines del
 * microcontrolador se pone a 1 el correspondiente LED se apaga y cuando se pone
 * a 0 el LED se enciende. Las conexiones entre los LEDs de la tarjeta y el
 * microcontrolador son las siguientes:
 *
 * Pin uC | Nombre | Color
 * ------ | ------ | ------
 * P1[5]  | LED1   | ROJO
 * P0[14] | LED2   | VERDE
 * P0[13] | LED3   | VERDE
 * P1[18] | LED4   | VERDE
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef LEDS_H
#define LEDS_H

#include "tipos.h"

// ===== LEDs - Constantes Publicas =====
/**
 * @brief   Constantes para refererise a los LEDs de la tarjeta Embedded Artist
 * LPC4088.
 * @ingroup LEDs
 */
enum leds_tarjeta_ea {
  LED1 = 1, //!< LED rojo conectado al pin P1[5]
  LED2 = 2, //!< LED verde conectado al pin P0[14]
  LED3 = 3, //!< LED verde conectado al pin P0[13]
  LED4 = 4  //!< LED verde conectado al pin P1[18]
};

/**
 * @brief   Constantes para el estado de los LEDs.
 * @ingroup LEDs
 */
enum leds_estado {
  LED_APAGADO = FALSE,  //!< LED apagado.
  LED_ENCENDIDO = TRUE, //!< LED encendido.
  LED_OFF = FALSE,      //!< LED apagado.
  LED_ON = TRUE         //!< LED encendido.
};

// ===== LEDs - Funciones Publicas =====
void leds_inicializar(void);
void leds_encender(uint8_t numero_led);
void leds_apagar(uint8_t numero_led);
void leds_invertir(uint8_t numero_led);
void leds_ajustar(uint8_t numero_led, bool_t estado);

#endif // LEDS_H
