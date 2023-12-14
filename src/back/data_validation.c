#include "../back/data_validation.h"

#include "../back/stack.h"

// this func checks if everything ok with the incoming string

int string_validation(char *input, char *string) {
  int error = 0, float_dot = 0;
  if (input == NULL || strlen(input) == 0 || strlen(input) > 255) error = 1;
  if (!error) {
    check_spaces(input, string);
    if (check_comma_with_dot(string)) error = 1;
  }
  if (!error) error = check_braces(string);

  if (!error) {
    for (int i = 0; !error && string[i] != '\0'; i++) {
      if (string[i] == '.') {
        error = check_dots(string, float_dot, i);
        float_dot = 1;
      } else if (is_number(string[i])) {
        error = check_number(string, &i, &float_dot);
      } else if (is_operator(string[i])) {
        error = check_operators(string, i);
        float_dot = 0;
      } else if (is_mod(string, i)) {
        error = check_mod(string, i);
        if (!error) {
          float_dot = 0;
          i += 2;
        }
      } else if (string[i] == 'x') {
        error = check_x(string, i);
      } else if (string[i] == '(' || string[i] == ')') {
        error = braces(string, i);
      } else {
        error = check_funcs(string, &i);
        if (!error) float_dot = 0;
      }
    }
  }
  return error;
}

void check_spaces(char *input, char *copy) {
  while (*input != '\0') {
    if (*input == '\n' || *input == ' ' || *input == '\t') {
      input++;
      continue;
    } else {
      strncpy(copy, input, 1);
      copy++;
      input++;
    }
  }
  *copy = '\0';
}

int check_comma_with_dot(char *string) {
  if (string[0] == '.' || string[0] == ',' ||
      string[strlen(string) - 1] == '.' || string[strlen(string) - 1] == ',')
    return 1;
  for (int i = 1; string[i] != '\0'; i++)
    if (string[i] == ',') string[i] = '.';
  return 0;
}

int check_braces(char *string) {
  int brace = 0, i = 0, error = 0;
  if (string[0] == ')' || string[strlen(string) - 1] == '(') error = 1;
  if (!error) {
    while (string[i] != '\0') {
      if (string[i] == '(') {
        brace++;
        if (string[i + 1] == ')') {
          error = 1;
          break;
        }
      }
      if (string[i] == ')') {
        brace--;
        if (i != 0) {
          if (string[i - 1] == '(') {
            error = 1;
            break;
          }
        }
      }
      i++;
    }
  }
  if (brace || brace < 0) error = 1;
  return error;
}

int check_dots(char *string, int float_dot, int i) {
  int error = 0;
  if (float_dot)
    error = 1;
  else {
    if (i != 0) {
      if (!is_number(string[i + 1]) || !is_number(string[i - 1])) error = 1;
    }
  }
  return error;
}

int is_number(char symb) { return (symb >= '0' && symb <= '9'); }

int is_operator(char symb) {
  const char *operators = "+-/*^~";
  return strchr(operators, symb) != NULL ? 1 : 0;
}

int check_number(char *string, int *i, int *float_dot) {
  int error = 0, len_num = 0;
  while (is_number(string[*i])) {
    len_num++;
    string++;
  }
  if (string[*i + len_num] == '.') {
    len_num++;
    string++;
    if (!is_number(string[*i]) || *float_dot == 1) {
      error = 1;
    } else {
      *float_dot = 1;
      while (is_number(string[*i])) {
        len_num++;
        string++;
      }
    }
  }
  *i += len_num - 1;
  return error;
}

int is_func(char *string, int i) {  // 0 - is func, 1 - error
  return check_funcs(string, &i);
}

int check_funcs(char *string, int *i) {
  int error = 0, len_fun = 0;

  if (strncmp(string + (*i), "ln", 2) == 0) {
    len_fun += 2;
  } else if (strncmp(string + (*i), "sin", 3) == 0 ||
             strncmp(string + (*i), "cos", 3) == 0 ||
             strncmp(string + (*i), "tan", 3) == 0 ||
             strncmp(string + (*i), "log", 3) == 0) {
    len_fun += 3;
  } else if (strncmp(string + (*i), "asin", 4) == 0 ||
             strncmp(string + (*i), "acos", 4) == 0 ||
             strncmp(string + (*i), "atan", 4) == 0 ||
             strncmp(string + (*i), "sqrt", 4) == 0)
    len_fun += 4;
  else
    error = 1;
  if (!error && *(string + *i - 1) != 'd' && !is_operator(*(string + *i - 1)) &&
      *(string + *i - 1) != '(' && is_number(*(string + *i - 1)))
    error = 1;
  if (!error && *(string + *i + len_fun) != '(') error = 1;

  (*i) += len_fun;
  return error;
}

int check_operators(char *string, int i) {
  int error = 0;
  int func = i + 1;
  if (!is_number(string[func]) && string[func] != '(' &&
      check_funcs(string, &func) && string[func] != 'x' && string[func] != '-')
    error = 1;
  if (string[i] == '+' || string[i] == '-') {
    if (i != 0 && string[i - 1] != '(' && string[i - 1] != ')' &&
        !is_number(string[i - 1]) && string[i - 1] != 'x' &&
        string[func] != 'x' && !is_number(string[func]) &&
        string[i - 1] != '*' && string[i - 1] != '/') {
      error = 1;
    }
  } else {
    if (string[i - 1] != ')' && !is_number(string[i - 1]) &&
        string[i - 1] != 'x')
      error = 1;
  }
  if (string[i] == '-') {
    check_unar(string, i);
  }
  return error;
}

int is_mod(char *string, int i) {
  int is_mod = 0;
  if (strncmp(&string[i], "mod", 3) == 0) {
    is_mod = 1;
  }
  return is_mod;
}

int check_mod(char *string, int i) {
  int error = 0;
  if (i == 0) return 1;
  if (!is_number(string[i - 1]) && string[i - 1] != ')' && string[i - 1] != 'x')
    error = 1;
  if (!is_number(string[i + 3]) && string[i + 3] != '(' &&
      string[i + 3] != 'x' && is_func(string, i + 3) && string[i + 3] != '-')
    error = 1;
  return error;
}

int check_x(char *string, int i) {
  int error = 0;
  if (i != 0 && !is_operator(string[i - 1]) && string[i - 1] != '(' &&
      !is_mod(string, i - 3) && string[i - 1] != '~')
    error = 1;

  if (!is_mod(string, i + 1) && !is_operator(string[i + 1]) &&
      string[i + 1] != '\0' && string[i + 1] != ')')
    error = 1;

  return error;
}

int braces(char *string, int i) {
  int error = 0;
  if (string[i] == '(') {
    if (i != 0 && !is_operator(string[i - 1]) && !is_mod(string, i - 3) &&
        string[i - 1] != '(')
      error = 1;
  } else {
    if (string[i + 1] != '\0' && !is_operator(string[i + 1]) &&
        !is_mod(string, i + 1) && string[i + 1] != ')')
      error = 1;
  }
  return error;
}

void check_unar(char *string, int i) {
  if ((i == 0 || string[i - 1] == '(' || is_operator(string[i - 1]) ||
       is_mod(string, i - 3)) &&
      !is_number(string[i - 1]))
    *(string + i) = '~';
  else
    *(string + i) = '-';
}
