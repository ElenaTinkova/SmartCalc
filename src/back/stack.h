/*!
\file
\brief Header file with a description of functions and structures used for working with a stack
*/

#ifndef STACK_H_
#define STACK_H_

#include "../back/data_validation.h"

/*!
 * \brief Definition of type_t data type using enum enumeration to simplify
 * stack operations and define data types for parsing in RPN.
 */
typedef enum {
  Number = 0,
  X = 1,
  Plus = 2,
  Minus = 3,
  Multiply = 4,
  Division = 5,
  Pow = 6,
  Mod = 7,
  Cos = 8,
  Sin = 9,
  Tan = 10,
  Acos = 11,
  Asin = 12,
  Atan = 13,
  Sqrt = 14,
  Ln = 15,
  Log = 16,
  Lbrace = 17,
  Rbrace = 18,
  UnarMinus = 19
} type_t;

/*!
 * \brief Definition of a stack structure based on a singly linked list
 * \param value the value of the number
 * \param priority the priority value of the mathematical operation
 * \param data_type the data type placed in the structure
 * \param next pointer to the next node in the stack
 */
typedef struct Stack {
  double value;
  int priority;
  type_t data_type;
  struct Stack *next;
} calc_stack;

/*!
 * \brief Adding a new node to the stack
 * \param stack pointer to a pointer to the stack where the new element should be placed
 * \param value value of the element, if it is a number (0 if it is not) 
 * \param priority priority value of the operation (0 if it is a number) 
 * \param type data type being placed in the structure
 */
void push(calc_stack **stack, double value, int priority, type_t type);

/*!
 * \brief Removing a node from the stack
 * \param stack pointer to a pointer to the stack
 */
void pop(calc_stack **stack);

/*!
 * \brief Complete clearing of the stack from all elements
 * \param stack pointer to a pointer to the stack
 */
void destroy_stack(calc_stack **stack);

/*!
 * \brief Reverse of the stack
 * \param stack pointer to pointer to the stack to be reversed
 * \return new reversed stack, original is deleted
 */
calc_stack *reverse_stack(calc_stack **stack);

/*!
 * \brief Writes number characters to an array
 * \param string string-expression
 * \param num character array into which number characters are written, including decimal point
 * \return number of characters that form the number (its length)
 */
int add_number(char *string, char *num);

/*!
 * \brief Performs expression calculation
 * \param rpn stack of operands and operations in reverse Polish notation
 * \return result of the calculation
 */
double calc_result(calc_stack *rpn);

/*!
 * \brief Calculates operation with two values
 * \param a value of first operand
 * \param b value of second operand
 * \param data_type type of operation
 * \return result of the calculation
 */
double binary_operation(double a, double b, int data_type);

/*!
 * \brief Calculates operation with one value
 * \param a value of the operand
 * \param type type of operation
 * \return result of the calculation
 */
double unary_operation(double a, int type);

/*!
 * \brief Performs a call to other functions to obtain the expression result
 * \param string string-expression
 * \param x value of variable x (0 if not specified)
 * \return result of the calculation
 */
double calculations(char *string, double x);

/*!
 * \brief Determines the type of operation and adds it to the stack structure
 * \param string pointer to character in the string
 * \param stack stack to which the element is added
 * \return length of the operation characters
 */
int push_operators_and_functions(char *string, calc_stack **stack);

/*!
 * \brief Determines whether the symbol is a function name
 * \param symb symbol to check for matching
 * \return returns 1 if the symbol belongs to the function name, 0 if the condition is not met
 */
int is_funcs(char symb);

/*!
 * \brief Determines the priority of operation execution
 * \param symb symbol to check for matching
 * \return returns 1 for addition/subtraction, 
 * 2 – multiplication/division/modulo,
 * 3 – power,
 * 4 – functions,
 * 5 – unary minus
 */
int math_precendence(char symb);

/*!
 * \brief Performs parsing of infix expression lexemes and adds elements to the stack, converting the expression to postfix using the shunting-yard algorithm
 * \param string string-expression
 * \param x value of variable x (0 if not specified)
 * \return stack with elements in reverse Polish notation
 */
calc_stack *new_polish_stack(char *string, double x);

#endif
