/**
 * @file    glcd.h
 * @brief   Funciones de manejo del LCD de 4.3" desde la tarjeta Embedded Artist Developer's Kit.
 *
 * @author  Alejandro Lara Doña - alejandro.lara@uca.es | Eduardo Romero
 * @date    2014/2025
 * @version 2.0
 *
 * @copyright GNU General Public License version 3 or later
 */

#ifndef GLCD_H
#define GLCD_H

#include <stdio.h>
#include "tipos.h"
#include "sdram.h"
#include "fuente.h"

// ===== GLCD - Constantes Publicas =====
/**
 * @brief   Dirección de la SDRAM donde comienza el espacio reservado para la imágen en pantalla.
 * @ingroup GLCD
 */
#define GLCD_VRAM_BASE_ADDR (SDRAM_BASE + 0x0010000)

/**
 * @brief   Parámetros de la LCD y ajustes indicados para el controlador de la LCD del LPC4088.
 * @ingroup GLCD
 *
 * @see     LCD BOARD - User's guide página 13.
 */
enum glcd_parametros {
  // Parámetros de la LCD
  GLCD_PIXELES_POR_LINEA  = 480,  //!< Num. píxeles por linea horizontal.
  GLCD_LINEAS_POR_PANEL   = 272,  //!< Num. lineas horizontales en el panel.

  // Ajustes del controlador
  GLCD_HSYNC_PULSE_WIDTH  = 2u,   //!< Anchura del pulso de sincronismo horizontal.
  GLCD_HSYNC_FRONT_PORCH  = 5u,   //!< Número de ciclos al final de cada línea.
  GLCD_HSYNC_BACK_PORCH   = 40u,  //!< Número de ciclos al comienzo de cada línea.

  GLCD_VSYNC_PULSE_WIDTH  = 2u,   //!< Anchura del pulso de sincronismo vertical.
  GLCD_VSYNC_FRONT_PORCH  = 8u,   //!< Número de ciclos al finalizar la actualización de la pantalla.
  GLCD_VSYNC_BACK_PORCH   = 8u,   //!< Número de ciclos al inicio de la actualización de la pantalla.

  GLCD_INVERTIR_SALIDA    = 0u,   //!< No invertir la polaridad de las señales.
  GLCD_INVERTIR_RELOJ     = 0u,   //!< No invertir la señal de reloj.
  GLCD_INVERTIR_HSYNC     = 1u,   //!< Invertir la señal de sincronismo horizontal.
  GLCD_INVERTIR_VSYNC     = 1u,   //!< Invertir la señal de sincronismo vertical.
  GLCD_CICLOS_POR_LINEA   = GLCD_PIXELES_POR_LINEA,   //!< Num. ciclos de reloj por linea.
  GLCD_RELOJ_LCD          = 9000000                   //!< Reloj óptimo según datasheet 9 MHz.
};

/**
 * @brief   Límites de la LCD.
 * @ingroup GLCD
 */
enum glcd_tamano {
  GLCD_TAMANO_X = GLCD_PIXELES_POR_LINEA,   //!< Num. píxeles en horizontal.
  GLCD_TAMANO_Y = GLCD_LINEAS_POR_PANEL,    //!< Num. píxeles en vertical.
  GLCD_X_MINIMO = 0,                        //!< Píxel inicial en horizontal.
  GLCD_X_MAXIMO = (GLCD_TAMANO_X - 1),      //!< Píxel máximo en horizontal.
  GLCD_Y_MINIMO = 0,                        //!< Píxel inicial en vertical.
  GLCD_Y_MAXIMO = (GLCD_TAMANO_Y - 1)       //!< Píxel máximo en vertical.
};

/**
 * @brief   Bits del registro CTRL del módulo LCD del LPC4088.
 * @ingroup GLCD
 */
