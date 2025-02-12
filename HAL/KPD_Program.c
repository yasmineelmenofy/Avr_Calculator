/* **************************************************************************************************************************************************
 * FILE NAME:     KPD_Program.c
 * MODULE:        Keypad driver 
 * SWC LAYER:     HAL
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * AUTHOR:        Yasmine Elmenofy 
 * CREATION DATE: 27/1/2025 
 ************************************************************************************************************************************************* */
 
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 #include "KPD_Private.h"
 #include "KPD_Interface.h"
 #include "KPD_Config.h"
 #include "GPIO_Interface.h"
 #include <util/delay.h>
 
 /***************************************************************************************************************************************************
 * Brief:  Intialize The Keypad rows and columns 
 *
 * Params: No parameters 
 * 
 * Return: void 
 *   
 ***************************************************************************************************************************************************/

void KPD_Init(void){
	//Initialize rows as input with internal pull-ups 
	DIO_enSetPinDirection(KPD_ROW_PORT, KPD_ROW0 , DIO_PIN_INPUT );
	DIO_enSetPinDirection(KPD_ROW_PORT, KPD_ROW1 , DIO_PIN_INPUT );
	DIO_enSetPinDirection(KPD_ROW_PORT, KPD_ROW2 , DIO_PIN_INPUT );
	DIO_enSetPinDirection(KPD_ROW_PORT, KPD_ROW3 , DIO_PIN_INPUT );

	// Enable internal pull-up resistors for rows (set them high) 
	DIO_enSetPinValue(KPD_ROW_PORT, KPD_ROW0 , DIO_PIN_HIGH  );
	DIO_enSetPinValue(KPD_ROW_PORT, KPD_ROW1 , DIO_PIN_HIGH );
	DIO_enSetPinValue(KPD_ROW_PORT, KPD_ROW2 , DIO_PIN_HIGH );
	DIO_enSetPinValue(KPD_ROW_PORT, KPD_ROW3 , DIO_PIN_HIGH );
	

	// Initialize columns as output and set them to high 
	DIO_enSetPinDirection(KPD_COL_PORT, KPD_COL0 , DIO_PIN_OUTPUT );
	DIO_enSetPinDirection(KPD_COL_PORT, KPD_COL1 , DIO_PIN_OUTPUT );
	DIO_enSetPinDirection(KPD_COL_PORT, KPD_COL2 , DIO_PIN_OUTPUT );
	DIO_enSetPinDirection(KPD_COL_PORT, KPD_COL3 , DIO_PIN_OUTPUT );
	DIO_enSetPinDirection(KPD_COL_PORT, KPD_COL4 , DIO_PIN_OUTPUT );
	DIO_enSetPinDirection(KPD_COL_PORT, KPD_COL5 , DIO_PIN_OUTPUT );
	
	
	DIO_enSetPinValue(KPD_COL_PORT, KPD_COL0 , DIO_PIN_HIGH  );
	DIO_enSetPinValue(KPD_COL_PORT, KPD_COL1 , DIO_PIN_HIGH );
	DIO_enSetPinValue(KPD_COL_PORT, KPD_COL2 , DIO_PIN_HIGH );
	DIO_enSetPinValue(KPD_COL_PORT, KPD_COL3 , DIO_PIN_HIGH );
	DIO_enSetPinValue(KPD_COL_PORT, KPD_COL4 , DIO_PIN_HIGH );
	DIO_enSetPinValue(KPD_COL_PORT, KPD_COL5 , DIO_PIN_HIGH );
	
}

/***************************************************************************************************************************************************
 * Brief:  That function detect which key is pressed by the user (handle bouncing and long press errors )
 *
 * Params: No parameters 
 * 
 * Return: Loc_u8ReturnKey : return the key that is pressed by the user 
 *   
 ***************************************************************************************************************************************************/
u8 KPD_u8GetKey(void) {
    u8 Loc_u8ReturnKey = KPD_NOT_PRESSED;
    u8 Get_u8PressedKey;
    u8 Loc_Row, Loc_Col;
    for (Loc_Col = 0 + KPD_COL_START; Loc_Col <= KPD_COL_END; Loc_Col++) {
        DIO_enSetPinValue(KPD_COL_PORT, Loc_Col, DIO_PIN_LOW);
        for (Loc_Row = 0 + KPD_ROW_START; Loc_Row <= KPD_ROW_END; Loc_Row++) {
            DIO_enGetPinValue(KPD_ROW_PORT, Loc_Row, &Get_u8PressedKey);
            if (Get_u8PressedKey == DIO_PIN_LOW) {
                DIO_enGetPinValue(KPD_ROW_PORT, Loc_Row, &Get_u8PressedKey);          // handle bouncing errors
                if (Get_u8PressedKey == DIO_PIN_LOW) {
                    Loc_u8ReturnKey = kpd_u8buttons[Loc_Row - KPD_ROW_START][Loc_Col - KPD_COL_START];
                }
                DIO_enGetPinValue(KPD_ROW_PORT, Loc_Row, &Get_u8PressedKey);
                while (Get_u8PressedKey == DIO_PIN_LOW) {                             // handle Long press
                    DIO_enGetPinValue(KPD_ROW_PORT, Loc_Row, &Get_u8PressedKey);
                }
				break;
            }
        }

        DIO_enSetPinValue(KPD_COL_PORT, Loc_Col, DIO_PIN_HIGH);
    }
    return Loc_u8ReturnKey;
}








