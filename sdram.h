/**
 * @file    sdram.h
 * @brief   Funciones para utilizar la SDRAM con la pantalla LCD de EA para el LPC4088.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef SDRAM_H
#define SDRAM_H

#include "tipos.h"

// ===== SDRAM - Constantes Publicas =====
/**
 * @defgroup  SDRAM_VEL Velocidad de comunicación con la SDRAM.
 * @ingroup   SDRAM
 * @{
 */
#define SDRAM_VEL_48MHZ 0  //!< Velocidad de 48 MHz.
#define SDRAM_VEL_50MHZ 1  //!< Velocidad de 50 MHz.
#define SDRAM_VEL_60MHZ 2  //!< Velocidad de 60 MHz.
#define SDRAM_VEL_72MHZ 3  //!< Velocidad de 72 MHz.
#define SDRAM_VEL_80MHZ 4  //!< Velocidad de 80 MHz.
 //!@}

/**
 * @defgroup  SDRAM_CONFIG Parámetros de la SDRAM utilizada.
 * @ingroup   SDRAM
 * @{
 */
#define SDRAM_BITS  32                //!< Número de bits del bus de la SDRAM.
#define SDRAM_FREC  SDRAM_VEL_60MHZ   //!< Velocidad de la SDRAM seleccionada.
#define SDRAM_SIZE  0x2000000         //!< Tamaño de la SDRAM.
#define SDRAM_BASE  0xA0000000        //!< Dirección 0 de la SDRAM (CS0).
//!@}

// ===== SDRAM - Funciones Publicas =====
bool_t sdram_inicializar(void);

#endif // SDRAM_H
