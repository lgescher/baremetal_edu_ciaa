/* Copyright 2016, manejoTeclas Leandro Escher
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
#include "manejoDeTeclado.h"       /* <= own header */

#include "led.h"
#include "teclas.h"

#define CANTIDAD_TECLAS 4

#define PRENDIDO  1
#define APAGADO  0
#define PULSADO  0
#define NO_PULSADO  1
#define CAMBIO_DE_ESTADO  0
#define SIN_CAMBIOS  0

#define POS_TECLA_1  0 //posición de la tecla 1 en el vector de teclas
#define POS_TECLA_2  1 //posición de la tecla 2 en el vector de teclas
#define POS_TECLA_3  2 //posición de la tecla 3 en el vector de teclas
#define POS_TECLA_4  3 //posición de la tecla 4 en el vector de teclas
#define CERO 0

#define TIEMPO_TIMER_RTI 1//Tiempo en milisegundo del contador RTI
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//----------------------------------
// LED
	//Instancaimos el struc de LED
	LED_1_2_3_RGB LEDS;


//----------------------------------
	//TECLAS

	//Instanciamos e inicializamos el struc de TECLAS
	TECLAS_1_2_3_4 TECLAS;



	//Definimos los vectores de Estado
	uint8_t ESTADO_TECLAS_PASADO [CANTIDAD_TECLAS];
	uint8_t ESTADO_TECLAS_ACTUAL [CANTIDAD_TECLAS];

	uint8_t TECLA_PULSADA= SIN_CAMBIOS;

	//VARIABLES DEL TIMER RTI
	uint32_t contadorRTI=0;
	uint8_t  TU =700;//tiempo en milisegundos
	uint8_t  TL =1000;//tiempo en milisegundos
	uint8_t  TC =500;//tiempo en milisegundos
	uint8_t cantidadTL=0; //Es la catidad de veces que se va a repetir el tiempo TL
	//definimos un tiempo de espera
	uint32_t tiempoDeEspera = 0;
	uint32_t espera=0;

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


uint8_t VerificarEstado(void)
{
	//Escanea teclado y lo guardamos como un estado pasado
	EscanearTeclado(&TECLAS);
	ESTADO_TECLAS_ACTUAL[POS_TECLA_1] = TECLAS.tec1;
	ESTADO_TECLAS_ACTUAL[POS_TECLA_2] = TECLAS.tec2;
	ESTADO_TECLAS_ACTUAL[POS_TECLA_3] = TECLAS.tec3;
	ESTADO_TECLAS_ACTUAL[POS_TECLA_4] = TECLAS.tec4;

	TECLA_PULSADA = DetectarCambio();

	if(TECLA_PULSADA)
	{

		if(TECLA_PULSADA==TEC4)
		{
			comportamiento1(TECLA_PULSADA);
		}
		if(TECLA_PULSADA==TEC3)
		{
			comportamiento2(TECLA_PULSADA);
		}
		if(TECLA_PULSADA==TEC2)
		{
			comportamiento3(TECLA_PULSADA);
		}

	}
	ActualizarEstadoPasado();
	//Cuenta
	contadorRTI++;
}

uint8_t DetectarCambio(void)
{
	if(EstadoTecla(TEC1)==PULSADO)
	{
		return TEC1;
	}
	if(EstadoTecla(TEC2)==PULSADO)
	{
		return TEC2;
	}
	if(EstadoTecla(TEC3)==PULSADO)
	{
		return TEC3;
	}
	if(EstadoTecla(TEC4)==PULSADO)
	{
		return TEC4;
	}
	return SIN_CAMBIOS;
}

void ActualizarEstadoPasado(void)
{
	int i=0;
	for(i=CANTIDAD_TECLAS;i>0;i--)
	{
		ESTADO_TECLAS_PASADO [i] = ESTADO_TECLAS_ACTUAL [i];
	}
}

