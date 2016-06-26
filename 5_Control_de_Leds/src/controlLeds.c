/* Copyright 2016, controlLEDS Leandro Escher
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
#include "controlLeds.h"       /* <= own header */

#include "led.h"
#include "teclas.h"

/*==================[macros and definitions]=================================*/
#define DERECHA 1
#define IZQUIERDA -1
#define INICIO_POSICION 1 //indica la menor posición posible de leds
#define FIN_POSICION 4 //indica la mayor posición posible de leds

/*==================[internal data declaration]==============================*/

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



int main(void)
{
   /* perform the needed initialization here */

	uint8_t INICIOLEDS;
	uint8_t INICIOTECLAS;

	uint8_t PRENDIDO = 1;
	uint8_t APAGADO = 0;
	uint8_t PULSADO = 0;
	uint8_t NO_PULSADO = 1;

	uint8_t POSICION_LEDS = 2;

	uint8_t CAMBIO_DE_ESTADO = 0;
	uint32_t i;

	uint32_t INTERVALO = 500000;
	uint32_t CONTADOR = 0;//ES LA VARIABLE INTERMEDIA QUE USAMOS PARA CONTAR LOS CICLOS QUE SE ESPERAN
	uint32_t INTERVALO_PULSADO =20;//ES EL TIEMPO QUE SE DEBE MANTENER PRESIONADO UN PULSADOR PARA QUE CAMBIE DE COLOR



	//Intancaimos e inicializamos el struc de LED
	LED_1_2_3_RGB LEDS;

	//Intancaimos e inicializamos el struc de TECLAS
	TECLAS_1_2_3_4 TECLAS;

	//Inicializamos los puertos de LED
	INICIOLEDS = inicializarPuertos();

	//Inicializamos los puertos de TECLAS
	INICIOTECLAS = InicializarTeclas();

	LEDS.ledR = APAGADO;
	LEDS.ledG = APAGADO;
	LEDS.ledB = APAGADO;
	LEDS.LED_UNO = APAGADO;
	LEDS.LED_DOS = PRENDIDO;
	LEDS.LED_TRES = APAGADO;

	//ARRANCAMOS UN CICLO INFINITO
	do
	{
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );
		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
		{
			asm("nop");
		};

		if(EstadoTecla(TEC1)==PULSADO)
		{
			do
			{
				CONTADOR++;
				if(CONTADOR==INTERVALO_PULSADO)
				{
					POSICION_LEDS = POSICION_LEDS + IZQUIERDA;

					if(POSICION_LEDS > FIN_POSICION)
					{
						POSICION_LEDS = INICIO_POSICION;
					}
					if(POSICION_LEDS < INICIO_POSICION)
					{
						POSICION_LEDS = FIN_POSICION;
					}

					cambiarLedHacia(&LEDS, POSICION_LEDS);
					CONTADOR=0;
				}
				apagarLed(LED1);
				apagarLed(LED2);
				apagarLed(LED3);
				apagarLed(LEDR);
				apagarLed(LEDG);
				apagarLed(LEDB);
				CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );
				//Esperamos un intervalo
				for(i=INTERVALO ;i!=0;i--)
				{
					asm("nop");
				};
			}
			while(!EstadoTecla(TEC1));
			CONTADOR=0;
		}

		if(EstadoTecla(TEC4)==PULSADO)
		{
			do
			{
				CONTADOR++;
				if(CONTADOR==INTERVALO_PULSADO)
				{

					POSICION_LEDS = POSICION_LEDS + DERECHA;

					if(POSICION_LEDS > FIN_POSICION)
					{
						POSICION_LEDS = INICIO_POSICION;
					}
					if(POSICION_LEDS < INICIO_POSICION)
					{
						POSICION_LEDS = FIN_POSICION;
					}

					cambiarLedHacia(&LEDS, POSICION_LEDS);
					CONTADOR=0;
				}
				apagarLed(LED1);
				apagarLed(LED2);
				apagarLed(LED3);
				apagarLed(LEDR);
				apagarLed(LEDG);
				apagarLed(LEDB);
				CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );
				//Esperamos un intervalo
				for(i=INTERVALO ;i!=0;i--)
				{
					asm("nop");
				};
			}
			while(!EstadoTecla(TEC4));
			CONTADOR=0;
		}
	}
	while(1);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

