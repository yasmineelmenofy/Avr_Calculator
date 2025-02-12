/* **************************************************************************************************************************************************
 * FILE NAME:     GPIO_Program.c
 * MODULE:        GPIO/DIO
 * SWC LAYER:     MCAL
 * Board:         ATMEGA32
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * AUTHOR:        Yasmine Elmenofy 
 * CREATION DATE: 6/1/2025 
 ************************************************************************************************************************************************* */
 
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 #include "GPIO_Private.h"
 #include "GPIO_Interface.h"
 #include "GPIO_Config.h"

///////////////////////////////////////////////////////////////////////// DIO PORTS FUNCTIONS///////////////////////////////////////////////////////

/***************************************************************************************************************************************************
 * Brief:  Sets the direction of a specified DIO port (all pins as input or output)
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 *   - Copy_u8Direction: The direction to set for the port 
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/

 Error_State DIO_enSetPortDirection(u8 Copy_u8Port ,u8 Copy_u8Direction){
	 Error_State Local_enErrorState = DIO_NOK;
	 if(Copy_u8Port <= DIO_PORTD ){
		 switch(Copy_u8Port){
			 case DIO_PORTA : DDRA_REG = Copy_u8Direction; break;
			 case DIO_PORTB : DDRB_REG = Copy_u8Direction; break;	
			 case DIO_PORTC : DDRC_REG = Copy_u8Direction; break;
			 case DIO_PORTD : DDRD_REG = Copy_u8Direction; break;
			  
		 }
		 Local_enErrorState = DIO_OK;
		  
	 } 
	 return Local_enErrorState;
		 
 }
 
 /***************************************************************************************************************************************************
 * Brief:  Write value to a specified DIO port (Set the pins of the port to high/low)
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 *   - Copy_u8Value: Set the value of the port (high or low)
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/
 
 Error_State DIO_enSetPortValue(u8 Copy_u8Port ,u8 Copy_u8Value){
	 Error_State Local_enErrorState = DIO_NOK;
	 if( Copy_u8Port <= DIO_PORTD ){
		 switch(Copy_u8Port){
			 case DIO_PORTA : PORTA_REG = Copy_u8Value; break;
			 case DIO_PORTB : PORTB_REG = Copy_u8Value; break;	
			 case DIO_PORTC : PORTC_REG = Copy_u8Value; break;
			 case DIO_PORTD : PORTD_REG = Copy_u8Value; break;
			 
		 }
		  Local_enErrorState = DIO_OK;
		  
	 } 
	 return Local_enErrorState;
		 
 }
 
 /***************************************************************************************************************************************************
 * Brief:  Toggle the value of the specified DIO port (Toggle the value of all the pins inside the ports)
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/
 Error_State DIO_enTogPortValue(u8 Copy_u8Port ){
	 Error_State Local_enErrorState = DIO_NOK;
	 if(Copy_u8Port <= DIO_PORTD ){
		 switch(Copy_u8Port){
			 case DIO_PORTA : PORTA_REG = ~PORTA_REG; break;
			 case DIO_PORTB : PORTB_REG = ~PORTB_REG; break;	
			 case DIO_PORTC : PORTC_REG = ~PORTC_REG; break;
			 case DIO_PORTD : PORTD_REG = ~PORTD_REG; break;
			 
		 }
		  Local_enErrorState = DIO_OK;
		  
	 } 
	 return Local_enErrorState;
		 
 }
 
 /***************************************************************************************************************************************************
 * Brief:  Read value of a specified DIO port 
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 *   - *Copy_u8ptrvalue: Pointer to save the value of the port 
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/
 Error_State DIO_enGetPortValue(u8 Copy_u8Port ,u8 *Copy_u8ptrvalue){
	 Error_State Local_enErrorState = DIO_NOK;
	 if(Copy_u8Port <= DIO_PORTD ){
		 switch(Copy_u8Port){
			 case DIO_PORTA : *Copy_u8ptrvalue = PINA_REG; break;
			 case DIO_PORTB : *Copy_u8ptrvalue = PINB_REG; break;	
			 case DIO_PORTC : *Copy_u8ptrvalue = PINC_REG; break;
			 case DIO_PORTD : *Copy_u8ptrvalue = PIND_REG; break;
			 
		 }
		  Local_enErrorState = DIO_OK;
		  
	 } 
	 return Local_enErrorState;
		 
 }
 
///////////////////////////////////////////////////////////////////////// DIO PINS FUNCTIONS///////////////////////////////////////////////////////

/***************************************************************************************************************************************************
 * Brief:  Sets the direction of a specified DIO Pin 
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 *   - Copy_u8Pin: The pin to configure   (DIO_PINA , DIO_PINB)
 *   - Copy_u8Direction: The direction to set for the pin 
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/

 Error_State DIO_enSetPinDirection(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Direction){
	 Error_State Local_enErrorState = DIO_NOK;
	 if(Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7){
	 	 if(Copy_u8Direction == DIO_PIN_OUTPUT){
	 	 switch(Copy_u8Port){
			 case DIO_PORTA :SET_BIT(DDRA_REG,Copy_u8Pin) ; break;
			 case DIO_PORTB :SET_BIT(DDRB_REG,Copy_u8Pin); break;	
			 case DIO_PORTC :SET_BIT(DDRC_REG,Copy_u8Pin) ; break;
			 case DIO_PORTD :SET_BIT(DDRD_REG,Copy_u8Pin) ; break;	  
		 }
		 
		 }else if(Copy_u8Direction == DIO_PIN_INPUT){
			 switch(Copy_u8Port){
			 case DIO_PORTA :CLR_BIT(DDRA_REG,Copy_u8Pin) ; break;
			 case DIO_PORTB :CLR_BIT(DDRB_REG,Copy_u8Pin); break;	
			 case DIO_PORTC :CLR_BIT(DDRC_REG,Copy_u8Pin) ; break;
			 case DIO_PORTD :CLR_BIT(DDRD_REG,Copy_u8Pin) ; break;	  
			 
		 }
		 }	 
		 Local_enErrorState = DIO_OK;	  
	 } 
	 return Local_enErrorState;
		 
 }
 
/***************************************************************************************************************************************************
 * Brief:  Sets the Value of a specified DIO Pin 
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 *   - Copy_u8Pin: The pin to configure   (DIO_PINA , DIO_PINB)
 *   - Copy_u8Value: The Value that will be set for the pin 
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/

 Error_State DIO_enSetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 Copy_u8Value){
	 Error_State Local_enErrorState = DIO_NOK;
	 if(Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7){
	 	 if(Copy_u8Value == DIO_PIN_HIGH){
	 	 switch(Copy_u8Port){
			 case DIO_PORTA :SET_BIT(PORTA_REG,Copy_u8Pin) ; break;
			 case DIO_PORTB :SET_BIT(PORTB_REG,Copy_u8Pin); break;	
			 case DIO_PORTC :SET_BIT(PORTC_REG,Copy_u8Pin) ; break;
			 case DIO_PORTD :SET_BIT(PORTD_REG,Copy_u8Pin) ; break;	  
		 }
		 
		 }else if(Copy_u8Value == DIO_PIN_LOW){
			 switch(Copy_u8Port){
			 case DIO_PORTA :CLR_BIT(PORTA_REG,Copy_u8Pin) ; break;
			 case DIO_PORTB :CLR_BIT(PORTB_REG,Copy_u8Pin); break;	
			 case DIO_PORTC :CLR_BIT(PORTC_REG,Copy_u8Pin) ; break;
			 case DIO_PORTD :CLR_BIT(PORTD_REG,Copy_u8Pin) ; break;	  
			 
		 }
		 }	 
		 Local_enErrorState = DIO_OK;	  
	 } 
	 return Local_enErrorState;
		 
 }
 
 
 
 

 /***************************************************************************************************************************************************
 * Brief:  Read value of a specified DIO Pin 
 * 
 * Params:
 *   - Copy_u8Port: The port to configure (DIO_PORTA, DIO_PORTB)
 *   - Copy_u8Pin: The pin to configure   (DIO_PINA , DIO_PINB)
 *   - *Copy_u8ptrvalue: Pointer to save the value of the pin
 * 
 * Return: Error_State indicating the function status:
 *   - DIO_OK: Operation successful
 *   - DIO_NOK: Invalid port identifier 
 ***************************************************************************************************************************************************/
 Error_State DIO_enGetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin , u8 *Copy_u8ptrvalue){
	 Error_State Local_enErrorState = DIO_NOK;
	 if(Copy_u8Port <= DIO_PORTD && Copy_u8Pin <= DIO_PIN7){
		 switch(Copy_u8Port){
			 case DIO_PORTA : *Copy_u8ptrvalue = GET_BIT(PINA_REG,Copy_u8Pin); break;
			 case DIO_PORTB : *Copy_u8ptrvalue = GET_BIT(PINB_REG,Copy_u8Pin); break;	
			 case DIO_PORTC : *Copy_u8ptrvalue = GET_BIT(PINC_REG,Copy_u8Pin); break;
			 case DIO_PORTD : *Copy_u8ptrvalue = GET_BIT(PIND_REG,Copy_u8Pin); break;
			 
		 }
		  Local_enErrorState = DIO_OK;
		  
	 } 
	 return Local_enErrorState;
		 
 }
 
