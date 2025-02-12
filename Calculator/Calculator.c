/*
 * Calculator.c
 *  Created on: 30 Jan 2025
 *  Author: yasmin Elemenofy
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <util/delay.h>
#include <string.h>
#include"Calculator.h"
#include "stack.h"
#include "CLCD_Interface.h"
#include "KPD_Interface.h"
#include"STD_TYPES.h"

/***************************************************************************************************************************************************
 * Brief:  Determine the precedence of the operation to know which operation will be executed first
 *
 * Params: - u8 op : The operator
 *
 * Return: u8 (unsigned char)
 *
 ***************************************************************************************************************************************************/
u8 Cal_u8preced(u8 op) {
    switch(op) {
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;// invalid operator
    }
}


/***************************************************************************************************************************************************
 * Brief:  Convert an infix expression to postfix notation using the precedence of operators
 * can handle also multi-digit numbers.
 *
 * Params: - const u8 *infix  : The infix expression
 *         - u8 *postfix      : The output postfix expression
 *
 * Return: void
 *
 ***************************************************************************************************************************************************/
void Calc_vinfixToPost(const u8 *infix, u8 *postfix) {
    stack op;
    createstack(&op);
    u8 j = 0;
    u8 i = 0;
    u8 isNegative = 0; // Track if '-' is part of a negative number

    while (infix[i] != '\0') {

        if (isspace(infix[i])) {
            i++;
            continue;
        }
        if (infix[i] == '-' && (i == 0 || infix[i - 1] == '(' || infix[i - 1] == '+' || infix[i - 1] == '-' || infix[i - 1] == '*' || infix[i - 1] == '/' || infix[i - 1] == '^')) {
            isNegative = 1; // Mark it as a negative number
            i++;
        }

        if (isdigit(infix[i]) || (infix[i] == '.' && i > 0 && isdigit(infix[i - 1]))) {
            u8 numStr[20];
            u8 k = 0;
            u8 hasDecimal = 0;

            if (isNegative) {
                numStr[k++] = '-';
                isNegative = 0; // Reset flag after use
            }

            // Capture numeric part
            while (isdigit(infix[i]) || (infix[i] == '.' && !hasDecimal)) {
                if (infix[i] == '.') {
                    hasDecimal = 1; // Mark decimal presence
                }
                numStr[k++] = infix[i++];
            }

            numStr[k] = '\0'; // Null-terminate

            strcpy(&postfix[j], numStr);
            j += k;
            postfix[j++] = ' '; // Separator
            continue;
        }

        // Handle opening parenthesis
        if (infix[i] == '(') {
            push(infix[i], &op);
        }
        // Handle closing parenthesis
        else if (infix[i] == ')') {
            while (!stackempty(&op) && stacktop(&op) != '(') {
                postfix[j++] = pop(&op);
                postfix[j++] = ' ';
            }
            pop(&op); // Remove '(' from stack
        }
        else {
            while (!stackempty(&op) && Cal_u8preced(stacktop(&op)) >= Cal_u8preced(infix[i])) {
                postfix[j++] = pop(&op);
                postfix[j++] = ' ';
            }
            push(infix[i], &op);
        }

        i++; // Move to next character
    }

    // Pop remaining operators
    while (!stackempty(&op)) {
        postfix[j++] = pop(&op);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0'; // Null-terminate postfix string
}

/***************************************************************************************************************************************************
 * Brief:  Evaluate a postfix expression to compute its final result
 *
 * Params: - const u8 *postfix : The postfix expression to be evaluated
 *         - u8* resultstr: After converting float number to string will be stored here
 *
 * Return: void
 *
 ***************************************************************************************************************************************************/
void Calc_sEvaluatePostfix(const u8* postfix, u8* resultStr) {
    stack value;
    createstack(&value);
    f32 tempNum = 0.0;
    f32 decimalPlace = 1.0;
    u8 isBuildingNumber = 0;
    u8 isNegative = 0;
    u8 isFloating = 0;

    for (u8 i = 0; postfix[i]; i++) {
        u8 output = postfix[i];

        // Handle negative numbers when followed by a digit
        if (output == '-' && (i == 0 || postfix[i - 1] == ' ') && isdigit(postfix[i + 1])) {
            isNegative = 1;
            continue;
        }

        // Handle numbers (including floating points)
        if (isdigit(output)) {
            if (isFloating) {
                tempNum = tempNum + (output - '0') * decimalPlace;
                decimalPlace *= 0.1;
            } else {
                tempNum = tempNum * 10 + (output - '0');
            }
            isBuildingNumber = 1;
        }
        else if (output == '.') {
            isFloating = 1;
            decimalPlace = 0.1;
        }
        else if (output == ' ') {
            if (isBuildingNumber) {
                if (isNegative) tempNum = -tempNum;
                push(tempNum, &value);
                // Reset tracking variables
                tempNum = 0.0;
                isBuildingNumber = 0;
                isNegative = 0;
                isFloating = 0;
                decimalPlace = 1.0;
            }
        }
        else {
            // Handle operators
            f32 val1 = pop(&value);
            f32 val2 = pop(&value);
            f32 tempResult = 0.0;

            switch (output) {
                case '+': tempResult = val2 + val1; break;
                case '-': tempResult = val2 - val1; break;
                case '*': tempResult = val2 * val1; break;
                case '/':
                    if (val1 == 0) {
                        strcpy(resultStr, "Error: Division by zero");
                        return;
                    }
                    tempResult = val2 / val1;
                    break;
                case '^': tempResult = pow(val2, val1); break;
                default:
                    strcpy(resultStr, "Error: Invalid operator");
                    return;
            }
            push(tempResult, &value);
        }
    }

    // Convert final result to string
    f32 finalResult = pop(&value);
    dtostrf(finalResult, 4, 2, resultStr); // Format to 2 decimal places
}
/***************************************************************************************************************************************************
 * Brief:  Captures an arithmetic expression from the keypad and stores it in the provided buffer.
 *
 * Params: - u8 *expression : Pointer to the buffer where the expression will be stored.
 *
 * Return: void
 *
 ***************************************************************************************************************************************************/
void getExpressionFromKeypad(u8 *expression) {
    u8 index = 0;
    u8 key;
    u8 decimalFlag = 0;
    u8 lastChar = '\0';  // Track last character for validation

    while (1) {
        key = KPD_u8GetKey();
        if (key != KPD_NOT_PRESSED) {
            if (key == '=') {
                if (index > 0) {
                    expression[index] = '\0';
                    break;
                }
            }
            else if (key == 'C') { // Clear the expression
                index = 0;
                decimalFlag = 0;
                expression[0] = '\0';
                CLCD_vClearScreen();
                CLCD_vSendCommand(CLCD_SET_CURSUR);
            }
            else if (key == 'D') { // Delete last character
                if (index > 0) {
                    index--;
                    if (expression[index] == '.') {
                        decimalFlag = 0; // Allow decimal again if deleted
                    }
                    expression[index] = '\0';

                    // Refresh display
                    CLCD_vSendCommand(CLCD_CLEAR);
                    CLCD_vSendString(expression);
                }
            }
            else if (key == '.') {
                if (decimalFlag == 0 && isdigit(lastChar)) { // Allow decimal only in a valid number
                    decimalFlag = 1;
                    expression[index++] = key;
                    CLCD_vSendData(key); // Display the key
                }
            }
            else if (isdigit(key) || key == '(' || key == ')') {
                // Reset decimal flag when a new number starts
                if (!isdigit(lastChar) && lastChar != '.') {
                    decimalFlag = 0;
                }
                expression[index++] = key;
                CLCD_vSendData(key);
            }
            else if (key == '+' || key == '-' || key == '*' || key == '/' || key == '^') {
                if (key == '-' && (index == 0 || lastChar == '(' || lastChar == '*' || lastChar == '/' || lastChar == '+' || lastChar == '^')) {
                    // Allow '-' at the beginning, after '(', or after another operator (for negative numbers)
                    expression[index++] = key;
                    CLCD_vSendData(key);
                }
                else if (index > 0 && lastChar != '(' && lastChar != '+' && lastChar != '-' && lastChar != '*' && lastChar != '/' && lastChar != '^') {
                    // Allow other operators only if not preceded by another operator
                    expression[index++] = key;
                    decimalFlag = 0;
                    CLCD_vSendData(key);
                }
            }



            lastChar = key;
        }
    }
}

/***************************************************************************************************************************************************
 * Brief:  Handles the calculation process by reading an expression from the keypad, converting it to postfix,
 *         evaluating the result, and displaying it on the LCD.
 *
 * Params: - None
 *
 * Return: void
 *
 ***************************************************************************************************************************************************/
void calculate() {
    u8 infix[MAX_EXPR_SIZE];
    u8 postfix[MAX_EXPR_SIZE];
    u8 result[MAX_EXPR_SIZE];

    getExpressionFromKeypad(infix);

    Calc_vinfixToPost(infix, postfix);
   Calc_sEvaluatePostfix(postfix,result);

    CLCD_vClearScreen();
    if (strstr(result, "Error") != NULL) {
        CLCD_vSendString(result);
    } else {
        CLCD_vSendString(result);
    }

    while (1) {
        u8 key = KPD_u8GetKey();
        if (key == 'C') {
            CLCD_vClearScreen();  // Clear the screen
            break;
        }
    }
}
