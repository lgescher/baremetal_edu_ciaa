/* Copyright 2016, psicodelia Leandro Escher
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

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

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
#include "psicodelia.h"       /* <= own header */

#include "led.h"

/*==================[macros and definitions]=================================*/

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

	uint8_t INICIO;
	uint8_t PRENDIDO = 1;
	uint8_t APAGADO = 0;
	uint8_t CAMBIO_DE_ESTADO = 0;
	uint32_t i;
	uint32_t INTERVALO=500000;

	//Intancaimos e inicializamos el struc
	LED_1_2_3_RGB LEDS;

	//Inicializamos los puertos
	INICIO = inicializarPuertos();

	//ARRANCAMOS UN CICLO INFINITO
	do
	  {
		//Seleccionamos el que vamos a cambiar de estado. PRIMERO EL LED1
		LEDS.ledR = APAGADO;
		LEDS.ledG = APAGADO;
		LEDS.ledB = APAGADO;
		LEDS.LED_UNO = PRENDIDO;
		LEDS.LED_DOS = APAGADO;
		LEDS.LED_TRES = APAGADO;

		//CAMBIAMOS EL LED1
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );

		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
			{
				asm("nop");
			};
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
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );

		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
			{
				asm("nop");
			};
		//Apagamos el LED2
		apagarLed(LED2);
		//Seleccionamos el SIGUEINTE, EL LED3
		LEDS.ledR = APAGADO;
		LEDS.ledG = APAGADO;
		LEDS.ledB = APAGADO;
		LEDS.LED_UNO = APAGADO;
		LEDS.LED_DOS = APAGADO;
		LEDS.LED_TRES = PRENDIDO;

		//CAMBIAMOS EL LED3
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );

		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
			{
				asm("nop");
			};

		//Apagamos el LED3
		apagarLed(LED3);

		//Seleccionamos el SIGUEINTE, EL LEDG
		LEDS.ledR = APAGADO;
		LEDS.ledG = PRENDIDO;
		LEDS.ledB = APAGADO;
		LEDS.LED_UNO = APAGADO;
		LEDS.LED_DOS = APAGADO;
		LEDS.LED_TRES = APAGADO;

		//CAMBIAMOS EL LEDG
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );

		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
			{
				asm("nop");
			};

		//Apagamos el LEDG
		apagarLed(LEDG);

		//Seleccionamos el SIGUEINTE, EL LEDR
		LEDS.ledR = PRENDIDO;
		LEDS.ledG = APAGADO;
		LEDS.ledB = APAGADO;
		LEDS.LED_UNO = APAGADO;
		LEDS.LED_DOS = APAGADO;
		LEDS.LED_TRES = APAGADO;

		//CAMBIAMOS EL LEDR
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );

		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
			{
				asm("nop");
			};

		//Apagamos el LEDR
		apagarLed(LEDR);

		//Seleccionamos el SIGUEINTE, EL LEDB
		LEDS.ledR = APAGADO;
		LEDS.ledG = APAGADO;
		LEDS.ledB = PRENDIDO;
		LEDS.LED_UNO = APAGADO;
		LEDS.LED_DOS = APAGADO;
		LEDS.LED_TRES = APAGADO;

		//CAMBIAMOS EL LEDB
		CAMBIO_DE_ESTADO = cambiarEstado(&LEDS );

		//Esperamos un intervalo
		for(i=INTERVALO ;i!=0;i--)
			{
				asm("nop");
			};
		//Apagamos el LEDG
		apagarLed(LEDB);

	  }
	  while(1);


}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