enum glcd_ctrl_bits {
  GLCD_CTRL_EN_BIT        = (1u << 0),    //!< Bit LCD Enable.
  GLCD_CTRL_BPP           = 1,            //!< Selector de bits por pixel.
  GLCD_CTRL_BW_BIT        = (1u << 4),    //!< Panel monocromo(1)/color.
  GLCD_CTRL_TFT_BIT       = (1u << 5),    //!< Panel TFT(1)/STN.
  GLCD_CTRL_MONO8_BIT     = (1u << 6),    //!< Panel monocromo de 8bits(1)/4bits.
  GLCD_CTRL_LCDDUAL_BIT   = (1u << 7),    //!< Dual panel(1)/single panel.
  GLCD_CTRL_BGR_BIT       = (1u << 8),    //!< Formato de color BGR(1)/RGB.
  GLCD_CTRL_BYTEORDER_BIT = (1u << 9),    //!< Formato de byte big-endian(1)/little-endian.
  GLCD_CTRL_BITORDER_BIT  = (1u << 10),   //!< Orden de bits big-endian(1)/little-endian.
  GLCD_CTRL_PWR_BIT       = (1u << 11)    //!< Bit LCD Power.
};

/**
 * @brief   Constantes para seleccionar el número de bits por píxel de la LCD.
 * @ingroup GLCD
 */
enum glcd_bits_por_pixel {
  GLCD_BPP_1   = 0,   //!< 1 bpp.
  GLCD_BPP_2   = 1u,  //!< 2 bpp.
  GLCD_BPP_4   = 2u,  //!< 4 bpp.
  GLCD_BPP_8   = 3u,  //!< 8 bpp.
  GLCD_BPP_16  = 4u,  //!< 16 bpp.
  GLCD_BPP_24  = 5u,  //!< 24 bpp (TFT panel only).
  GLCD_BPP_565 = 6u,  //!< 16 bpp, 5:6:5 mode.
  GLCD_BPP_12  = 7u   //!< 12 bpp, 4:4:4 mode.
};

/**
 * @brief   Bits del registro POL (configuración del reloj) del módulo LCD del LPC4088.
 * @ingroup GLCD
 */
enum glcd_pol_bits {
  GLCD_POL_PCD_LO       = 0,            //!< 5 bits más bajos del divisor de reloj del panel.
  GLCD_POL_CLKSEL_BIT   = (1u << 5),    //!< Selector del reloj externo(1)/CCLK.
  GLCD_POL_ACB          = 6,            //!< Frecuencia de la polarizacón AC (panel STN).
  GLCD_POL_IVS_BIT      = (1u << 11),   //!< Invertir sincronismo vertical.
  GLCD_POL_IHS_BIT      = (1u << 12),   //!< Invertir sincronismo horizontal.
  GLCD_POL_IPC_BIT      = (1u << 13),   //!< Invertir reloj.
  GLCD_POL_IOE_BIT      = (1u << 14),   //!< Invertir señales de salida.
  GLCD_POL_CPL          = 16,           //!< Num. ciclos de reloj por linea.
  GLCD_POL_BCD_BIT      = (1u << 26),   //!< Ignorar el divisor de reloj.
  GLCD_POL_PCD_HI       = 27            //!< 5 bits más altos del divisor de reloj del panel
};

/**
 * @brief   Convertir el color RGB de 24 bits (8:8:8) al de resolución de 16 bits (5:6:5).
 * @ingroup GLCD
 *
 * @param[in]  r  Intensidad de rojo 0-255.
 * @param[in]  g  Intensidad de verde 0-255.
 * @param[in]  b  Intensidad de azul 0-255.
 *
 * @return    Color en formato RGB de 16 bits.
 *
 * @warning   r, g y b deben ser de 8 bits.
 */
#define RGB(r, g, b)    ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b) & 0xF8) >> 3))

/**
 * @brief   Constantes de los colores más comunes en español e inglés a partir de sus valores RGB.
 * @ingroup GLCD
 */
