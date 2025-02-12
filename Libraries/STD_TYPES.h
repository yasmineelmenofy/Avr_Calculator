/* **************************************************************************************************************************************************
 * [FILE NAME]:     STD_Types.h 
 * [MODULE]:        Standard Types
 * [SWC LAYER]:     Libraries 
 * ----------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 6/1/2025 
 ************************************************************************************************************************************************* */


#ifndef STD_TYPES_H_INCLUDED
#define STD_TYPES_H_INCLUDED

// unsigned Data_Types 
typedef unsigned char            u8;
typedef volatile unsigned char  vu8;
typedef unsigned short          u16;
typedef unsigned long           u32;
typedef unsigned long long      u64;


// Signed Data_Types 
typedef signed char              s8;
typedef volatile signed char    vs8;
typedef signed short            s16;
typedef signed long             s32;
typedef signed long long        s64;

// Boolean Type 
typedef enum {
	False =0,
	True  =1
}boolean;

// Float Data_Types
typedef float                   f32;  
typedef double                  f64;

#endif 
