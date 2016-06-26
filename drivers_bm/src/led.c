/* Copyright 2016, XXXXXXXXX  
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

/** \brief Blinking Bare Metal driver led
 **
 **
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal LED Driver
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

#ifndef CPU
#error CPU shall be defined
#endif
#if (lpc4337 == CPU)
#elif (mk60fx512vlq15 == CPU)
#else
#endif

#include "led.h"
#include "chip.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

int inicializarPuertos(void)
{
	/*Le pasamos el parametro la direccion base del periferico GPIO ya definida en LPC_GPIO_Init*/
	Chip_GPIO_Init (LPC_GPIO_PORT);
	/*Indicamos las caracteristicas electricas de cada pin empleado y remapearlos como puertos GPIO y le definimos la función.*/


	/*remapea P2_0 en GPIO5[0], LED0R y habilita el pull up*/
	Chip_SCU_PinMux(paquetePinLed,LEDR,MD_PUP,FUNC4);
	/*remapea P2_1 en GPIO5[1], LED0B y habilita el pull up*/
	Chip_SCU_PinMux(paquetePinLed,LEDB,MD_PUP,FUNC4);
	/*remapea P2_2 en GPIO5[2], LED0G y habilita el pull up*/
	Chip_SCU_PinMux(paquetePinLed,LEDG,MD_PUP,FUNC4);
	/*remapea P2_10 en GPIO0[14], LED1 y habilita el pull up*/
	Chip_SCU_PinMux(paquetePinLed,LED1,MD_PUP,FUNC0);
	/*remapea P2_11 en GPIO1[11], LED2 y habilita el pull up*/
	Chip_SCU_PinMux(paquetePinLed,LED2,MD_PUP,FUNC0);
	/*remapea P2_12 en GPIO2[12], LED3 y habilita el pull up*/
	Chip_SCU_PinMux(paquetePinLed,LED3,MD_PUP,FUNC0);

/*void Chip_GPIO_SetDir 	(LPC_GPIO_T * pGPIO, uint8_t portNum, uint32_t bitValue, uint8_t  out)
 * pGPIO	: The base of GPIO peripheral on the chip
 * portNum	: Port Number
 * bitValue	: GPIO bit to set
 * out	: Direction value, 0 = input, !0 = output */

	uint8_t salida=1;

	Chip_GPIO_SetDir(LPC_GPIO_PORT, puertoLedRojo,1<<LEDR,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, puertoLedVerde,1<<LEDB,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, puertoLedAzul,1<<LEDG,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, puertoLed_1,1<<LED1,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, puertoLed_2,1<<LED2,salida);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, puertoLed_3,1<<LED3,salida);

	return TRUE;
}

int prenderLed(uint8_t numLed)
{
	switch(numLed)
	{
	case LEDR:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT,puertoLedRojo,LEDR);
		break;
	case LEDG:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, puertoLedVerde,LEDG);
		break;
	case LEDB:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, puertoLedAzul,LEDB);
		break;
	case LED1:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, puertoLed_1,LED1);
		break;
	case LED2:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, puertoLed_2,LED2);
		break;
	case LED3:
		Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, puertoLed_3,LED3);
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

int apagarLed(uint8_t numLed)
{
	switch(numLed)
	{
	case LEDR:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, puertoLedRojo,LEDR);
		break;
	case LEDG:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, puertoLedVerde,LEDG);
		break;
	case LEDB:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, puertoLedAzul,LEDB);
		break;
	case LED1:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, puertoLed_1,LED1);
		break;
	case LED2:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, puertoLed_2,LED2);
		break;
	case LED3:
		Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, puertoLed_3,LED3);
		break;
	default:
		return FALSE;
		break;
	}

	return TRUE;
}

int cambiarEstado(LED_1_2_3_RGB *LedRGB)
{
	//Si se inicializa el struc en un valor distinto de CERO, el mismo cambia de estado.
	if(LedRGB->ledR == TRUE)
		{
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, puertoLedRojo,LEDR);
		}
	if(LedRGB->ledG == TRUE)
		{
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, puertoLedVerde,LEDG);
		}
	if(LedRGB->ledB == TRUE)
		{
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, puertoLedAzul,LEDB);
		}
	if(LedRGB->LED_UNO == TRUE)
		{
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, puertoLed_1,LED1);
		}
	if(LedRGB->LED_DOS == TRUE)
		{
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, puertoLed_2,LED2);
		}
	if(LedRGB->LED_TRES == TRUE)
		{
		Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, puertoLed_3,LED3);
		}
	return TRUE;

}

int cambiarLedHacia(LED_1_2_3_RGB* LEDS, uint8_t POS_ACTUAL)
{

	switch(POS_ACTUAL)
	{
	case POS_LED_1_:
		LEDS->ledR = APAGAR;
		LEDS->ledG = APAGAR;
		LEDS->ledB = APAGAR;
		LEDS->LED_UNO = PRENDER;
		LEDS->LED_DOS = APAGAR;
		LEDS->LED_TRES = APAGAR;
		break;
	case POS_LED_2_:
		LEDS->ledR = APAGAR;
		LEDS->ledG = APAGAR;
		LEDS->ledB = APAGAR;
		LEDS->LED_UNO = APAGAR;
		LEDS->LED_DOS = PRENDER;
		LEDS->LED_TRES = APAGAR;
		break;
	case POS_LED_3_:
		LEDS->ledR = APAGAR;
		LEDS->ledG = APAGAR;
		LEDS->ledB = APAGAR;
		LEDS->LED_UNO = APAGAR;
		LEDS->LED_DOS = APAGAR;
		LEDS->LED_TRES = PRENDER;
		break;
	case POS_LED_RGB_:
		LEDS->ledR = PRENDER;
		LEDS->ledG = PRENDER;
		LEDS->ledB = PRENDER;
		LEDS->LED_UNO = APAGAR;
		LEDS->LED_DOS = APAGAR;
		LEDS->LED_TRES = APAGAR;
		break;
	default:
		return FALSE;
		break;
	}
}

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




/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

