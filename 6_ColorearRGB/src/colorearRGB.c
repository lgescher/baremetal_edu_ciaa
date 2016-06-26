/* Copyright 2016, colorearRGB Leandro Escher
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
#include "colorearRGB.h"       /* <= own header */

#include "led.h"
#include "teclas.h"
#include "driverRGB.h"

/*==================[macros and definitions]=================================*/
#define CERO 0


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
	uint8_t INICIOTIMERS;
	uint8_t ESTADOESCANEO;


	//VARIABLES DE TECLAS
	uint8_t PRENDIDO = 1;
	uint8_t APAGADO = 0;
	uint8_t PULSADO = 0;
	uint8_t NO_PULSADO = 1;


	//Instancaimos el struc de TECLAS
	TECLAS_1_2_3_4 TECLAS;

	//Inicializamos los puertos de TECLAS
	INICIOTECLAS = InicializarTeclas();

	//----------------------------------
	//VARIABLES DEL TIMER RTI
	uint32_t DURACION_DEL_CICLO_COLOR=100;//Es una variable que se usa para determina cuantas cuentas del RTI dura un ciclo del color. En este caso la duración de un color es igual a 100 cuentas del RTI
	uint32_t TIEMPO_TIMER_RTI=1;//Tiempo en milisegundo del contador RTI
	uint32_t Cuenata_color=0;//Es una variable que cuenta la cantidad de ciclos que se va a mostrar un color determinado
	uint32_t TIEMPO_DEL_COLOR=5;//Es una variable que determina el tiempo total que va a durar un color. Se determina con la cantidad de ciclos que se va a mostrar de un color

	//Inicializamos los TIMERS y definimos el intervalo
	INICIOTIMERS = InicializarTimers();

	DefinirIntervaloRTI(TIEMPO_TIMER_RTI);


	//----------------------------------
	//VARIABLES DE LEDS
	//Inicializamos los puertos de LED
	INICIOLEDS = inicializarPuertos();

	//Instancaimos el struc de LED
	LED_1_2_3_RGB LEDS;

	//VARIABLES DEL RGB
	//Instancaimos el struc de COLORES DE RGB
	COLORES_LEDRGB COLORES_RGB;
	GenerarColoresRGB();

	//DEFINIMOS LOS INTERVALOS DE TIEMPO INICIALES QUE LO VAMOS A DEJAR PRENDIDO A CADA COLOR DEL RGB

	COLORES_RGB.color_ledR=DURACION_DEL_CICLO_COLOR;
	COLORES_RGB.color_ledG=DURACION_DEL_CICLO_COLOR;
	COLORES_RGB.color_ledB=DURACION_DEL_CICLO_COLOR;

	//----------------------------------

	do
	{//GENERAMOS EL ARCOIRIS
		if(!EstadoTecla(TEC1))
		{

			do
			{
				//Seleccionamos lo que vamos a cambiar de estado. En este caso los tres R-G-B
				LEDS.ledR = PRENDIDO;
				LEDS.ledG = PRENDIDO;
				LEDS.ledB = PRENDIDO;
				LEDS.LED_UNO = APAGADO;
				LEDS.LED_DOS = APAGADO;
				LEDS.LED_TRES = APAGADO;

				//CAMBIAMOS EL ESTAD
				cambiarEstado(&LEDS);

				//INICIALIZAMOS a CERO EL CONTADOR DEL TIMER
				SetContadorRGB(CERO);

				//ARRANCAMOS UN CICLO DE COLOR EL CUAL DURA UNA CANTIDAD IGUAL A DURACION_DEL_CICLO_COLOR. EN ESTE CASO SE DEFINIO EN 100 mseg

				//Obtenemos el valor del contador
				uint32_t tiempoPrendido = GetContadorRGB();

				do
				{
					tiempoPrendido = GetContadorRGB();

					if(COLORES_RGB.color_ledR <= tiempoPrendido)
					{
						apagarLed(LEDR);
					}
					if(COLORES_RGB.color_ledG <= tiempoPrendido)
					{
						apagarLed(LEDG);
					}
					if(COLORES_RGB.color_ledB <= tiempoPrendido)
					{
						apagarLed(LEDB);
					}
				}
				while(tiempoPrendido<=DURACION_DEL_CICLO_COLOR);

				//LUEGO DE CUMPLIDO UN CICLO DE VISUALIZACIÓN DE UN COLOR

				//Aumentamos el contador de ciclos
				Cuenata_color++;

			}while(TIEMPO_DEL_COLOR>=Cuenata_color);

			//INICIALIZAMOS A CERO EL CONTADOR DE COLOR
			Cuenata_color=CERO;
			//CAMBIAMOS EL COLOR, MEDIANTE EL CAMBIO DE LA DURACIÓN DE LOS RGB
			CambiarColorRGB(&COLORES_RGB,DURACION_DEL_CICLO_COLOR);
		}
		else
		{
			//Seleccionamos el que vamos a cambiar de estado. PRIMERO EL LED1
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = PRENDIDO;
			LEDS.LED_DOS = APAGADO;
			LEDS.LED_TRES = APAGADO;

			//CAMBIAMOS EL LED1
			cambiarEstado(&LEDS );

			//Esperamos un intervalo


			SetContadorRGB(CERO);

			uint32_t INTERVALO=250;//Definimos un intervalo de 250 milisegundos entre el ensendido de cada color

			uint32_t tiempoDeEspera = CERO;

			do
			{
				tiempoDeEspera= GetContadorRGB();
			}
			while(tiempoDeEspera<INTERVALO);
			//Apagamos el LED1
			apagarLed(LED1);

			//Seleccionamos el SIGUEINTE, EL LED2
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = APAGADO;
			LEDS.LED_DOS = PRENDIDO;
			LEDS.LED_TRES = APAGADO;

			//CAMBIAMOS EL LED2
			cambiarEstado(&LEDS );

			//Esperamos otro intervalo de 250 ms
			SetContadorRGB(CERO);

			do
			{
				tiempoDeEspera= GetContadorRGB();
			}
			while(tiempoDeEspera<INTERVALO);
			//Apagamos el LED2
			apagarLed(LED2);
		}

	}while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

