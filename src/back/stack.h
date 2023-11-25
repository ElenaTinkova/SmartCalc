#ifndef STACK_H_
#define STACK_H_

#include "../back/data_validation.h"

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

typedef struct Stack {
  double value;
  int priority;
  type_t data_type;
  struct Stack *next;
} calc_stack;

void push(calc_stack **stack, double value, int priority, type_t type);
void pop(calc_stack **stack);
void destroy_stack(calc_stack **stack);
int is_stack_empty(calc_stack *stack);
void parser(calc_stack **stack, char *string);
calc_stack *reverse_stack(calc_stack **stack);
void print_stack(calc_stack *stack);
int add_number(char *string, char *num);
calc_stack *polish_stack(calc_stack **stack);
long double calc_result(calc_stack *rpn);
double binary_operation(double a, double b, int data_type);
double unary_operation(double a, int type);

#endif
