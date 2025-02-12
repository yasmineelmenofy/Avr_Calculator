/*
 * Calculator.h
 *
 *  Created on: 30 Jan 2025
 *      Author: yassm
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#include "STD_TYPES.h"

#define MAX_EXPR_SIZE 50

u8 Cal_u8preced(u8 op);
void Calc_vinfixToPost(const u8 *infix, u8 *postfix);
s32 Calc_intEvaluatepostfix(const u8* postfix);
void getExpressionFromKeypad(u8 *expression);
void calculate();


#endif /* CALCULATOR_H_ */
