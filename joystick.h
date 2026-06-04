/**
 * @file    joystick.h
 * @brief   Función básica de lectura del joystick integrado en la tarjeta
 * Embedded Artist LPC4088.
 *
 * @details Los pulsadores del joystick son activos a nivel bajo: cuando se
 * pulsan ponen el correspondiente pin del microcontrolador a 0 y cuando están
 * sin pulsar ponen el correspondiente pin a 1. Las conexiones entre el joystick
 * el microcontrolador son:
 *
 * Pin uC | Dirección
 * ------ | ---------
 * P2[25] | ARRIBA
 * P2[27] | ABAJO
 * P2[23] | IZQUIERDA
 * P2[26] | DERECHA
 * P2[22] | CENTRAL
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "tipos.h"

// ===== Joystick - Constantes Publicas =====
/**
 * @brief Constantes para indicar la dirección hacia donde se pulsó el Joystick.
 * @ingroup Joystick
 */
enum joystick_dir {
  JOYSTICK_NADA = 0,
  JOYSTICK_ARRIBA = 1,
  JOYSTICK_ABAJO = 2,
  JOYSTICK_IZQUIERDA = 3,
  JOYSTICK_DERECHA = 4,
  JOYSTICK_CENTRO = 5
};

// ===== Joystick - Funciones Publicas =====
uint8_t joystick_leer(void);

#endif // JOYSTICK_H
