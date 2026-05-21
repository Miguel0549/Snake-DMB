/**
 * @file  main.c
 *
 * @brief Modo sleep del LPC40xx (sección 3.12 del manual) y deshabilitar periféricos no utilizados
 * y activados por defecto (sección 3.3.2.2 del manual)
 *
 * @author
 * @date
 * @version
 *
 * @copyright GNU General Public License version 3 or later
 */

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "snake.h"

//Prototipos de funciones
void bajo_consumo(void);

int main(){

  //Definimos si necesitamos alguna variable local en el main

  //Desconectamos los periféricos no utilizados para disminuir el consumo
  bajo_consumo();

  //Inicializamos el resto de periféricos: i2c, uart, lcd, etc.

  glcd_inicializar();
  pintar_tablero();

  //Habilitamos las interrupciones globalmente
  __enable_irq();

  while(1){
    __wfi();  //Pasamos al modo Sleep hasta que ocurra una interrupción pero
              //siguen funcionando los periféricos (PWM, I2C, etc)

    //__wfe();  //Pasamos al modo DeepSleep hasta que ocurra una interrupción
          //NMI, EINT0-3, GPIO, RTC y demás recogidas en el 3.12.2. Se
          //detiene la ejecución de todos los periféricos excepto el RTC
  }
}

/**
 * @brief Función para disminuir el consumo apagando los periféricos no utilizados (UARTs,
 * interfaces I2C no utilizadas y el comparador analógico).
 *
 * @see   Tabla 16 del manual (sección 3.3.2.2)
 */
void bajo_consumo(void){
  //---------------------------------- UART0  UART1  I2C1  I2C2
  LPC_SC->PCONP &= (LPC_SC->PCONP & ~((1<<3)|(1<<4)|(1<<19)|(1<<26)));
  LPC_SC->PCONP1 = 0;//Comparador
}
