#define _GNU_SOURCE
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "sapi.h"            /* <= sAPI header */
//#include "board.h"

/**
 * Entrada boton subir por puerto DIN0

 */
#define SUBIR_IN 			DI0
#define BAJAR_IN			DI1
#define HABILITAR_AIRE_IN	DI2
#define CORTAR_AIRE_IN		DI3

#define SUBIR_OUT			DO0
#define BAJAR_OUT			DO1
#define HABILITAR_AIRE_OUT	DO2
#define CORTAR_AIRE_OUT		DO3


#define MUP_IN_PIN 		0x04
#define MUP_IN_PORT 	0x00
#define MUP_IN_FUNC 	FUNC0
#define MUP_IN_GPION 	0x02
#define MUP_IN_GPIOP 	0x00

/**
 * Salida subir por puerto DOUT0
 */
#define MUP_OUT_PIN 	0x02
#define MUP_OUT_PORT	0x01
#define MUP_OUT_FUNC 	FUNC4
#define MUP_OUT_GPION	0x05
#define MUP_OUT_GPIOP	0x01

/**
 * Entrada boton bajar por puerto DIN1
 */
#define MDOWN_IN_PIN 	0x04
#define MDOWN_IN_PORT 	0x01
#define MDOWN_IN_FUNC 	FUNC0
#define MDOWN_IN_GPION	0x02
#define MDOWN_IN_GPIOP	0x01

/**
 * Salida bajar por puerto DOUT1
 */
#define MDOWN_OUT_PIN 	0x04
#define MDOWN_OUT_PORT 	0x06
#define MDOWN_OUT_FUNC 	FUNC0
#define MDOWN_OUT_GPION	0x02
#define MDOWN_OUT_GPIOP	0x06
/*
#define MANIP_IN_PIN 	0x04
#define MANIP_IN_PORT 	0x02
#define MANIP_IN_FUNC 	FUNC0
#define MANIP_IN_GPION	0x02
#define MANIP_IN_GPIOP	0x02
*/

/**
 * Entrada boton habilitar aire por puerto DIN2
 */
#define AIRON_IN_PIN 	0x04
#define AIRON_IN_PORT 	0x02
#define AIRON_IN_FUNC 	FUNC0
#define AIRON_IN_GPION	0x02
#define AIRON_IN_GPIOP	0x02

/**
 * Salida habilitar aire por puerto DOUT2
 */
#define AIRON_OUT_PIN 	0x04
#define AIRON_OUT_PORT 	0x05
#define AIRON_OUT_FUNC 	FUNC0
#define AIRON_OUT_GPION	0x02
#define AIRON_OUT_GPIOP	0x05

/**
 * Entrada boton cerrar aire por puerto DIN3
 */
#define AIROFF_IN_PIN 	0x04
#define AIROFF_IN_PORT 	0x03
#define AIROFF_IN_FUNC 	FUNC0
#define AIROFF_IN_GPION	0x02
#define AIROFF_IN_GPIOP	0x03

/**
 * Salida cerrar aire por puerto DOUT3
 */
#define AIROFF_OUT_PIN 	0x04
#define AIROFF_OUT_PORT 	0x04
#define AIROFF_OUT_FUNC 	FUNC0
#define AIROFF_OUT_GPION	0x02
#define AIROFF_OUT_GPIOP	0x04

/*
#define MSTOP_IN_PIN 	0x04
#define MSTOP_IN_PORT 	0x03
#define MSTOP_IN_FUNC 	FUNC0
#define MSTOP_IN_GPION 	0x02
#define MSTOP_IN_GPIOP 	0x03
*/

#define NO_BUTTON_PRESSED	0X00
#define BUTTONS_UP		0X01
#define BUTTONS_DOWN	0X02
#define BUTTONS_DIS_AIR 0x03
#define BUTTONS_EN_AIR	0X04
//#define  0x05
typedef enum  inupt_states {PARAR, SUBIR, BAJAR, LIBERAR, CARGAR} inupt_states;



void incializarPuertos(void);

uint8_t loadCable();
uint8_t releaseCable();
uint8_t stopMotor();

uint8_t enableAir();
uint8_t disableAir();
uint8_t Button_GetStatus();
