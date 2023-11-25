#include "../back/data_validation.h"
#include "../back/stack.h"

int main() {
  int error = 0;
  char string[256] = {0};
  char *example = "jgjghg";
  error = string_validation(example, string);
  if (!error) {
    calc_stack *first = NULL, *reversed_first = NULL;
    parser(&first, string);
    reversed_first = reverse_stack(&first);

    calc_stack *rpn = NULL, *output = NULL;
    rpn = polish_stack(&reversed_first);
    output = reverse_stack(&rpn);
    // print_stack(output);
    long double res = calc_result(output);
    printf("res is: %.12Lf", res);
  }

  return 0;
}
