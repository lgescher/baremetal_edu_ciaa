/* Copyright 2016, LeoDriverTECLASLPCOpen
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

#include "teclas.h"
#include "chip.h"



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

uint16_t INTERVALO = 5000;

/*==================[internal functions declaration]=========================*/
void delay(uint32_t cuentas){
	uint32_t i;
	for (i=cuentas;i!=0;i--){
		asm("nop");
	};
};

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

uint8_t InicializarTeclas(void)
{
	/*Le pasamos el parametro la direccion base del periferico GPIO ya definida en LPC_GPIO_Init*/
	Chip_GPIO_Init (LPC_GPIO_PORT);
	/*Indicamos las caracteristicas electricas de cada pin empleado y remapearlos como puertos GPIO y le definimos la función.*/


	/* mapea P1 0 en GPIO 0[4], SW1 */
	Chip_SCU_PinMux(_PAQUETE_PIN_TEC_,_PIN_PAQ_TEC1_,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	/* mapea P1 1 en GPIO 0[8], SW2 */
	Chip_SCU_PinMux(_PAQUETE_PIN_TEC_,_PIN_PAQ_TEC2_,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	/* mapea P1 2 en GPIO 0[9], SW3 */
	Chip_SCU_PinMux(_PAQUETE_PIN_TEC_,_PIN_PAQ_TEC3_,MD_PUP|MD_EZI|MD_ZI,FUNC0);
	/* mapea P1 6 en GPIO 1[9], SW4 */
	Chip_SCU_PinMux(_PAQUETE_PIN_TEC_,_PIN_PAQ_TEC4_,MD_PUP|MD_EZI|MD_ZI,FUNC0);


	//pregunta: QUE DIFERENCIA HAY ENTRE EL PIN DEL PAQUETE Y EL PIN DEL PUERTO


/*void Chip_GPIO_SetDir 	(LPC_GPIO_T * pGPIO, uint8_t portNum, uint32_t bitValue, uint8_t  out)
 * pGPIO	: The base of GPIO peripheral on the chip
 * portNum	: Port Number
 * bitValue	: GPIO bit to set
 * out	: Direction value, 0 = input, !0 = output */

	uint8_t ENTRADA=0;

	Chip_GPIO_SetDir(LPC_GPIO_PORT, _PUERTO_TEC1_,1<<_TEC1_,ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, _PUERTO_TEC2_,1<<_TEC2_,ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, _PUERTO_TEC3_,1<<_TEC3_,ENTRADA);
	Chip_GPIO_SetDir(LPC_GPIO_PORT, _PUERTO_TEC4_,1<<_TEC4_,ENTRADA);

	return TRUE;
}

uint8_t EstadoTecla(uint8_t numTec )
{

	/*sE RECOMIENDA Chip_GPIO_GetPinState() ANTES QUE Chip_GPIO_ReadPortBit()
	 * return	true if the GPIO is high, false if low
	*/

	//DEFINIMOS UNA VARIABLE AUX PARA DEVOLVER EL ESADO LEIDO
	uint8_t ESTADO = FALSE;

		switch(numTec)
	{
	case TEC1:
		ESTADO = Chip_GPIO_GetPinState(LPC_GPIO_PORT,_PUERTO_TEC1_,_TEC1_);
		break;
	case TEC2:
		ESTADO = Chip_GPIO_GetPinState(LPC_GPIO_PORT,_PUERTO_TEC2_,_TEC2_);
		break;
	case TEC3:
		ESTADO = Chip_GPIO_GetPinState(LPC_GPIO_PORT,_PUERTO_TEC3_,_TEC3_);
		break;
	case TEC4:
		ESTADO = Chip_GPIO_GetPinState(LPC_GPIO_PORT,_PUERTO_TEC4_,_TEC4_);
		break;
	default:
		return FALSE;
		break;
	}
	return ESTADO;
}

uint8_t EscanearTeclado(TECLAS_1_2_3_4 * TECLAS)
{
	TECLAS->tec1 = EstadoTecla(_TEC1_);
	TECLAS->tec2 = EstadoTecla(_TEC2_);
	TECLAS->tec3 = EstadoTecla(_TEC3_);
	TECLAS->tec4 = EstadoTecla(_TEC4_);
	return TRUE;

}


uint8_t EstadoTecla_Antirebote_Liberacion(uint8_t numTec, uint8_t Antirrebote, uint8_t Liberacion)
{//RETORNA TRUE SI LA TECLA ESTA APRETA O SI HAY UN CAMBIO EN LA LIBERACIÓN

	uint8_t PIN=0;
	uint8_t PUERTO=0;

		switch(numTec)
	{
	case TEC1:
		PIN=_TEC1_;
		PUERTO=_PUERTO_TEC1_;
		break;
	case TEC2:
		PIN=_TEC2_;
		PUERTO=_PUERTO_TEC2_;
		break;
	case TEC3:
		PIN=_TEC3_;
		PUERTO=_PUERTO_TEC3_;
		break;
	case TEC4:
		PIN=_TEC4_;
		PUERTO=_PUERTO_TEC4_;
		break;
	default:
		return FALSE;
		break;
	}

	if (Chip_GPIO_GetPinState(LPC_GPIO_PORT,PUERTO,PIN) == FALSE )//SI ESTA BAJO, ENTRA
		{
		if (Antirrebote == TRUE)//SI EL ANTIRREBOTE ESTA ACTIVADO, ESPERA UN DELAY ANTES DE ENVIAR EL ESTADO
		{
			delay(INTERVALO);
			if (Chip_GPIO_GetPinState(LPC_GPIO_PORT,PUERTO,PIN) == FALSE)
			{
				if (Liberacion == TRUE)//SI LA LIBERACIÓN ESTA ACTIVADA, ESPERA A QUE SE LIBERE LA TECLA
				{
					while (Chip_GPIO_GetPinState(LPC_GPIO_PORT,PUERTO,PIN) == FALSE)//Esperamos hasta que la tecla esté liberada
					{
						asm("nop");
					}
					return TRUE;
				}
				else //SIN ESPERAR QUE LIBERE
				{
					return TRUE;
				}
			}
			else //SI LUEGO DE ESPERAR NO ESTA ACTIVADA Y FALLA EL CONTROL DEL REBOTE
				{
				return FALSE;
				}
		}
		else //SIN ANTIREBOTE
		{
			if (Liberacion == TRUE) //SI LA LIBERACIÓN ESTA ACTIVADA, ESPERA A QUE SE LIBERE LA TECLA
				{
				while (Chip_GPIO_GetPinState(LPC_GPIO_PORT,PUERTO,PIN) == FALSE)//Esperamos hasta que la tecla esté liberada
					{
					asm("nop");
					}
				return TRUE;
				}
			else //SIN ESPERAR QUE LIBERE
				{
				return TRUE;
				}
			}
		}
	else //NO HAY TECLA APRETADA, NI CAMBIO EN LA LIBERACION
	{
		return FALSE;
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

