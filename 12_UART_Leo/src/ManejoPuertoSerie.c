/* Copyright 2016, ManejoPuertoSerie
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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



/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "ManejoPuertoSerie.h"       /* <= own header */

#include "teclas.h"
#include "led.h"
#include "UART.h"
#include "timer.h"

#define TIEMPO_TIMER_RTI 1000//Tiempo en milisegundo del contador RTI
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//----------------------------------
//LEDS
	//Intancaimos e inicializamos el struc
	LED_1_2_3_RGB LEDS;


//----------------------------------
	//VARIABLES DEL TIMER RTI
	uint32_t contadorRTI=0;

const uint8_t palabras[];

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */
void InterrupcionRTI(void)
{
	uint8_t dato = leerPuerto();
	enviarNumeroAlPuerto(1235);
	ResponderAlCaracter(dato);

	//Borramos el flag de interrupción del timer RIT
	BorrarFlagTimerRIT();
}

uint8_t leerPuerto()
{
	return LeerByte_UART();
}

void enviarDatoAlPuerto(uint8_t dato)
{
	EnviarByte_UART(dato);
}

void enviarPalabraAlPuerto(uint8_t palabras[])
{
	int i;
	for(i=0;i<strlen(palabras);i++)
	{
		enviarDatoAlPuerto(palabras[i]);
	}
}

void enviarNumeroAlPuerto(uint8_t num)
{
	uint8_t numero[4];

	numero[0] = '0'+ num % 10;
	numero[1] = '0'+ num % 100 / 10;
	numero[2] = '0'+ num % 1000 / 100;
	numero[3] = '0'+ num % 10000 / 1000;

	int i;
	for(i=0;i<strlen(numero);i++)
	{
		enviarDatoAlPuerto(numero[i]);
	}
}


uint8_t ResponderAlCaracter(uint8_t dato)
{
	switch(dato)
		{
		case 'a':
			//Definimos al led uno para que cambie de estado
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = PRENDIDO;
			LEDS.LED_DOS = APAGADO;
			LEDS.LED_TRES = APAGADO;
			cambiarEstado(&LEDS);

			apagarLed(LED2);
			apagarLed(LED3);

			enviarPalabraAlPuerto("HOLA MUNDO");
			break;
		case 'r':
			//Definimos al led dos para que cambie de estado
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = APAGADO;
			LEDS.LED_DOS = PRENDIDO;
			LEDS.LED_TRES = APAGADO;
			cambiarEstado(&LEDS);

			apagarLed(LED1);
			apagarLed(LED3);
			enviarPalabraAlPuerto("HOLA MUNDO");
			break;
		case 'v':
			//Definimos al led dos para que cambie de estado
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = APAGADO;
			LEDS.LED_DOS = APAGADO;
			LEDS.LED_TRES = PRENDIDO;
			cambiarEstado(&LEDS);
			apagarLed(LED1);
			apagarLed(LED2);
			enviarPalabraAlPuerto("HOLA MUNDO");
			break;
		default:
			return FALSE;
			break;
		}

	return TRUE;
}

int main(void)
{
	uint8_t INICIOLEDS;

	//Inicializamos los puertos de LED
	INICIOLEDS = inicializarPuertos();

	LEDS.ledR = APAGADO;
	LEDS.ledG = APAGADO;
	LEDS.ledB = APAGADO;
	LEDS.LED_UNO = APAGADO;
	LEDS.LED_DOS = APAGADO;
	LEDS.LED_TRES = APAGADO;

	cambiarEstado(&LEDS);

	//Inicializamos los TIMERS y definimos el intervalo
	InicializarTimers();
	DefinirIntervaloRTI(TIEMPO_TIMER_RTI);


	//Inicializamos la UART
	Inicializar_UART();


	//ARRANCAMOS UN CICLO INFINITO

	  while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