enum glcd_color_t {
  NEGRO =         RGB(0, 0, 0),
  AZUL_OSCURO =   RGB(0, 0, 128),
  VERDE_OSCURO =  RGB(0, 128, 0),
  CIAN_OSCURO =   RGB(0, 128, 128),
  MARRON =        RGB(128, 0, 0),
  PURPURA =       RGB(128, 0, 128),
  OLIVA =         RGB(128, 255, 0),
  NARANJA =       RGB(255, 128, 0),
  GRIS_CLARO =    RGB(192, 192, 192),
  GRIS_OSCURO =   RGB(128, 128, 128),
  AZUL =          RGB(0, 0, 255),
  VERDE =         RGB(0, 255, 0),
  CIAN =          RGB(0, 255, 255),
  ROJO =          RGB(255, 0, 0),
  MAGENTA =       RGB(255, 0, 255),
  AMARILLO =      RGB(255, 255, 0),
  BLANCO =        RGB(255, 255, 255),
  BLACK =         RGB(0, 0, 0),
  DARKBLUE =      RGB(0, 0, 128),
  DARKGREEN =     RGB(0, 128, 0),
  DARKCYAN =      RGB(0, 128, 128),
  MAROON =        RGB(128, 0, 0),
  PURPLE =        RGB(128, 0, 128),
  OLIVE =         RGB(128, 255, 0),
  ORANGE =        RGB(255, 128, 0),
  LIGHTGREY =     RGB(192, 192, 192),
  DARKGREY =      RGB(128, 128, 128),
  BLUE =          RGB(0, 0, 255),
  GREEN =         RGB(0, 255, 0),
  CYAN =          RGB(0, 255, 255),
  RED =           RGB(255, 0, 0),
  YELLOW =        RGB(255, 255, 0),
  WHITE =         RGB(255, 255, 255)
};

/**
 * @brief   Constantes para los diferentes tamaños de fuentes de caracteres disponibles.
 * @ingroup GLCD
 */
enum fuentes_lcd {
  FUENTE8X16 = 0,   //!< Fuente pequeña (8 píxeles de ancho y 16 de alto).
  FUENTE12X24 = 1,  //!< Fuente mediana (12 píxeles de ancho y 24 de alto).
  FUENTE16X32 = 2   //!< Fuente grande (16 píxeles de ancho y 32 de alto).
};

/**
 * @brief   Número de fuentes disponibles.
 * @ingroup GLCD
 */
#define NUMERO_FUENTES  3

// ===== GLCD - Tipos Publicos =====
/**
 * @brief   Estructura para almacenar la configuración de la LCD (color, fuente y posición) para
 * la salida de texto mediante glcd_printf.
 * @ingroup GLCD
 */
typedef struct {
  uint16_t color;
  uint16_t color_fondo;
  uint32_t fuente;
  uint16_t pos_x;
  uint16_t pos_y;
  bool_t desplazamiento_activado;
} glcd_config_texto_t;


/**
 * @defgroup  GLCD_PCA9532 GLCD - Constantes del PCA9532
 * @ingroup   GLCD
 * @private
 * @brief     Constantes para utilizar el expansor de pines PCA9532.
 * @details  Este dispositivo permite generar las señales de control de "reset" y "display_enable",
 * controlar la tensión de alimentación a la LCD (3.3V o 5V) e intensidad de la retroiluminación de
 * la pantalla LCD (genera una señal PWM el propio PCA9532).
 * @{
 */
#define GLCD_PCA9532_I2C_ADDR   0x64  //!< Dirección I2C del PCA9532 de la LCD.

/**
 * @brief     Bit de Autoincremento
 * @details   Permite acceder a los registros secuencialmente sin reiniciar la comunicación.
 */
#define GLCD_PCA9532_AUTO_INC   0x10

/**
 * @brief   Direcciones de los registros del PCA9532.
 */
enum glcd_pca9532_registros {
  GLCD_PCA9532_INPUT0 = 0x00,
  GLCD_PCA9532_INPUT1 = 0x01,
  GLCD_PCA9532_PSC0 = 0x02,
  GLCD_PCA9532_PWM0 = 0x03,
  GLCD_PCA9532_PSC1 = 0x04,
  GLCD_PCA9532_PWM1 = 0x05,
  GLCD_PCA9532_LS0 = 0x06,
  GLCD_PCA9532_LS1 = 0x07,
  GLCD_PCA9532_LS2 = 0x08,
  GLCD_PCA9532_LS3 = 0x09
};

/**
 * @brief   Modos de las salidas del PCA9532.
 */
enum glcd_pca9532_ls_modos {
  GLCD_LS_MODO_OFF = 0x00,      //!< Salida en alta impedancia (LED off). Valor por defecto.
  GLCD_LS_MODO_ON = 0x01,       //!< Salida a nivel bajo (LED on).
  GLCD_LS_MODO_PWM0 = 0x02,   //!< Salida controlada por el PWM0
  GLCD_LS_MODO_PWM1 = 0x03    //!< Salida controlada por el PWM1
};

/**
 * @brief   Constantes para generar las señales de control de la LCD con el PCA9532.
 */
