/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a simple blink example.
 */

/** \addtogroup blink Bare-metal blink example
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"
//#include "sapi.h"            /* <= sAPI header */


/*==================[macros and definitions]=================================*/


/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/


/*==================[internal functions definition]==========================*/


/*==================[external functions definition]==========================*/

int main(void)
{
	boardConfig();
	/* Inicializar UART_USB a 115200 baudios */
	uartConfig( UART_USB, 115200 );
	uint8_t buffer[10];
	//delay_t delay;
	tick_t duration = 100;
	//delayConfig( &delay, 500 );
	incializarPuertos();
	BrazoState maquina = {.en_state = WAITING, .m_state = MANIPULATOR_HOLDING, .distance = 0, .msg=""};
	cambiarEngState(&maquina,WAITING);
	cambiarManipState(&maquina,MANIPULATOR_HOLDING);
	showState(&maquina);
	uint8_t butStat= 0;// = 0x00;
	uartWriteString( UART_USB, "Manipulador incializado \r\n" );
	engine_states engState_prev;// = maquina.en_state;
	manip_states manipState_prev;// = maquina.m_state;
	while (1)
	{
		butStat = 0x00;
		engState_prev = maquina.en_state;
		manipState_prev = maquina.m_state;

		butStat = Button_GetStatus();

		delay(duration);
		if (butStat!= Button_GetStatus())
			butStat = NO_BUTTON_PRESSED;
		if(uartReadByte( UART_USB, &buffer ))
		{
			if(buffer[0] == 'c')
				butStat = CARGAR;//BUTTONS_EN_AIR;
			else if(buffer[0] == 'l')
				butStat = LIBERAR;//BUTTONS_DIS_AIR;
			else if(buffer[0] == 's')
				butStat = SUBIR;//BUTTONS_UP;
			else if(buffer[0] == 'b')
				butStat = BAJAR;//BUTTONS_DOWN;
			else if(buffer[0] == 'p')
				butStat = PARAR;//BUTTONS_STOP;
			else if(buffer[0] == 'q')
				showState(&maquina);
		}
		switch(butStat)
		{
			case PARAR:
				cambiarEngState(&maquina,WAITING);
				//uartWriteString( UART_USB, "parar motor presionado \r\n" );
				break;
			case SUBIR: // 2
				cambiarEngState(&maquina,ENGINE_UP); // 1
				uartWriteString( UART_USB, "subiendo\r\n" );
				break;
			case BAJAR: // 4
				cambiarEngState(&maquina,ENGINE_DOWN); // 2
				uartWriteString( UART_USB, "bajando ... \r\n" );
				break;
			case CARGAR: // 8
				cambiarManipState(&maquina,MANIPULATOR_HOLDING);
				uartWriteString( UART_USB, "cargando placa ... \r\n" );
				break;
			case LIBERAR: // 16
				cambiarManipState(&maquina,MANIPULATOR_FREE);
				uartWriteString( UART_USB, "manipulador liberado ... \r\n" );
				break;
			default:
				cambiarEngState(&maquina,WAITING);
				cambiarManipState(&maquina,MANIPULATOR_HOLDING);
				break;
		}
		if ((engState_prev != maquina.en_state) || (manipState_prev != maquina.m_state) )
			showState(&maquina);
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
