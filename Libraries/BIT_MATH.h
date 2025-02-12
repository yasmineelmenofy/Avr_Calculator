/* **************************************************************************************************************************************************
 * [FILE NAME]:     BIT_MATH.h 
 * [MODULE]:        BIT Manipulation
 * [SWC LAYER]:     Libraries 
 * ----------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 6/1/2025 
 ************************************************************************************************************************************************* */


#ifndef BIT_MATH_H_INCLUDED
#define BIT_MATH_H_INCLUDED

// BIT Manipulation  
#define      SET_BIT(REG,BIT)                (REG |= (1 << (BIT)))
#define      CLR_BIT(REG,BIT)                (REG &= ~(1 << (BIT)))
#define      Tog_BIT(REG,BIT)                (REG ^= (1 << (BIT)))
#define      GET_BIT(REG,BIT)                ((REG >> (BIT)) & 0x01)


// Register Manipulation 
#define      SET_REG(REG)                    (REG = 0xFF) // Setting all the bits of the register to one 
#define      CLR_REG(REG)                    (REG = 0x00) // Setting all the bits of the register to zero 


#endif 