enum glcd_pca9532_ctrl {
  GLCD_PCACTRL_3V3 = 0x0001,       //!< Alimentación de la pantalla LCD a 3.3V
  GLCD_PCACTRL_5V = 0x0002,        //!< Alimentación de la pantalla LCD a 5V
  GLCD_PCACTRL_DISP_EN = 0x0010,   //!< Generar la señal "display_enable"
  GLCD_PCACTRL_BL_EN = 0x0080,     //!< Habilitar la retroiluminación
  GLCD_PCACTRL_BL_C = 0x0100       //!< Señal de control del contraste de la LCD
};
//!@}

/**
 * @name      No Semihosting
 * @brief     Deshabilitar la funcionalidad de semihosting de ARM para el compilador ARM v6 o v5.
 * @details   La funcionalidad de semihosting es un mecanismo de depuración que permite que un
 * dispositivo ARM target (embebido) se comunique con un host (PC) para realizar operaciones de
 * E/S, como printf, a través del depurador. Al deshabilitar el semihosting, el compilador se
 * asegura de que las funciones que dependen de él no se incluyan, liberando memoria y eliminando
 * la necesidad de la conexión del host, lo cual es útil en entornos de producción o cuando se
 * desea una mayor independencia del host durante la depuración.
 *
 * Si se deshabilita el semihosting las funciones que lo utilizan se deben reimplementar enviandolas
 * a la UART, LCD u otras salidas. El Linker lanzará un error indicando la función que utiliza 
 * semihosting que no se ha reimplementado.
 *
 * Ejemplo:
 *
 *```c
 *  int fputc(int ch, FILE *f) {
 *    unsigned char tempch = ch;
 *    if (tempch == '\n') {
 *      uart_putc_polled('\r');
 *    }
 *    uart_putc_polled(tempch);
 *    return ch;
 *  }
 *```
 * @{
 */
#if (__ARMCC_VERSION >= 6000000L)
  __asm(".global __use_no_semihosting\n\t");  //!< Versión 6 del compilador
#else
  #pragma import(__use_no_semihosting_swi)    //!< Versión 5 del compilador
#endif

// ===== Reimplementación de funciones que utilizan semihosting =====
/**
 * @brief   Sobrecarga la estructra de archivos (FILE).
 */
/*
struct __FILE{
  int handle;
};
*/

int32_t fputc(int c, FILE *file);
int32_t fgetc(FILE *file);
int32_t ferror(FILE *file);
void _sys_exit(int32_t return_code);
//!@}

// ===== GLCD - Funciones Publicas =====
/**
 * @brief   Inicializa el controlador LCD.
 * @ingroup GLCD
 */
void glcd_inicializar(void);

/**
 * @brief   Borra la pantalla LCD rellenándola con el color indicado.
 * @ingroup GLCD
 *
 * @param[in]   color   color con el que rellenar la pantalla LCD.
 */
void glcd_borrar(uint16_t color);

/**
 * @brief   Función análoga a printf para imprimir texto en la pantalla LCD.
 * @ingroup GLCD
 *
 * @param[in]   format  Cadena de caracteres a imprimir incluyendo opcionalmente especificadores
 *                      de formato que serán reemplazados por los valores de los argumentos
 *                      adicionales subsiguientes y formateados como se indique.
 * @param[in]   ...     Argumentos adicionales. Dependiendo de los especificadores de formato
 *                      incluidos en la cadena de formato, la función espera una secuencia de
 *                      argumentos adicionales cuyos valores se usan para reemplazar dichos
 *                      especificadores. Debe haber, al menos, tantos argumentos adicionales
 *                      como especificadores de formato. Los argumentos extra a los necesarios
 *                      son ignorados.
 *
 * @return  Si la función tiene éxito, retorna el número de caracteres que ha impreso. En caso de
 * error, se retorna un número negativo.
 */
int32_t glcd_printf(const char *format, ...);

