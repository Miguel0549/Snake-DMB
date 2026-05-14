/**
 * @file    gpio_lpc40xx.h
 * @brief   Constantes y funciones para manejar los puertos E/S digital del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef GPIO_LPC40XX_H
#define GPIO_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"

// ===== GPIO - Constantes Publicas =====
/**
 * @defgroup  GPIO_Macros_Publicas GPIO - Macros Públicas
 * @ingroup   GPIO
 * @brief     Símbolos alternativos de los puertos GPIO.
 * @{
 */
#define PORT0   LPC_GPIO0
#define PORT1   LPC_GPIO1
#define PORT2   LPC_GPIO2
#define PORT3   LPC_GPIO3
#define PORT4   LPC_GPIO4
#define PORT5   LPC_GPIO5

#define PUERTO0 PORT0
#define PUERTO1 PORT1
#define PUERTO2 PORT2
#define PUERTO3 PORT3
#define PUERTO4 PORT4
#define PUERTO5 PORT5
//!@}

/**
 * @brief     Número de puertos del LPC4088 (GPIO0-GPIO5).
 * @ingroup   GPIO
 */
#define GPIO_NUMERO_PUERTOS 6u

/**
 * @brief     Número máximo de pines por puerto de GPIO.
 * @ingroup   GPIO
 */
#define GPIO_MAXIMO_PINES_POR_PUERTO 32u

/**
 * @brief   Símbolos de las máscaras de los pines.
 * @ingroup GPIO
 */
enum gpio_pines {
  PIN0 = (1u << 0),
  PIN1 = (1u << 1),
  PIN2 = (1u << 2),
  PIN3 = (1u << 3),
  PIN4 = (1u << 4),
  PIN5 = (1u << 5),
  PIN6 = (1u << 6),
  PIN7 = (1u << 7),
  PIN8 = (1u << 8),
  PIN9 = (1u << 9),
  PIN10 = (1u << 10),
  PIN11 = (1u << 11),
  PIN12 = (1u << 12),
  PIN13 = (1u << 13),
  PIN14 = (1u << 14),
  PIN15 = (1u << 15),
  PIN16 = (1u << 16),
  PIN17 = (1u << 17),
  PIN18 = (1u << 18),
  PIN19 = (1u << 19),
  PIN20 = (1u << 20),
  PIN21 = (1u << 21),
  PIN22 = (1u << 22),
  PIN23 = (1u << 23),
  PIN24 = (1u << 24),
  PIN25 = (1u << 25),
  PIN26 = (1u << 26),
  PIN27 = (1u << 27),
  PIN28 = (1u << 28),
  PIN29 = (1u << 29),
  PIN30 = (1u << 30),
  PIN31 = (1u << 31)
};

/**
 * @brief   Constantes para especificar la dirección de un pin.
 * @ingroup GPIO
 */
enum gpio_direccion {
  DIR_IN = 0u,
  DIR_OUT = 1u,
  DIR_ENTRADA = 0u,
  DIR_SALIDA = 1u
};


#ifndef inline
  #define inline __inline  //!< Definición del cualificador inline no disponible en modo C90.
#endif

// ===== GPIO - Funciones Publicas =====
/**
 * @brief   Lee el estado de un pin.
 * @ingroup GPIO
 *
 * @param[in]   gpio_regs     Puntero al bloque de registros del puerto.
 * @param[in]   mascara_pin   Máscara para seleccionar el pin.
 *
 * @retval  FALSE   El pin está a 0.
 *          TRUE    El pin está a 1.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline bool_t gpio_leer_pin(const LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin) {
  return (gpio_regs->PIN & mascara_pin) != 0;
}

/**
 * @brief     Lee el estado de un puerto completo.
 * @ingroup   GPIO
 *
 * @param[in]   gpio_regs   Puntero al bloque de registros del puerto.
 *
 * @return    Valor leído del puerto.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline uint32_t gpio_leer_puerto(const LPC_GPIO_TypeDef *gpio_regs) {
  return gpio_regs->PIN;
}

/**
 * @brief   Establece el estado de uno o más pines de salida al mismo estado.
 * @ingroup GPIO
 *
 * @param[in]   gpio_regs     Puntero al bloque de registros del puerto.
 * @param[in]   mascara_pin   Máscara de selección del pin o pines.
 * @param[in]   valor         FALSE => poner a 0, TRUE => poner a 1.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline void gpio_escribir_pin(LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin, bool_t valor) {
  if (valor) {
    gpio_regs->SET = mascara_pin;
  } else {
    gpio_regs->CLR = mascara_pin;
  }
}

/**
 * @brief   Establece el estado de todos los pines de salida de un puerto.
 * @ingroup GPIO
 *
 * @param[in]   gpio_regs   Puntero al bloque de registros del puerto.
 * @param[in]   valor       Valor a escribir en el puerto.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline void gpio_escribir_puerto(LPC_GPIO_TypeDef *gpio_regs, uint32_t valor) {
  gpio_regs->PIN = valor;
}

/**
 * @brief   Pone a 1 uno o más pines de salida.
 * @ingroup GPIO
 *
 * @param[in]   gpio_regs     Puntero al bloque de registros del puerto.
 * @param[in]   mascara_pin   Máscara de selección del pin o pines.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline void gpio_pin_a_1(LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin) {
  gpio_regs->SET = mascara_pin;
}

/**
 * @brief   Pone a 0 uno o más pines de salida.
 * @ingroup GPIO
 *
 * @param[in]   gpio_regs     Puntero al bloque de registros del puerto.
 * @param[in]   mascara_pin   Máscara de selección del pin o pines.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline void gpio_pin_a_0(LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin) {
  gpio_regs->CLR = mascara_pin;
}

/**
 * @brief   Invierte el estado de uno o más pines de salida.
 * @ingroup GPIO
 *
 * @param[in]   gpio_regs     Puntero al bloque de registros del puerto.
 * @param[in]   mascara_pin   Máscara de selección del pin o pines.
 *
 * @warning No se comprueba la validez de los argumentos para que el tiempo de ejecución sea
 * corto y reducir el tamaño de la expansión en línea.
 */
inline void gpio_invertir_pin(LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin) {
  gpio_regs->PIN ^= mascara_pin;
}

// ===== Prototipos de funciones definidas en gpio_lpc40xx.c =====
void gpio_ajustar_dir(LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin, uint32_t direccion);
uint32_t gpio_obtener_dir(const LPC_GPIO_TypeDef *gpio_regs, uint32_t mascara_pin);

#endif  // GPIO_LPC40XX_H
