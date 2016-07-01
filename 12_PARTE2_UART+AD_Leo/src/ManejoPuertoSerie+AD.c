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
#include "ManejoPuertoSerie+AD.h"       /* <= own header */

#include "teclas.h"
#include "led.h"
#include "UART.h"
#include "timer.h"
#include "ADC.h"
#include "DAC.h"

#define TIEMPO_TIMER_RTI 1000//Tiempo en milisegundo del contador RTI
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//----------------------------------
//LEDS
	//Intancaimos e inicializamos el struc
	LED_1_2_3_RGB LEDS;


//----------------------------------
//Vector de letras para sacar palabras por pantalla
const uint8_t palabras[];
const uint8_t digitosAD[];
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
	uint16_t dato = Leer_Dato_ADC();
	enviarNumeroAlPuerto(dato);


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

uint16_t enviarNumeroAlPuerto(uint16_t num)
{
	/*
	//El salto de linea es ASCII es el 10
	const SL = 10;
	uint8_t C,D,U; //C=centena, D= decena, U=unidad

	C =  num /100;
	D = (num-C*100) /10;
	U = (num-C*100-D*10);

	uint8_t numero[5];

	numero[0] = '0'+ C;
	numero[1] = '0'+ D;
	numero[2] = '0'+ U;
	numero[3] = SL;
	*/

	DeterminarDigitos(num, &digitosAD);

	int i=0;
	for(i=0;i<strlen(digitosAD);i++)
	{
		enviarDatoAlPuerto(digitosAD[i]);
	}

	LimpiarDigitos(&digitosAD);

	return FIN_DEL_ENVIO;

}



void DeterminarDigitos(uint16_t num, uint8_t * Digitos)
{

	uint8_t ValorDigito = 0;
	uint8_t Dig=0;
	uint8_t pos = 0;//posición en la cadena;

	//El salto de linea es ASCII es el 10
		const SL = 10;

	while (num >= 1)
	{
		ValorDigito = num%10;
		Digitos[pos] = '0'+ ValorDigito;
		num -= ValorDigito;
		num /= 10;
		pos++;
	}

	Digitos[pos]=SL;


	uint8_t Aux;

	int i = 0;
	for (i = 0; i < strlen(Digitos) / 2; ++i)
	{
		Aux = Digitos[i];
		Digitos[i] = Digitos[(strlen(Digitos)-1) - i ];
		Digitos[(strlen(Digitos)-1) - i] = Aux;
	}
}

void LimpiarDigitos(uint8_t * Digitos)
{
	memset( Digitos, '\0', strlen(Digitos) );
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

	//Inicializamos el ADC
	InicializarADC();

	//Inicializamos la UART
	Inicializar_UART();


	//ARRANCAMOS UN CICLO INFINITO

	  while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

