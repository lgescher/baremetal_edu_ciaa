/* Copyright 2016, ADporPooling
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
#include "ADporPooling.h"       /* <= own header */

#include "led.h"
#include "ADC.h"
#include "UART.h"
#define TIEMPO_TIMER_RTI 2000//Tiempo en milisegundo del contador RTI
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//----------------------------------
//LEDS
	//Intancaimos e inicializamos el struc
	LED_1_2_3_RGB LEDS;

//----------------------------------
//Vector de letras para sacar palabras por pantalla
const uint8_t palabras[];

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


void InterrupcionRTI(void)
{
	uint16_t dato_Del_ADC = leerDatoAnalogico();
	enviarNumeroAlPuerto(dato_Del_ADC);
	ResponderAlDatoAnalogico(dato_Del_ADC);
}

uint16_t leerDatoAnalogico(void)
{
	return Leer_Dato_ADC();
}

void ResponderAlDatoAnalogico(uint16_t dato)
{
	if(dato<100)
	{
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

	}
	else
	{
		if(dato>1000)
		{
			//Definimos al led tres para que cambie de estado
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = APAGADO;
			LEDS.LED_DOS = APAGADO;
			LEDS.LED_TRES = PRENDIDO;
			cambiarEstado(&LEDS);

			apagarLed(LED1);
			apagarLed(LED2);

		}
		else
		{
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
		}
	}
}

void enviarDatoAlPuerto(uint8_t dato)
{
	EnviarByte_UART(dato);
}

void enviarNumeroAlPuerto(uint16_t num)
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

	//Inicializamos el ADC
	InicializarADC();



	//ARRANCAMOS UN CICLO INFINITO

	  while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

