/* **************************************************************************************************************************************************
 * [FILE NAME]:     GPIO_Private.h 
 * [MODULE]:        GPIO/DIO
 * [SWC LAYER]:     MCAL
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 6/1/2025 
 ************************************************************************************************************************************************* */

#ifndef GPIO_PRIVATE_H_INCLUDED
#define GPIO_PRIVATE_H_INCLUDED

// Port A register addresses
#define PORTA_REG   (*(vu8 *)(0x3B)) 
#define DDRA_REG    (*(vu8 *)(0x3A))
#define PINA_REG    (*(vu8 *)(0x39))

// Port B register addresses
#define PORTB_REG   (*(vu8 *)(0x38)) 
#define DDRB_REG    (*(vu8 *)(0x37))
#define PINB_REG    (*(vu8 *)(0x36))

// Port C register addresses
#define PORTC_REG   (*(vu8 *)(0x35)) 
#define DDRC_REG    (*(vu8 *)(0x34))
#define PINC_REG    (*(vu8 *)(0x33))

// Port D register addresses
#define PORTD_REG   (*(vu8 *)(0x32)) 
#define DDRD_REG    (*(vu8 *)(0x31))
#define PIND_REG    (*(vu8 *)(0x30))


#endif 
