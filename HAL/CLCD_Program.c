/* **************************************************************************************************************************************************
 * FILE NAME:     CLCD_Program.c
 * MODULE:        CLCD
 * SWC LAYER:     HAL
 * Board:         ATMEGA32
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * AUTHOR:        Yasmine Elmenofy 
 * CREATION DATE: 25/1/2025 
 ************************************************************************************************************************************************* */
 
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 #include "CLCD_Private.h"
 #include "CLCD_Interface.h"
 #include "CLCD_Config.h"
 #include "GPIO_Interface.h"
 #include <util/delay.h>

/***************************************************************************************************************************************************
 * Brief:  Intialize the clcd for 8 bit mode 
 *
 * Params: No parameters 
 * 
 * Return: void 
 *   
 ***************************************************************************************************************************************************/
void CLCD_vInit(){ 
     _delay_ms(50);
  DIO_enSetPortDirection(CLCD_DATA_PORT ,DIO_PORT_OUTPUT);
  DIO_enSetPinDirection (CLCD_RS_PORT   ,CLCD_RS_PIN    ,DIO_PIN_OUTPUT);
  DIO_enSetPinDirection (CLCD_EN_PORT   ,CLCD_EN_PIN    ,DIO_PIN_OUTPUT);
  DIO_enSetPinDirection (CLCD_RW_PORT   ,CLCD_RW_PIN    ,DIO_PIN_OUTPUT);
  
    CLCD_vSendCommand(CLCD_SET_CURSUR); 
	_delay_ms(1);
	CLCD_vSendCommand(CLCD_8BIT_MODE); 
	_delay_ms(1);
    CLCD_vSendCommand(CLCD_DISPLAY_ONOFF_CONTROL);   
    _delay_ms(1);	
    CLCD_vSendCommand(CLCD_CLEAR   );
	_delay_ms(3);
	CLCD_vSendCommand(CLCD_ENTRYMODE);
	_delay_ms(1);
}

/***************************************************************************************************************************************************
 * Brief:  Send the data entered by the user to the data port to be displayed on the screen 
 *       
 * Params: - Copy_u8Data : The date that will be displayed on the screen 
 * 
 * Return: void 
 *  
 * Note: To Sent the single digit as data you need to  Add ASCII offset
 ***************************************************************************************************************************************************/
void CLCD_vSendData(u8 Copy_u8Data){
	DIO_enSetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	DIO_enSetPinValue(CLCD_RS_PORT   ,CLCD_RS_PIN    ,DIO_PIN_HIGH);
	DIO_enSetPinValue(CLCD_RW_PORT   ,CLCD_RW_PIN    ,DIO_PIN_LOW);
	DIO_enSetPinValue(CLCD_EN_PORT   ,CLCD_EN_PIN    ,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_enSetPinValue  (CLCD_EN_PORT   ,CLCD_EN_PIN  ,DIO_PIN_LOW );
	_delay_ms(1);
	
}

/***************************************************************************************************************************************************
 * Brief:  Send the command to be excuted to the data port 
 *       
 * Params: - Copy_u8Command : The Command that will be excuted  
 * 
 * Return: void 
 *   
 ***************************************************************************************************************************************************/
void CLCD_vSendCommand(u8 Copy_u8Command){
	DIO_enSetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	DIO_enSetPinValue(CLCD_RS_PORT   ,CLCD_RS_PIN    ,DIO_PIN_LOW);
	DIO_enSetPinValue(CLCD_RW_PORT   ,CLCD_RW_PIN    ,DIO_PIN_LOW);
	DIO_enSetPinValue(CLCD_EN_PORT   ,CLCD_EN_PIN    ,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_enSetPinValue  (CLCD_EN_PORT   ,CLCD_EN_PIN  ,DIO_PIN_LOW );
	_delay_ms(1);
}

void CLCD_vClearScreen(void) {
    CLCD_vSendCommand(CLCD_CLEAR);
    _delay_ms(2); 
}

/***************************************************************************************************************************************************
 * Brief:  Set the cursur postion according to the number of the row and coloumn 
 *       
 * Params: - Copy_u8Row : The number of row (1 or 2 ) 
 *         - Copy_u8Col: The number of coloumn from one to 16 
 * 
 * Return: void 
 *   
 ***************************************************************************************************************************************************/
void CLCD_vSetCursurPostion(u8 Copy_u8Row , u8 Copy_u8Col){
	u8 u8_Adress;
	if ((Copy_u8Row > 1)  || (Copy_u8Col > 15) )
	{
		u8_Adress = CLCD_SET_CURSUR ;
	}else if ((Copy_u8Row == CLCD_ROW_1))
	{
		u8_Adress = CLCD_SET_CURSUR + Copy_u8Col ;
	}else if ((Copy_u8Row == CLCD_ROW_2))
	{
		u8_Adress = CLCD_SET_CURSUR + Copy_u8Col + 64 ;
	}
	CLCD_vSendCommand(u8_Adress);
		_delay_ms(1);
}

/***************************************************************************************************************************************************
 * Brief:  Send The number that entered by the user to the screen to be displayed 
 *       
 * Params: - Copy_u64Number : The number that will be displayed on the screen 
 * 
 * Return: void 
 *   
 ***************************************************************************************************************************************************/
void CLCD_vSendNumber(u64 Copy_u64Number) {
    u8 arr[21]; // Array to store digits (max for u16 is 20 digits)
    u8 i = 0;
    if (Copy_u64Number == 0) {            
        CLCD_vSendData('0');
    }else {                                  // Extracting the digits from the number and storing it in reverse order in the array 
    while (Copy_u64Number != 0) {
        arr[i++] = (Copy_u64Number % 10) + '0';  // Convert digit to ASCII
        Copy_u64Number /= 10;  // Remove the last digit
    }

    // Send digits from the end to the start of the array 
    while (i > 0) {
        CLCD_vSendData(arr[--i]);
    }
	}
}

/***************************************************************************************************************************************************
 * Brief:  Send The string entered by the user to the screen to be displayed 
 *       
 * Params: - Copy_str: The string that will be displayed on the screen 
 * 
 * Return: void 
 ***************************************************************************************************************************************************/
void CLCD_vSendString(const u8* Copy_u8str) {
    u8 i = 0;
    // Loop through each character in the string and send it to the LCD
    while (Copy_u8str[i] != '\0') {
        CLCD_vSendData(Copy_u8str[i]);
        i++;  // Move to the next character in the string
    }
}


void CLCD_vSendFloat(f32 Copy_f32Number) {
    // Handle negative numbers
    if (Copy_f32Number < 0) {
        CLCD_vSendData('-');
        Copy_f32Number = -Copy_f32Number;  // Make the number positive for processing
    }

    // Extract integer and decimal parts
    u32 intPart = (u32)Copy_f32Number;
    f32 decimalPart = Copy_f32Number - intPart;

    // Round the decimal part to 2 places
    decimalPart *= 100;
    u32 decimalInt = (u32)(decimalPart + 0.5); // Proper rounding

    // Handle cases where rounding affects the integer part (e.g., 9.999 → 10.00)
    if (decimalInt == 100) {
        intPart++;
        decimalInt = 0;
    }

    // Display integer part
    CLCD_vSendNumber(intPart);

    // Only show decimal point and fraction if necessary
    if (decimalInt > 0) {
        CLCD_vSendData('.');

        // Ensure two-digit format (e.g., 5.30 instead of 5.3)
        if (decimalInt < 10) {
            CLCD_vSendData('0');
        }

        CLCD_vSendNumber(decimalInt);
    }
}

