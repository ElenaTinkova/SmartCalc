#ifndef DATA_VALIDATION_H_
#define DATA_VALIDATION_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 255
#define MIN_STR_SIZE 3

int string_validation(char *input, char *string);
void check_spaces(char *string, char *copy);
int check_comma_with_dot(char *string);
int check_braces(char *string);
int is_number(char symb);
int is_operator(char symb);
int check_dots(char *string, int float_dot, int i);
int check_number(char *string, int *i, int *float_dot);
int check_funcs(char *string, int *i);
int is_func(char *string, int i);
int check_operators(char *string, int i);
int is_mod(char *string, int i);
int check_mod(char *string, int i);
int check_x(char *string, int i);
int braces(char *string, int i);
void check_unar(char *string, int i);

#endif
