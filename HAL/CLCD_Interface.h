/* **************************************************************************************************************************************************
 * [FILE NAME]:     CLCD_Interface.h 
 * [MODULE]:        CLCD
 * [SWC LAYER]:     HAL
 * --------------------------------------------------------------------------------------------------------------------------------------------------
 * [AUTHOR]:        Yasmine Elmenofy 
 * [CREATION DATE]: 25/1/2025 
 ************************************************************************************************************************************************* */

#ifndef CLCD_INTERFACE_H_INCLUDED
#define CLCD_INTERFACE_H_INCLUDED

#define CLCD_8BIT_MODE                0x38
#define CLCD_CLEAR                    0x01
#define CLCD_SET_CURSUR               0x02
#define CLCD_DISPLAY_ONOFF_CONTROL    0x0c              // display on cursur off 
#define CLCD_ENTRYMODE                0x06
#define CLCD_CURSOR_ON  0x0E   // Cursor ON (Solid)
#define CLCD_CURSOR_BLINK 0x0F// shift cursur from left to right
#define CLCD_CURSOR_LEFT   0x10

#define CLCD_ROW_1 0 
#define CLCD_ROW_2 1 

#define CLCD_COL_1   0 
#define CLCD_COL_2   1
#define CLCD_COL_3   2
#define CLCD_COL_4   3
#define CLCD_COL_5   4
#define CLCD_COL_6   5
#define CLCD_COL_7   6
#define CLCD_COL_8   7
#define CLCD_COL_9   8
#define CLCD_COL_10  9
#define CLCD_COL_11  10
#define CLCD_COL_12  11
#define CLCD_COL_13  12
#define CLCD_COL_14  13
#define CLCD_COL_15  14
#define CLCD_COL_16  15


void CLCD_vInit(void);
void CLCD_vSendData(u8 Copy_u8Data);
void CLCD_vSendCommand(u8 Copy_u8Command);
void CLCD_vClearScreen(void);
void CLCD_vSetCursurPostion(u8 Copy_u8Row, u8 Copy_u8Col);
void CLCD_vSendNumber(u64 Copy_u64Number);
void CLCD_vSendString(const u8* Copy_u8str);
void CLCD_vSendFloat(f32 Copy_f32Number) ;


#endif 
