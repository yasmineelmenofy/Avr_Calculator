/* **************************************************************************************************************************************************
 * [FILE NAME]:     CLCD_Config.h 
 * [MODULE]:        CLCD
 * [SWC LAYER]:     HAL
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 25/1/2025 
 ************************************************************************************************************************************************* */


#ifndef CLCD_CONFIG_H_INCLUDED
#define CLCD_CONFIG_H_INCLUDED

// Configuration of Control pins 

#define CLCD_RS_PORT   DIO_PORTA
#define CLCD_RS_PIN    DIO_PIN0

#define CLCD_RW_PORT   DIO_PORTA
#define CLCD_RW_PIN    DIO_PIN1

#define CLCD_EN_PORT   DIO_PORTA
#define CLCD_EN_PIN    DIO_PIN2

// Configuration of Data pins 

#define CLCD_DATA_PORT  DIO_PORTB


#endif 
