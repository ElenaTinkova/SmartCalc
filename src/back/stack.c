#include "../back/stack.h"

#include "../back/data_validation.h"

void push(calc_stack **stack, double value, int priority, type_t type) {
  calc_stack *top = (calc_stack *)calloc(1, sizeof(calc_stack));
  if (!top)
    exit(1);
  else {
    top->value = value;
    top->priority = priority;
    top->data_type = type;
    top->next = *stack;
    *stack = top;
  }
}

void pop(calc_stack **stack) {
  calc_stack *tmp = *stack;
  *stack = tmp->next;
  free(tmp);
}

void destroy_stack(calc_stack **stack) {
  while (*stack) pop(stack);
}

void parser(calc_stack **stack, char *string) {
  while (*string != '\0') {
    if (is_number(*string)) {
      char num[256];
      int lenght = add_number(string, num) - 1;
      push(stack, atof(num), 0, Number);
      string += lenght;
    } else if (*string == 'x')
      push(stack, 0, 0, X);
    else if (*string == '+')
      push(stack, 0, 1, Plus);
    else if (*string == '-')
      push(stack, 0, 1, Minus);
    else if (*string == '~')
      push(stack, 0, 5, UnarMinus);
    else if (*string == '*')
      push(stack, 0, 2, Multiply);
    else if (*string == '/')
      push(stack, 0, 2, Division);
    else if (*string == '^')
      push(stack, 0, 3, Pow);
    else if (*string == 'm') {
      push(stack, 0, 2, Mod);
      string += 2;
    } else if (*string == '(')
      push(stack, 0, 6, Lbrace);
    else if (*string == ')')
      push(stack, 0, -1, Rbrace);
    else if (*string == 's' && *(string + 1) == 'q') {
      push(stack, 0, 4, Sqrt);
      string += 3;
    } else if (*string == 'l' && *(string + 1) == 'n') {
      push(stack, 0, 4, Ln);
      string += 1;
    } else if (*string == 'l' && *(string + 1) == 'o') {
      push(stack, 0, 4, Log);
      string += 2;
    } else if (*string == 's' && *(string + 1) == 'i') {
      push(stack, 0, 4, Sin);
      string += 2;
    } else if (*string == 'c' && *(string + 1) == 'o') {
      push(stack, 0, 4, Cos);
      string += 2;
    } else if (*string == 't' && *(string + 1) == 'a') {
      push(stack, 0, 4, Tan);
      string += 2;
    } else if (*string == 'a' && *(string + 1) == 's') {
      push(stack, -1, 4, Asin);
      string += 3;
    } else if (*string == 'a' && *(string + 1) == 'c') {
      push(stack, 0, 4, Acos);
      string += 3;
    } else if (*string == 'a' && *(string + 1) == 't') {
      push(stack, 0, 4, Atan);
      string += 3;
    }
    string++;
  }
}

void print_stack(calc_stack *stack) {
  while (stack != NULL) {
    printf("Значение: %f, Приоритет: %d, Тип: %d\n", stack->value,
           stack->priority, stack->data_type);
    stack = stack->next;
  }
}

int add_number(char *string, char *num) {
  int num_len = 0;
  while (is_number(*string) || *string == '.') {
    *num++ = *string++;
    num_len++;
  }
  *num = '\0';
  return num_len;
}

calc_stack *reverse_stack(calc_stack **stack) {
  calc_stack *new = NULL;
  while (*stack) {
    push(&new, (*stack)->value, (*stack)->priority, (*stack)->data_type);
    pop(stack);
  }
  destroy_stack(stack);
  return new;
}

