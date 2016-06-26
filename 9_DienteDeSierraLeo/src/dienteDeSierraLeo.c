/* Copyright 2016, Generador de Señal para un diente de sierra fijo Leandro Escher
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
#include "dienteDeSierraLeo.h"       /* <= own header */

#include "teclas.h"
#include "DAC.h"
#include "timer.h"

#define CANTIDAD_TECLAS 4

#define PRENDIDO  1
#define APAGADO  0
#define PULSADO  0
#define NO_PULSADO  1
#define CAMBIO_DE_ESTADO  0
#define SIN_CAMBIOS  0


#define CERO 0

#define TIEMPO_TIMER_RTI 1//Tiempo en milisegundo del contador RTI
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//----------------------------------

//----------------------------------
	//TECLAS

	//Instanciamos e inicializamos el struc de TECLAS
	TECLAS_1_2_3_4 TECLAS;

	//VARIABLES DEL TIMER RTI
	uint32_t contadorRTI=0;

	//DAC

	uint32_t valor=0;
	uint32_t VMIN=0;//Escalon que representa la Minima tensión alcanzada
	uint32_t VMAX=1023;//Escalon que representa la Maxima tensión alcanzada. El conversor tiene 10bit de conversión
	uint32_t IncrementoDeV=0;//Valor del escalon
	uint32_t T=0;//Periodo

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
	generarSalida();//modifica el valor de tensión a mostrar
	EnviarValor(valor);//envia el valor generado

	//Borramos el flag de interrupción del timer RIT
	BorrarFlagTimerRIT();
}


uint8_t generarSalida(void)
{
	if(valor>=VMAX)
	{
		valor=VMIN;
	}
	else
	{
		valor=valor+IncrementoDeV;

	}
}


uint8_t EnviarValor(uint32_t aux)
{
	return EnviarValorBuffer_DAC(aux);
}

void SetVMIN(uint32_t aux)
{
	VMIN=aux;
}
void SetVMAX(uint32_t aux)
{
	VMAX=aux;
}
void SetT(uint32_t aux)//Función para setear el periodo
{
	T=aux;
}
void DeterminarIncrementoDeV(void)//Función que calcula el incremeto maximo en función del periodo seleccionado y los valores de Vmax y Vmin
{
	IncrementoDeV =(VMAX-VMIN)/T;
}


int main(void)
{
	//Inicializamos los puertos de TECLAS
	InicializarTeclas();

	//Inicializamos los TIMERS y definimos el intervalo
	InicializarTimers();
	DefinirIntervaloRTI(TIEMPO_TIMER_RTI);

	//Inicializamos el DAC
	InicializarDAC();

	//INICIALIZAR LA SEÑAL A GENERAR
	SetVMIN(0);//set la minima tensión de la señal 0 V
	SetVMAX(1023);//set la maxima tensión de la señal al maximo (3,3 Volt repartidos en 1024 estados)
	SetT(100);//setiamos el periodo a 100 milisegundos
	DeterminarIncrementoDeV();//detemina el valor del escalon, buscando siempre la mejor resolución posible

	//ARRANCAMOS UN CICLO INFINITO

	  while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

