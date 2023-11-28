#include "../back/data_validation.h"
#include "../back/stack.h"

int main() {
  int error = 0;
  char string[256] = {0};
  char *example = "10+x";
  error = string_validation(example, string);
  if (!error) {
    calc_stack *first = NULL, *reversed_first = NULL;
    parser(&first, string);
    reversed_first = reverse_stack(&first);

    calc_stack *rpn = NULL, *output = NULL;
    rpn = polish_stack(&reversed_first);
    output = reverse_stack(&rpn);
    // print_stack(output);
    stack_with_x(&output, 3);
    double res = calc_result(output);
    printf("%.11f", res);
  }

  return 0;
}
