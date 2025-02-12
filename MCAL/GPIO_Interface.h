/* **************************************************************************************************************************************************
 * [FILE NAME]:     GPIO_Interface.h 
 * [MODULE]:        GPIO/DIO
 * [SWC LAYER]:     MCAL
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 6/1/2025 
 ************************************************************************************************************************************************* */
#include "STD_TYPES.h"
#ifndef GPIO_INTERFACE_H_INCLUDED
#define GPIO_INTERFACE_H_INCLUDED

// Pin direction 
#define DIO_PIN_OUTPUT  1  
#define DIO_PIN_INPUT   0 

//  DIO Pin Values 
#define DIO_PIN_HIGH    1
#define DIO_PIN_LOW     0 

// port Directions 
#define DIO_PORT_INPUT   0x00         // All the pins inside the port will be input 
#define DIO_PORT_OUTPUT  0xFF        //  All the pins inside the port will be output 

// Port Values 
#define DIO_PORT_HIGH    0xFF       // All the pins of the port will be high 
#define DIO_PORT_LOW     0x00      //  All the pins of the port will be low 

//Pins 
#define DIO_PIN0    0
#define DIO_PIN1    1
#define DIO_PIN2    2
#define DIO_PIN3    3
#define DIO_PIN4    4
#define DIO_PIN5    5
#define DIO_PIN6    6
#define DIO_PIN7    7

//Ports 
#define DIO_PORTA    0
#define DIO_PORTB    1
#define DIO_PORTC    2
#define DIO_PORTD    3

//Error State 
typedef enum {
	DIO_NOK =0 ,
	DIO_OK  =1
}Error_State;

Error_State DIO_enSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
Error_State DIO_enSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
Error_State DIO_enTogPortValue(u8 Copy_u8Port);
Error_State DIO_enGetPortValue(u8 Copy_u8Port, u8 *Copy_u8ptrvalue);
Error_State DIO_enSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
Error_State DIO_enSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
Error_State DIO_enGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *Copy_u8ptrvalue);


#endif 