uint8_t GetEstadoPasado(uint8_t numTec)
{
	uint8_t ESTADO = CERO;

	switch(numTec)
	{
	case TEC1:
		ESTADO = ESTADO_TECLAS_PASADO [POS_TECLA_1];
		break;
	case TEC2:
		ESTADO = ESTADO_TECLAS_PASADO [POS_TECLA_2];
		break;
	case TEC3:
		ESTADO = ESTADO_TECLAS_PASADO [POS_TECLA_3];
		break;
	case TEC4:
		ESTADO = ESTADO_TECLAS_PASADO [POS_TECLA_4];
		break;
	default:
		return CERO;
		break;
	}
	return ESTADO;
}

void comportamiento1(TECLA_PULSADA)
{
	if(GetEstadoPasado(TECLA_PULSADA)==NO_PULSADO && ESTADO_TECLAS_ACTUAL [TECLA_PULSADA]==PULSADO)
	{
		if(LEDS.LED_TRES==APAGADO)
		{
			prenderLed(LED3);
			LEDS.LED_TRES=PRENDIDO;
			apagarLed(LED2);
			LEDS.LED_TRES=APAGADO;
		}
		else
		{
			prenderLed(LED2);
			LEDS.LED_DOS=PRENDIDO;
			apagarLed(LED3);
			LEDS.LED_TRES=APAGADO;
		}
	}
}

void comportamiento2(TECLA_PULSADA)
{
	if(GetEstadoPasado(TECLA_PULSADA)==NO_PULSADO && ESTADO_TECLAS_ACTUAL [TECLA_PULSADA]==PULSADO)
	{
		if(LEDS.LED_TRES==APAGADO)
		{
			prenderLed(LED3);
			LEDS.LED_TRES=PRENDIDO;
		}
		else
		{
			apagarLed(LED3);
			LEDS.LED_TRES=APAGADO;
		}
	contadorRTI=0;
	}
	if(GetEstadoPasado(TECLA_PULSADA)==PULSADO && ESTADO_TECLAS_ACTUAL [TECLA_PULSADA]==PULSADO)
	{
		if(contadorRTI>TU)
		{
			if(LEDS.LED_TRES==APAGADO)
			{
				prenderLed(LED3);
				LEDS.LED_TRES=PRENDIDO;
			}
			else
			{
				apagarLed(LED3);
				LEDS.LED_TRES=APAGADO;
			}

		contadorRTI=0;
		}
	}
}

void comportamiento3(TECLA_PULSADA)
{

	if(GetEstadoPasado(TECLA_PULSADA)==NO_PULSADO && ESTADO_TECLAS_ACTUAL [TECLA_PULSADA]==PULSADO)
	{
		if(LEDS.LED_TRES==APAGADO)
		{
			prenderLed(LED3);
			LEDS.LED_TRES=PRENDIDO;
		}
		else
		{
			apagarLed(LED3);
			LEDS.LED_TRES=APAGADO;
		}
	contadorRTI=0;
	}

	if(GetEstadoPasado(TECLA_PULSADA)==PULSADO && ESTADO_TECLAS_ACTUAL [TECLA_PULSADA]==PULSADO)
	{

		if(contadorRTI>TL && cantidadTL<1)
		{
			if(LEDS.LED_TRES==APAGADO)
			{
				prenderLed(LED3);
				LEDS.LED_TRES=PRENDIDO;
			}
			else
			{
				apagarLed(LED3);
				LEDS.LED_TRES=APAGADO;
			}

		contadorRTI=0;
		cantidadTL++;
		}
		else
		{
			if(contadorRTI>TC && cantidadTL>=1)
			{
				if(LEDS.LED_TRES==APAGADO)
				{
					prenderLed(LED3);
					LEDS.LED_TRES=PRENDIDO;
				}
				else
				{
					apagarLed(LED3);
					LEDS.LED_TRES=APAGADO;
				}

			contadorRTI=0;
			}
		}
	}
	else
	{
		cantidadTL=0;
	}
}

int main(void)
{
	//Inicializamos los puertos de LED
	inicializarPuertos();

	//Inicializamos los puertos de TECLAS
	InicializarTeclas();

	//Inicializamos los TIMERS y definimos el intervalo
	InicializarTimers();
	DefinirIntervaloRTI(TIEMPO_TIMER_RTI);

	//ARRANCAMOS UN CICLO INFINITO

	  while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

