#include "hw_handler.h"

/**
 * void incializarPuertos(void)
 * Configura e inicializa los puertos de la entrada y de salida
 */
void incializarPuertos(void)
{
	gpioConfig( SUBIR_IN , GPIO_INPUT_PULLUP);
	gpioConfig( BAJAR_IN, GPIO_INPUT_PULLUP);
	gpioConfig( HABILITAR_AIRE_IN, GPIO_INPUT_PULLUP);
	gpioConfig( CORTAR_AIRE_IN, GPIO_INPUT_PULLUP);

	gpioConfig( SUBIR_OUT, GPIO_OUTPUT);
	gpioConfig( BAJAR_OUT, GPIO_OUTPUT);
	gpioConfig( HABILITAR_AIRE_OUT, GPIO_OUTPUT);
	gpioConfig( CORTAR_AIRE_OUT, GPIO_OUTPUT);

	gpioWrite(SUBIR_IN , true);
	gpioWrite(BAJAR_IN , true);
	gpioWrite(HABILITAR_AIRE_IN , true);
	gpioWrite(CORTAR_AIRE_IN , true);

	gpioWrite(SUBIR_OUT,false);
	gpioWrite(BAJAR_OUT,false);
	gpioWrite(CORTAR_AIRE_OUT,false);
	gpioWrite(HABILITAR_AIRE_OUT,true);
}


uint8_t loadCable(){

	uint8_t res = 0x0;
	gpioWrite(BAJAR_OUT,0);
	gpioWrite(SUBIR_OUT,1);
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 1);
	return res;
}

uint8_t releaseCable()
{
	uint8_t res = 0x0;
	gpioWrite(SUBIR_OUT,0);
	gpioWrite(BAJAR_OUT,1);
		/*
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
	Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 1);*/
	return res;
}

uint8_t stopMotor()
{
	uint8_t res = 0x0;
	gpioWrite(SUBIR_OUT,0);
		gpioWrite(BAJAR_OUT,0);
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, MUP_OUT_GPION,MUP_OUT_GPIOP, 0);
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, MDOWN_OUT_GPION,MDOWN_OUT_GPIOP, 0);
	return res;
}

/**
 * uint8_t enableAir()
 * Habilita el aire
 */
uint8_t enableAir()
{
	uint8_t ret = 0x0;
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, AIROFF_OUT_GPION,AIROFF_OUT_GPIOP, 0);
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, AIRON_OUT_GPION,AIRON_OUT_GPIOP, 1);
	gpioWrite(CORTAR_AIRE_OUT,0);
	gpioWrite(HABILITAR_AIRE_OUT,1);
	return ret;
}


/**
 * uint8_t disableAir()
 * Desabilita el aire
 */
uint8_t disableAir()
{
	uint8_t ret = 0x0;
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, AIRON_OUT_GPION,AIRON_OUT_GPIOP, 0);
	//Chip_GPIO_SetPinState(LPC_GPIO_PORT, AIROFF_OUT_GPION,AIROFF_OUT_GPIOP, 1);

	gpioWrite(HABILITAR_AIRE_OUT,0);
	gpioWrite(CORTAR_AIRE_OUT,1);
	return ret;
}

/**
 * Funcion que se fija que boton esta siendo apretado.
 */
uint8_t Button_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;
	uint8_t post = NO_BUTTON_PRESSED;
	//if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, MUP_IN_GPION , (1<<MUP_IN_GPIOP)) == 0) {
	if (gpioRead(SUBIR_IN)) {
		ret = BUTTONS_UP;
	}
	//if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, MDOWN_IN_GPION , (1<<MDOWN_IN_GPIOP)) == 0) {
	if (gpioRead(BAJAR_IN)) {
		ret = BUTTONS_DOWN;
	}
	//if (Chip_GPIO_GetPinState(LPC_GPIO_PORT, AIROFF_IN_GPION , (1<<AIROFF_IN_GPIOP)) == 0) {
	if (gpioRead(CORTAR_AIRE_IN)) {
		ret = BUTTONS_DIS_AIR ;
	}
	if (gpioRead(HABILITAR_AIRE_IN)) {
		ret = BUTTONS_EN_AIR ;
	}

	return ret;
}
