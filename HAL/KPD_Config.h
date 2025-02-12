/* **************************************************************************************************************************************************
 * [FILE NAME]:     KPD_Config.h 
 * [MODULE]:        Keypad driver 
 * [SWC LAYER]:     HAL
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 27/1/2025 
 ************************************************************************************************************************************************* */


#ifndef KPD_CONFIG_H_INCLUDED
#define KPD_CONFIG_H_INCLUDED


#define KPD_ROW_PORT DIO_PORTC
#define KPD_COL_PORT DIO_PORTD

#define KPD_ROW_START DIO_PIN0
#define KPD_ROW_END   DIO_PIN3

#define KPD_COL_START DIO_PIN0
#define KPD_COL_END   DIO_PIN5



u8 kpd_u8buttons[4][6] = {
    {'C', '7', '8', '9', 'r', '/'},  // Row A: ON/C, 7, 8, 9, X, ÷
    {'-', '4', '5', '6', '(', '*'}, // Row B: ±, 4, 5, 6, -, MRC
    {'D', '1', '2', '3', ')', '-'},  // Row C: %, 1, 2, 3, +, M-
    {'A', '0', '.', '=', ')', '+'}   // Row D: √, 0, =, M+, (empty cells)
};

#define KPD_ROW0 DIO_PIN0
#define KPD_ROW1 DIO_PIN1
#define KPD_ROW2 DIO_PIN2
#define KPD_ROW3 DIO_PIN3


#define KPD_COL0 DIO_PIN0
#define KPD_COL1 DIO_PIN1
#define KPD_COL2 DIO_PIN2
#define KPD_COL3 DIO_PIN3
#define KPD_COL4 DIO_PIN4
#define KPD_COL5 DIO_PIN5


#endif 
