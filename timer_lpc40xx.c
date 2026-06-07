/**
 * @file    timer_lpc40xx.c
 * @brief   Funciones para el uso de los timers del LPC40xx.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#include "timer_lpc40xx.h"
#include "error.h"
#include <LPC407x_8x_177x_8x.h>

/**
 * @brief   Inicializa el TIMER indicado habilitándo su alimentación en el
 * registro de control de consumo de periféricos PCONP.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER a inicializar.
 */
void timer_inicializar(const LPC_TIM_TypeDef *timer_regs) {

  if (timer_regs == TIMER0) {
    LPC_SC->PCONP |= (1u << 1);

  } else if (timer_regs == TIMER1) {
    LPC_SC->PCONP |= (1u << 2);

  } else if (timer_regs == TIMER2) {
    LPC_SC->PCONP |= (1u << 22);

  } else if (timer_regs == TIMER3) {
    LPC_SC->PCONP |= (1u << 23);

  } else {
    ERROR("timer_regs incorrecto");
  }
}

/**
 * @brief   Configura un TIMER para que genere un retardo del número de
 * milisegundos indicado. La función no retorna hasta que transcurre este
 * tiempo.
 * @ingroup TIMER
 *
 * @param[in] timer_regs    Ptr. al bloque de registros del TIMER.
 * @param[in] retardo_en_ms Número de milisegundos de duración del retardo.
 *
 * @pre   El TIMER debe estar inicializado antes de invocar esta función.
 *
 * @note  ¡Atención! El registro de preescala se configura para que se
 * incremente cada 0.1 milisegundos para aumentar la resolución y permitir
 * realizar retardos de 1 milisegundo.
 *
 * @warning Función bloqueante.
 */
void timer_retardo_ms(LPC_TIM_TypeDef *timer_regs, uint32_t retardo_en_ms) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  if (retardo_en_ms == 0) {
    return;
  }

  timer_regs->TCR = 0;
  timer_regs->TC = 0;
  timer_regs->PC = 0;
  timer_regs->PR = PeripheralClock * 1e-4 - 1;
  timer_regs->MR0 = 10 * retardo_en_ms - 1;
  timer_regs->MCR |= 7;
  timer_regs->IR = 1;
  timer_regs->TCR = 1;

  while ((timer_regs->IR & 1) == 0) {
    ;
  }
}

/**
 * @brief   Configura un TIMER para que genere un retardo del número de
 * microsegundos indicado. La función no retorna hasta que transcurre este
 * tiempo.
 * @ingroup TIMER
 *
 * @param[in] timer_regs    Ptr. al bloque de registros del TIMER.
 * @param[in] retardo_en_us Número de microsegundos de duración del retardo.
 *
 * @pre   El TIMER debe estar inicializado antes de invocar esta función.
 *
 * @note  ¡Atención! El registro de preescala se configura para que se
 * incremente cada 0.1 microsegundos para aumentar la resolución y permitir
 * realizar retardos de 1 microsegundo.
 *
 * @warning Función bloqueante.
 */
void timer_retardo_us(LPC_TIM_TypeDef *timer_regs, uint32_t retardo_en_us) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  if (retardo_en_us == 0) {
    return;
  }

  // ===== COMPLETAR =====
}

/**
 * @brief   Programa un TIMER para que realice ciclos del número de milisegundos
 * indicado.
 * @ingroup TIMER
 *
 * @param[in] timer_regs    Ptr. al bloque de registros del TIMER.
 * @param[in] periodo_en_ms Duración de cada ciclo en milisegundos.
 *
 * @pre   El TIMER debe estar inicializado antes de invocar esta función.
 *
 * @note  ¡Atención! El registro de preescala se configura para que se
 * incremente cada 0.1 milisegundos para aumentar la resolución y permitir
 * realizar ciclos de 1 milisegundo.
 */
void timer_iniciar_ciclos_ms(LPC_TIM_TypeDef *timer_regs,
                             uint32_t periodo_en_ms) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  ASSERT(periodo_en_ms != 0, "Periodo de timer nulo");

  timer_regs->TCR &= ~(1 << 0);

  timer_regs->PC = 0;
  timer_regs->TC = 0;

  uint32_t PCLK = 25000000;
  timer_regs->PR = (PCLK / 10000) - 1;

  timer_regs->MR0 = periodo_en_ms * 25;

  timer_regs->MCR = (timer_regs->MCR & ~0x07) | (1 << 1) | (1 << 0);

  timer_regs->IR |= 1;

  timer_regs->TCR |= (1 << 0);
}