/**
 * @brief   Función parecida a glcd_printf pero pudiendo indicar las coordedadas donde aparece
 * el texto, el color del texto y la fuente.
 * @ingroup GLCD
 *
 * @param[in]   x             Coordenada X de pantalla en la que se imprimirá.
 * @param[in]   y             Coordenada Y de pantalla en la que se imprimirá.
 * @param[in]   color         Color con el que se imprimirá el texto.
 * @param[in]   color_fondo   Color de fondo con el que se imprimirá el texto.
 * @param[in]   fuente        Fuente de caracteres con la que se imprimirá.
 * @param[in]   format        Cadena de caracteres a imprimir incluyendo opcionalmente
 *                            especificadores de formato que serán reemplazados por los valores de
 *                            los argumentos subsiguientes y formateados como se indique.
 * @param[in]   ...           Argumentos adicionales. Dependiendo de los especificadores de formato
 *                            incluidos en la cadena de formato, la función espera una secuencia de
 *                            argumentos adicionales cuyos valores se usan para reemplazar dichos
 *                            especificadores. Debe haber, al menos, tantos argumentos adicionales
 *                            como especificadores de formato. Los argumentos extra a los
 *                            necesarios se ignoran.
 *
 * @return  Si la función tiene éxito, retorna el número de caracteres que ha impreso. En caso de 
 * error, se retorna un número negativo.
 *
 * @note  No se actualiza la configuración actual de colores o posición de la LCD.
 */
int32_t glcd_xprintf(uint16_t x, uint16_t y, uint16_t color, uint16_t color_fondo, uint32_t fuente,
                     const char *format, ...);

/**
 * @brief   Imprime un carácter en pantalla. No se interpretan caracteres de control.
 * @ingroup GLCD
 *
 * @param[in]   c             Carácter a imprimir. Sólo se imprimirá si es uno de los caracteres
 *                            definidos en la fuente indicada por el argumento fuente y las
 *                            coordenadas indicadas por los argumentos `x` e `y` están dentro de
 *                            la pantalla. En caso contrario no se imprimirá nada.
 * @param[in]   x             Coordenada X de pantalla en la que se imprimirá.
 * @param[in]   y             Coordenada Y de pantalla en la que se imprimirá.
 * @param[in]   color         Color con el que se imprimirá el carácter.
 * @param[in]   color_fondo   Color de fondo con el que se imprimirá el carácter.
 * @param[in]   fuente        Fuente de caracteres con la que se imprimirá.
 */
void glcd_caracter(char c, uint16_t x, uint16_t y, uint16_t color, uint16_t color_fondo,
                   uint32_t fuente);

/**
 * @brief   Imprime una cadena de caracteres en la pantalla LCD. No se interpretan los caracteres
 * de control.
 * @ingroup GLCD
 *
 * @param[in]   x             Coordenada X de pantalla en la que se imprimirá.
 * @param[in]   y             Coordenada Y de pantalla en la que se imprimirá.
 * @param[in]   color         Color con el que se imprimirá el carácter.
 * @param[in]   color_fondo   Color de fondo con el que se imprimirá el carácter.
 * @param[in]   fuente        Fuente de caracteres con la que se imprimirá.
 * @param[in]   str           Puntero a la cadena a imprimir. Sólo se imprimirá si las coordenadas
 *                            indicadas por los argumentos `x` e `y` están dentro de la pantalla.
 *                            En caso contrario, no se imprimirá nada.
 */
void glcd_texto(uint16_t x, uint16_t y, uint16_t color, uint16_t color_fondo, uint32_t fuente,
                const char *str);

/**
 * @brief   Fija el color que se usará para la salida de texto con glcd_printf.
 * @ingroup GLCD
 *
 * @param[in]   color   Color de texto que usará glcd_printf.
 */
void glcd_color_texto(uint16_t color);

/**
 * @brief   Fija el color de fondo que se usará para la salida de texto con glcd_printf.
 * @ingroup GLCD
 *
 * @param[in]   color_fondo   Color de fondo que usará glcd_printf.
 */
void glcd_fondo_texto(uint16_t color_fondo);

/**
 * @brief   Fija las coordenadas en las que se mostrará el texto en la siguiente llamada a
 * `glcd_printf`. Sólo tiene efecto si las coordenadas están dentro de la pantalla.
 * @ingroup GLCD
 *
 * @param[in]   x   Coordenada X de la pantalla.
 * @param[in]   y   Coordenada Y de la pantalla.
 */
void glcd_xy_texto(uint16_t x, uint16_t y);

