/*!
 * \mainpage
 * \section intro_sec Description of the project
 * The implementation of an extended version of a calculator. \n
 * In addition to basic arithmetic operations such as add/subtract and
 * multiply/divide, this calculator has the ability to calculate arithmetic
 * expressions by following the order, as well as some mathematical functions
 * (sine, cosine, logarithm, etc.). \n
 *   Besides calculating expressions, it supports
 * the usage of the x variable and the graphing of the corresponding function.
 * \n Also it has a credit calculator's mode.
 */

/*!
\file
\brief Header file describing the functions used to validate a string.
*/

#ifndef DATA_VALIDATION_H_
#define DATA_VALIDATION_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * \brief Validates a mathematical expression
 * \param input string-expression received from the user
 * \param string converted copy of the expression string after validation
 * \return returns 1 if an error occurred, 0 if the expression was successfully read
 */
int string_validation(char *input, char *string);

/*!
 * \brief Removes spaces between characters
 * \param string source string
 * \param copy copy of the source string without spaces
 */
void check_spaces(char *string, char *copy);

/*!
 * \brief Performs an initial check for the correct placement of dots in the expression and changes the ',' symbol to the '.' symbol
 * \param string string-expression
 * \return returns 1 if an error occurred, 0 if the expression was successfully read
 */
int check_comma_with_dot(char *string);

/*!
 * \brief Checks the correctness of parentheses in an expression and their pairing
 * \param string string-expression
 * \return returns 1 if an error occurs, 0 if the expression is successfully read
 */
int check_braces(char *string);

/*!
 * \brief Checks whether a character is a number
 * \param symb character to be checked
 * \return returns 1 if the character is a number, 0 if the character is not a number
 */
int is_number(char symb);

/*!
 * \brief Checks whether a character is an operation sign
 * \param symb character to be checked
 * \return returns 1 if the symbol is an operation sign, 0 if the symbol is not an operation
 */
int is_operator(char symb);

/*!
 * \brief Checks the correctness of the dot notation
 * \param string string-expression
 * \param float_dot Flag indicating the presence of a decimal point in the expression (1 - if the point has been encountered before, 0 - if there was no point)
 * \param i Index of the character being checked
 * \return returns 1 in case of an error, 0 - if there is no error
 */
int check_dots(char *string, int float_dot, int i);

/*!
 * \brief Checks the correctness of the number notation
 * \param string string-expression
 * \param i pointer to the current character in the string
 * \param float_dot pointer to the value of the flag indicating the presence of a decimal point in the expression (1 - if the point has been encountered before, 0 - if there was no point)
 * \return returns 1 in case of an error, 0 - if there is no error
 */
int check_number(char *string, int *i, int *float_dot);

/*!
 * \brief Checks the correctness of the function name
 * \param string string-expression
 * \param i pointer to the current character in the string
 * \return returns 1 in case of an error, 0 - if there is no error
 */
int check_funcs(char *string, int *i);

/*!
 * \brief Checks whether the symbol is an operator sign
 * \param string string-expression
 * \param i index of the current symbol in the string
 * \return кeturns 0 if the check is successful, 1 if it is not an operator
 */
int is_func(char *string, int i);

/*!
 * \brief Checks the correctness of the operation signs
 * \param string string-expression
 * \param i index of the current symbol in the string
 * \return returns 1 in case of an error, 0 - if there is no error.
 */
int check_operators(char *string, int i);

/*!
 * \brief Checks for the presence of the "mod" operation in the given expression string
 * \param string string-expression
 * \param i index of the current symbol in the string
 * \return returns 1 if the operation is present, 0 - if it is not
 */
int is_mod(char *string, int i);

/*!
 * \brief Checks the correctness of the "mod" operation
 * \param string string-expression
 * \param i index of the current symbol in the string
 * \return returns 1 in case of an error, 0 - if there is no error
 */
int check_mod(char *string, int i);

/*!
 * \brief Checks the correctness of x value in operation  'x' в строке
 * \param string string-expression
 * \param i index of the current symbol in the string
 * \return returns 1 in case of an error, 0 - if there is no error
 */
int check_x(char *string, int i);

/*!
 * \brief Performs an additional check for the correct use of parentheses in the string
 * \param string string-expression 
 * \param i index of the current symbol in the string
 * \return returns 1 in case of an error, 0 - if there is no error
 */
int braces(char *string, int i);

/*!
 * \brief Checks if the symbol '-' is an unary minus, replaces the symbol with '~' if an unary minus is encountered
 * \param string string-expression 
 * \param i index of the current symbol in the string
 */
void check_unar(char *string, int i);

#endif
