/* Copyright 2016, LeoDriverLPCOpen
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

#ifndef LED_H
#define LED_H
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example header file
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
#include "stdint.h"


/*==================[macros]=================================================*/
#define lpc4337            1
#define mk60fx512vlq15     2

#define LEDR 0
#define LEDB 2
#define LEDG 1
#define LED1 14
#define LED2 11
#define LED3 12
#define paquetePinLed 2
#define puertoLed_1 0
#define puertoLed_2 1
#define puertoLed_3 1
#define puertoLedRojo 5
#define puertoLedVerde 5
#define puertoLedAzul 5
#define APAGAR 0
#define PRENDER 1
#define POS_LED_1_ 1
#define POS_LED_2_ 2
#define POS_LED_3_ 3
#define POS_LED_RGB_ 4


/*==================[typedef]================================================*/

typedef struct {
	uint8_t ledR;
	uint8_t ledG;
	uint8_t ledB;
	uint8_t LED_UNO;
	uint8_t LED_DOS;
	uint8_t LED_TRES;}LED_1_2_3_RGB;

/*==================[external data declaration]==============================*/

/* */

int inicializarPuertos(void);
int prenderLed(uint8_t numLed );
int apagarLed(uint8_t numLed);
int cambiarEstado(LED_1_2_3_RGB *LedRGB);
int cambiarLedHacia(LED_1_2_3_RGB* leds, uint8_t POS_ACTUAL);











/*==================[external functions declaration]=========================*/

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef MI_NUEVO_PROYECTO_H */