/**
 * @brief   Desplaza hacia arriba el contenido de la pantalla un determinado número de líneas.
 * Las líneas inferiores se rellenan con el color del fondo de texto actual.
 * @ingroup GLCD
 *
 * @param[in]   lineas  Líneas a desplazar.
 */
void glcd_desplazar(uint16_t lineas);

/**
 * @brief   Activa o desactiva el desplazamiento automático hacia arriba del contenido de la
 * pantalla cuando la salida de texto mediante glcd_printf sobrepasa la linea inferior.
 * @ingroup GLCD
 *
 * @param[in]   activar   TRUE => activar, FALSE => desactivar.
 */
void glcd_activar_desplazamiento(bool_t activo);

/**
 * @brief   Selecciona la fuente de caracteres que se usará para la salida de texto mediante
 * la función `glcd_printf`.
 * @ingroup GLCD
 *
 * @param[in]   fuente  Número de la fuente a seleccionar.
 */
void glcd_seleccionar_fuente(uint32_t fuente);

/**
 * @brief   Dibuja un punto (pixel) en la pantalla LCD.
 * @ingroup GLCD
 *
 * @param[in]   x       Coordenada X del punto.
 * @param[in]   y       Coordenada Y del punto.
 * @param[in]   color   Color del punto.
 */
void glcd_punto(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief   Dibuja en la pantlla LCD un segmento de línea recta definido por las coordenadas de
 * sus extremos. Si las coordenadas de uno o ambos extremos del segmento están fuera de la pantalla
 * se dibuja la porción contenida en la misma (si la hay).
 * @ingroup GLCD
 *
 * @param[in]   x0      Coordenada X del primer extremo del segmento.
 * @param[in]   y0      Coordenada Y del primer extremo del segmento.
 * @param[in]   x1      Coordenada X del segundo extremo del segmento.
 * @param[in]   y1      Coordenada Y del segundo extremo del segmento.
 * @param[in]   color   Color del segmento.
 */
void glcd_linea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * @brief   Dibuja en la pantalla LCD un rectángulo definido por las coordenadas de los vértices
 * de una diagonal. Se dibuja la porción del rectángulo contenida entre los límites de la pantalla.
 * @ingroup GLCD
 *
 * @param[in]   x0      Coordenada X de un vértice.
 * @param[in]   y0      Coordenada Y de un vértice.
 * @param[in]   x1      Coordenada X del vértice opuesto al dado por (x0, y0).
 * @param[in]   y1      Coordenada Y del vértice opuesto al dado por (x0, y0).
 * @param[in]   color   Color del rectángulo.
 */
void glcd_rectangulo(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * @brief   Dibuja en la pantalla LCD un rectángulo relleno definido por las coordenadas de los
 * vértices de una diagonal. Se dibuja la porción del rectángulo contenida en los límites de la
 * pantalla.
 * @ingroup GLCD
 *
 * @param[in]   x0      Coordenada X de un vértice.
 * @param[in]   y0      Coordenada Y de un vértice.
 * @param[in]   x1      Coordenada X del vértice opuesto al dado por (x0, y0).
 * @param[in]   y1      Coordenada Y del vértice opuesto al dado por (x0, y0).
 * @param[in]   color   Color del rectángulo.
 */
void glcd_rectangulo_relleno(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

/**
 * @brief   Dibuja una circunferencia en la pantalla LCD. Se dibuja la parte de la circunferencia
 * contenida entre los límites de la pantalla.
 * @ingroup GLCD
 *
 * @param[in]   xc      Coordenada X del centro.
 * @param[in]   yc      Coordenada Y del centro.
 * @param[in]   radio   Radio de la circunferencia (en píxeles).
 * @param[in]   color   Color de la circunferencia.
 */
void glcd_circunferencia(uint16_t xc, uint16_t yc, uint16_t radio, uint16_t color);

/**
 * @brief   Dibuja un circulo relleno en la pantalla LCD. Se dibuja la parte del cículo contenido
 * entre los límites de la pantalla.
 * @ingroup GLCD
 *
 * @param[in]   xc      Coordenada X del centro.
 * @param[in]   yc      Coordenada Y del centro.
 * @param[in]   radio   Radio del circulo (en píxeles).
 * @param[in]   color   Color del circulo.
 */
void glcd_circulo(uint16_t xc, uint16_t yc, uint16_t radio, uint16_t color);

#endif  // GLCD_H
