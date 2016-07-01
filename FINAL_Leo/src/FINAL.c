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
#include "FINAL.h"       /* <= own header */

#include "teclas.h"
#include "led.h"
#include "UART.h"
#include "timer.h"
#include "ADC.h"


#define TIEMPO_TIMER_RTI 100//Tiempo en milisegundo del contador RTI
#define CERO 0
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
//----------------------------------
//LEDS
	//Intancaimos e inicializamos el struc
	LED_1_2_3_RGB LEDS;
	uint8_t INICIOLEDS;

//TECLADO
	//Intancaimos e inicializamos el struc de TECLAS
	TECLAS_1_2_3_4 TECLAS;
	uint8_t INICIOTECLAS;
	uint8_t ESTADOESCANEO;
const uint8_t PRENDIDO = 1;
const uint8_t APAGADO = 0;
const uint8_t PULSADO = 0;
const uint8_t NO_PULSADO = 1;
const uint8_t CAMBIO_DE_ESTADO = 0;


//DAC
uint32_t valor=0;
uint32_t VMIN=0;//Escalon que representa la Minima tensión alcanzada
uint32_t VMAX=1023;//Escalon que representa la Maxima tensión alcanzada. El conversor tiene 10bit de conversión
uint32_t IncrementoDeV=0;//Valor del escalon
uint32_t F=10;//Factor
uint32_t F_A_MAX=100;//Factor AUMENTO maximo
uint32_t F_A_MIN=1;//Factor AUMENTO minimo



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
	uint16_t dato = LeerDatoADC(); //Adquiere el dato de la entrada analógica y cambia el estado del led 1

	uint32_t datoEcualizado= EcualizarSenial(dato);//Modifica el valor del dato segun la configuración del usuario

	enviarNumero_AlPuerto(datoEcualizado);

	EnviarValor_Al_DAC(datoEcualizado);//envia el dato modificado a la salida analógica

	//ResponderAlCaracter(dato);

	//Borramos el flag de interrupción del timer RIT
	BorrarFlagTimerRIT();
}


uint32_t EcualizarSenial(uint16_t valor)
{
	if(EstadoTecla_Antirebote_Liberacion(TEC1,1,0) != FALSE )
	{
		while(enviarPalabra_AlPuerto("Aumento la ganancia")){};
		LimpiarPalabra(palabras);
		if(F>=F_A_MAX)
		{
			F=F_A_MAX;
		}
		else
		{
			F++;
		}
	}

	if(EstadoTecla(TEC2) == FALSE )
	{
		while(enviarPalabra_AlPuerto("Disminuyo la ganancia")){};
		LimpiarPalabra(palabras);

		if(F<=F_A_MIN)
		{
			F=F_A_MIN;
		}
		else
		{
			F--;
		}

		}


	if(EstadoTecla(TEC3) == FALSE )
	{
		while(enviarPalabra_AlPuerto("MUTE")){};
		LimpiarPalabra(palabras);
		F=0;
	}

	if(EstadoTecla(TEC4) == FALSE )
	{
			LEDS.ledR = APAGADO;
			LEDS.ledG = APAGADO;
			LEDS.ledB = APAGADO;
			LEDS.LED_UNO = APAGADO;
			LEDS.LED_DOS = PRENDIDO;
			LEDS.LED_TRES = APAGADO;
			cambiarEstado(&LEDS);
			enviarPalabra_AlPuerto("LED AMARILLO");

	}

	uint32_t aux=(valor*F)/10;

	if(aux>=VMAX)
	{
		return VMAX;
	}
	else
	{
		return aux;
	}

}

//Funciones asociadas al ADC
//-------------------------------------------
uint16_t LeerDatoADC(void)
{
	// EN CADA LECTURA CAMBIAMOS EL ESTADO DEL LED 1
	//Definimos al led uno para que cambie de estado
	LEDS.ledR = APAGADO;
	LEDS.ledG = APAGADO;
	LEDS.ledB = APAGADO;
	LEDS.LED_UNO = PRENDIDO;
	LEDS.LED_DOS = APAGADO;
	LEDS.LED_TRES = APAGADO;
	cambiarEstado(&LEDS);

	//enviamos el dato leido
	uint16_t D = Leer_Dato_ADC();
	return D;
}
//----------------------------------------

//Funciones asociadas a la UART
//----------------------------------------
void enviarDato_AlPuerto(uint8_t dato)
{
	EnviarByte_UART(dato);
}

uint8_t enviarPalabra_AlPuerto(uint8_t palabras[])
{
	int i;
	for(i=0;i<strlen(palabras);i++)
	{
		enviarDato_AlPuerto(palabras[i]);
	}
	return TRUE;

}

uint16_t enviarNumero_AlPuerto(uint16_t num)
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

	Determinar_Digitos(num, &digitosAD);

	int i=0;
	for(i=0;i<strlen(digitosAD);i++)
	{
		enviarDato_AlPuerto(digitosAD[i]);
	}

	LimpiarPalabra(&digitosAD);

	return FIN_DEL_ENVIO;

}


void Determinar_Digitos(uint16_t num, uint8_t * Digitos)
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

void LimpiarPalabra(uint8_t * palabra)
{
	memset( palabra, '\0', strlen(palabra) );
}
//----------------------------------------


//Funciones asociadas al DAC
//-------------------------------------------

uint8_t EnviarValor_Al_DAC(uint32_t aux)
{
	uint8_t valor = EnviarValorBuffer_DAC(aux);
	return valor;
}


//---------------------------------------------------------------------


int main(void)
{
	//Inicializamos los puertos de LED
	INICIOLEDS = inicializarPuertos();

	//Inicializamos los puertos de TECLAS
	INICIOTECLAS = InicializarTeclas();

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

	//Inicializamos la UART
	Inicializar_UART();

	//Inicializamos el ADC
	InicializarADC();

	//Inicializamos el DAC
	InicializarDAC();


	//ARRANCAMOS UN CICLO INFINITO

	  while(1);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