/**
 * @brief   Programa un TIMER para que realice ciclos del número de
 * microsegundos indicado.
 * @ingroup TIMER
 *
 * @param[in] timer_regs    Ptr. al bloque de registros del TIMER.
 * @param[in] periodo_en_us Duración de cada ciclo en microsegundos.
 *
 * @pre   El TIMER debe estar inicializado antes de invocar esta función.
 *
 * @note  ¡Atención! El registro de preescala se configura para que se
 * incremente cada 0.1 microsegundos para aumentar la resolución y permitir
 * realizar ciclos de 1 microsegundo.
 */
void timer_iniciar_ciclos_us(LPC_TIM_TypeDef *timer_regs,
                             uint32_t periodo_en_us) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  ASSERT(periodo_en_us != 0, "El periodo no puede ser 0");

  // ===== COMPLETAR =====
}

/**
 * @brief   Espera a que el bit de petición de interrupción del match 0 de un
 * TIMER se ponga a 1. Cuando esto ocurra, ponerlo a 0 y retornar.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER.
 *
 * @pre El TIMER debe estar inicializado antes de invocar esta función.
 */
void timer_esperar_fin_ciclo(LPC_TIM_TypeDef *timer_regs) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  ASSERT((timer_regs->TCR & 1) == 1, "El TIMER seleccionado está detenido");

  while ((timer_regs->IR & (1 << 0)) == 0) {
  }

  timer_regs->IR = (1 << 0);
}
/**
 * @brief   Devuelve si el bit de interrupción del match 0 de un timer está a 1.
 * Para cuando quieres hacer algo mientras esperas en un bucle.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER.
 *
 * @pre El TIMER debe estar inicializado antes de invocar esta función.
 */
bool timer_fin_ciclo(LPC_TIM_TypeDef *timer_regs) {
  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");
  ASSERT((timer_regs->TCR & 1) == 1, "El TIMER seleccionado está detenido");
  return ((timer_regs->IR & (1 << 0)) == 0);
}

/**
 * @brief   Programa un TIMER para que se incremente indefinidamente una vez por
 * milisegundo.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER.
 *
 * @pre El TIMER debe estar inicializado antes de invocar esta función.
 */
void timer_iniciar_conteo_ms(LPC_TIM_TypeDef *timer_regs) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  // ===== COMPLETAR =====
  timer_regs->TCR = 0;
  timer_regs->TC = 0;
  timer_regs->PC = 0;
  timer_regs->MCR = 0;
  timer_regs->PR = (PeripheralClock / 1000) - 1;
  timer_regs->TCR = 1;
}

/**
 * @brief   Programa un TIMER para que se incremente indefinidamente una vez por
 * microsegundo.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER.
 *
 * @pre El TIMER debe estar inicializado antes de invocar esta función.
 */
void timer_iniciar_conteo_us(LPC_TIM_TypeDef *timer_regs) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  // ===== COMPLETAR =====
}

/**
 * @brief   Leer el valor del registro TC de un TIMER.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER.
 *
 * @return  Valor actual del registro TC del TIMER seleccionado.
 *
 * @pre El TIMER debe estar inicializado antes de invocar esta función.
 */
uint32_t timer_leer(const LPC_TIM_TypeDef *timer_regs) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  return timer_regs->TC;
}

/**
 * @brief   Reinicia la cuenta de un TIMER.
 * @ingroup TIMER
 *
 * @param[in] timer_regs  Ptr. al bloque de registros del TIMER.
 *
 * @pre El TIMER debe estar inicializado antes de invocar esta función.
 */
void timer_poner_contador_a_0(LPC_TIM_TypeDef *timer_regs) {

  ASSERT(timer_regs == TIMER0 || timer_regs == TIMER1 || timer_regs == TIMER2 ||
             timer_regs == TIMER3,
         "TIMER seleccionado incorrecto");

  // Resetear las cuentas actuales
  // ===== COMPLETAR =====
}
