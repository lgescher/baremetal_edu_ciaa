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
#include "driverRGB.h"       /* <= own header */

#include "chip.h"
#include "timer.h"
#include "led.h"
#include "stdlib.h"

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

//Variable destinada a llevar la cuenta del contadorRTI
volatile uint32_t cuentaRGB=0;


uint8_t CANTIDAD_DE_COLORES=17;
uint8_t PASO=17;

uint32_t paletaDeColor[17];


void InterrupcionRIT(void)
{
	//Llamamos a la función que cuenta
	ContadorRGB();

	//Borramos el flag de interrupción del timer RIT
	BorrarFlagTimerRIT();

}

void ContadorRGB(void)
{
	cuentaRGB++;
}

void SetContadorRGB(uint32_t cuenta)
{
	cuentaRGB=cuenta;
}

uint32_t GetContadorRGB(void)
{
	return cuentaRGB;
}

void GenerarColoresRGB(void)
{
		int i=0;

		for(i=0;i<CANTIDAD_DE_COLORES;i++)
			{
				paletaDeColor[i]=PASO*i;
			}
}
void CambiarColorRGB(COLORES_LEDRGB* COLORES_RGB,uint32_t DURAC_DEL_CICLO_COLOR)
{

	int posicionEnPaleta1 = rand() %CANTIDAD_DE_COLORES;
	int posicionEnPaleta2 = rand() %CANTIDAD_DE_COLORES;
	int posicionEnPaleta3 = rand() %CANTIDAD_DE_COLORES;


	COLORES_RGB->color_ledR=paletaDeColor[posicionEnPaleta1];
	COLORES_RGB->color_ledG=paletaDeColor[posicionEnPaleta2];
	COLORES_RGB->color_ledB=paletaDeColor[posicionEnPaleta3];

}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

