/*
 * Main.c
 *
 *  Created on: 29 Jan 2025
 *      Author: yassm
 */

#include "GPIO_Interface.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "CLCD_Interface.h"
#include "KPD_Interface.h"
#include "Calculator.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
void main(void) {


	    // Initialize the keypad
	    KPD_Init();

	    // Initialize the CLCD
	    CLCD_vInit();
	    // Clear the display
	    CLCD_vClearScreen();
	        CLCD_vSendString("Welcome ");
	        _delay_ms(50);
	        CLCD_vClearScreen();

	    while (1) {

	            calculate();

	        }

	}

