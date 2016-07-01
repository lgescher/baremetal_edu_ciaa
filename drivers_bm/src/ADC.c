/* Copyright 2016, LeoDriverADC
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

#include "timer.h"
#include "chip.h"
#include "ADC.h"

//#include "ritimer 18xx 43xx.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//INICIALIZACIÓN DE LA CONFIGURACIÓN PARA EL ADC
static ADC_CLOCK_SETUP_T ADCSetup;

uint32_t ADC_ID_1 = 1;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/





uint8_t InicializarADC(void)
{

	//INICIALIZACIÓN DE LA CONFIGURACIÓN PARA EL ADC
	ADCSetup.adcRate = 1000;
	ADCSetup.bitsAccuracy = ADC_10BITS;	/*!< ADC bit accuracy */
	ADCSetup.burstMode= DISABLE;

	Chip_SCU_ADC_Channel_Config(ADC_1, ADC_CH1);

	//Inicializa el ADC y la estructura de instalación de ADC al valor por defecto
	Chip_ADC_Init(LPC_ADC1, &ADCSetup);

	Chip_ADC_EnableChannel(LPC_ADC1, ADC_CH1, ENABLE);
}


uint16_t Leer_Dato_ADC(void)
{
	uint16_t dato_Del_ADC;
	//Seleccionamos el modo de iniciar la conversión AD
	Chip_ADC_SetStartMode(LPC_ADC1,  ADC_START_NOW, ADC_TRIGGERMODE_RISING);

	//Esperaramo por que se complete la comversión A/D

	while (Chip_ADC_ReadStatus(LPC_ADC1, ADC_CH1, ADC_DR_DONE_STAT)!=SET){}
	Chip_ADC_ReadValue(LPC_ADC1, ADC_CH1, &dato_Del_ADC);

	return dato_Del_ADC;
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