calc_stack *polish_stack(calc_stack **stack) {
  calc_stack *output = NULL;
  calc_stack *operators = NULL;
  while (*stack) {
    if ((*stack)->data_type == Number || (*stack)->data_type == X)
      push(&output, (*stack)->value, (*stack)->priority, (*stack)->data_type);
    else if ((*stack)->data_type == Lbrace)
      push(&operators, 0, 6, Lbrace);
    else if (((*stack)->data_type >= 2 && (*stack)->data_type < 17) ||
             (*stack)->data_type == UnarMinus) {
      if (operators == NULL || operators->data_type == Lbrace)
        push(&operators, (*stack)->value, (*stack)->priority,
             (*stack)->data_type);
      else if ((*stack)->data_type == UnarMinus)
        push(&operators, (*stack)->value, (*stack)->priority,
             (*stack)->data_type);
      else {
        if ((*stack)->priority > operators->priority)
          push(&operators, (*stack)->value, (*stack)->priority,
               (*stack)->data_type);
        else {
          while (operators != NULL &&
                 (*stack)->priority <= operators->priority &&
                 operators->data_type != Lbrace) {
            push(&output, operators->value, operators->priority,
                 operators->data_type);
            pop(&operators);
          }
          push(&operators, (*stack)->value, (*stack)->priority,
               (*stack)->data_type);
        }
      }
    } else if ((*stack)->data_type == Rbrace) {
      while (operators != NULL && operators->data_type != Lbrace) {
        push(&output, operators->value, operators->priority,
             operators->data_type);
        pop(&operators);
      }
      pop(&operators);
    }
    pop(stack);
  }
  while (operators) {
    push(&output, operators->value, operators->priority, operators->data_type);
    pop(&operators);
  }
  destroy_stack(stack);
  destroy_stack(&operators);
  return output;
}

double calc_result(calc_stack *rpn) {
  calc_stack *result = NULL;
  double res = 0, a = 0, b = 0;
  while (rpn) {
    if (rpn->next && rpn->next->next && rpn->data_type == Number &&
        rpn->next->data_type == Number &&
        (rpn->next->next->data_type >= 2 && rpn->next->next->data_type < 8)) {
      a = rpn->value;
      b = rpn->next->value;
      a = binary_operation(a, b, rpn->next->next->data_type);
      push(&result, a, 0, Number);
      rpn = rpn->next->next->next;
    } else if (rpn->next && rpn->data_type == Number &&
               (rpn->next->data_type == UnarMinus ||
                (rpn->next->data_type >= 8 && rpn->next->data_type < 17))) {
      a = rpn->value;
      a = unary_operation(a, rpn->next->data_type);
      push(&result, a, 0, Number);
      rpn = rpn->next->next;
    } else if (rpn->data_type >= 2 && rpn->data_type < 8) {
      b = result->value;
      pop(&result);
      a = result->value;
      pop(&result);
      a = binary_operation(a, b, rpn->data_type);
      push(&result, a, 0, Number);
      rpn = rpn->next;
    } else if (rpn->data_type == UnarMinus) {
      a = -result->value;
      pop(&result);
      push(&result, a, 0, Number);
      rpn = rpn->next;
    } else if (rpn->data_type >= 8 && rpn->data_type < 17) {
      a = result->value;
      pop(&result);
      a = unary_operation(a, rpn->data_type);
      push(&result, a, 0, Number);
      rpn = rpn->next;
    } else if (rpn) {
      push(&result, rpn->value, rpn->priority, rpn->data_type);
      rpn = rpn->next;
    }
  }
  if (result->next == NULL) res = result->value;
  destroy_stack(&rpn);
  destroy_stack(&result);
  return res;
}

double binary_operation(double a, double b, int type) {
  if (type == Plus) {
    a += b;
  } else if (type == Minus) {
    a -= b;
  } else if (type == Multiply) {
    a *= b;
  } else if (type == Division) {
    a /= b;
  } else if (type == Pow) {
    a = pow(a, b);
  } else if (type == Mod) {
    a = fmod(a, b);
  }
  return a;
}

double unary_operation(double a, int type) {
  if (type == UnarMinus)
    a = -a;
  else if (type == Cos)
    a = cos(a);
  else if (type == Sin)
    a = sin(a);
  else if (type == Tan)
    a = tan(a);
  else if (type == Acos)
    a = acos(a);
  else if (type == Asin)
    a = asin(a);
  else if (type == Atan)
    a = atan(a);
  else if (type == Sqrt)
    a = sqrt(a);
  else if (type == Ln)
    a = log(a);
  else if (type == Log)
    a = log10(a);
  return a;
}

void stack_with_x(calc_stack **stack, double x) {
  while (*stack) {
    if ((*stack)->data_type == X) {
      (*stack)->value = x;
      (*stack)->data_type = Number;
    }
    stack = &(*stack)->next;
  }
}
