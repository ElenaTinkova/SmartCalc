#include "../test/tests.h"

START_TEST(expression_1) {
  int error = 0;
  char string[256] = {0};
  char *example = "1.23-5";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = -3.77;
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_2) {
  int error = 0;
  char string[256] = {0};
  char *example =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = -30.0721649484536082;
  ck_assert_ldouble_eq(check, check_origin);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_3) {
  int error = 0;
  char string[256] = {0};
  char *example = "10+sin(5+5)";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = 9.455978889111;
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_4) {
  int error = 0;
  char string[256] = {0};
  char *example = "10+2*(9-2)^2";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = 108;
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_5) {
  int error = 0;
  char string[256] = {0};
  char *example = "3+6*2/3*ln(2)*sqrt(9)-atan(2.95)";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin =
      3 + 6 * 2 / 3 * log(2) * sqrt(9) - atan(2.95);  // 10.0737964928543437
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_6) {
  int error = 0;
  char string[256] = {0};
  char *example = "123,78.11.05";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_7) {
  int error = 0;
  char string[256] = {0};
  char *example = "+";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_8) {
  int error = 0;
  char string[256] = {0};
  char *example = "))(";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_9) {
  int error = 0;
  char string[256] = {0};
  char *example = "12";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = 12;
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_10) {
  int error = 0;
  char string[256] = {0};
  char *example = "123,78- 11.05-";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_11) {
  int error = 0;
  char string[256] = {0};
  char *example = "mod4";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_12) {
  int error = 0;
  char string[256] = {0};
  char *example = "aboba bob";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_13) {
  int error = 0;
  char string[256] = {0};
  char *example = "x + 1234";
  double x = 5;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = 1239;
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_14) {
  int error = 0;
  char string[256] = {0};
  char *example = "()";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_15) {
  int error = 0;
  char string[256] = {0};
  char *example = "/4)-489,";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_16) {
  int error = 0;
  char string[256] = {0};
  char *example = "12modcos(2)*(sin(1)/10)";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = fmod(12, cos(2)) * (sin(1) / 10);
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_17) {
  int error = 0;
  char string[256] = {0};
  char *example = "-1112.000009mod(-151*ln(10,12345)/4)-489";
  double x = 0;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = fmod(-1112.000009, -151 * log(10.12345) / 4) - 489;
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_18) {
  int error = 0;
  char string[256] = {0};
  char *example = "";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_19) {
  int error = 0;
  char string[256] = {0};
  char *example = "3mod)x";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_20) {
  int error = 0;
  char string[256] = {0};
  char *example =
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
      "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(expression_21) {
  int error = 0;
  char string[256] = {0};
  char *example = "atan(x)*-1+log(1)+acos(1)*tan(-x)-asin(1)";
  double x = 4;
  error = string_validation(example, string);
  double check = calculations(string, x);
  double check_origin = atan(x) * -1 + log(1) + acos(1) * tan(-x) - asin(1);
  ck_assert_ldouble_eq_tol(check, check_origin, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(expression_22) {
  int error = 0;
  char string[256] = {0};
  char *example = "+-*/~";
  error = string_validation(example, string);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(credit) {
  credit_input *test_input = calloc(1, sizeof(credit_input));
  test_input->amount = 1000000;
  test_input->term = 12;
  test_input->percent = 10;

  credit_output test_output;
  test_output = annuity_calculations(*test_input);

  ck_assert_float_eq(test_output.monthly_payment, 87915.89);
  ck_assert_float_eq(test_output.interest_overpayment, 54990.65);
  ck_assert_float_eq(test_output.total_payments, 1054990.65);
}
END_TEST

START_TEST(deposit) {
  deposit_info *dep = calloc(1, sizeof(deposit_info));
  Month *months = calloc(12, sizeof(Month));

  dep->input_summ = 1000000;
  dep->temp_of_placement = 12;
  dep->percent = 10;
  dep->tax_rate = 13;
  dep->frequency_of_payments = 1;

  dep->capitalization_of_interest = 0;

  deposit_calculation(dep, months);

  ck_assert_float_eq(dep->accrued_interest, 100000);
  ck_assert_float_eq(dep->result_summ, 1087000);
  ck_assert_float_eq(dep->tax_amount, 13000);

  dep->capitalization_of_interest = 1;

  dep->accrued_interest = 0;
  dep->result_summ = 0;
  dep->tax_amount = 0;

  deposit_calculation(dep, months);

  ck_assert_float_eq_tol(dep->accrued_interest, 104085, 10);
  ck_assert_float_eq(dep->result_summ, 1090554.35);
  ck_assert_float_eq_tol(dep->tax_amount, 13531.1, 10);

  free(dep);
  free(months);
}
END_TEST

void srunner_calculator_test(SRunner *sr) {
  Suite *suit_1 = suite_create("regular calculator");
  TCase *tc1_1 = tcase_create("regular calculator");
  suite_add_tcase(suit_1, tc1_1);

  tcase_add_test(tc1_1, expression_1);
  tcase_add_test(tc1_1, expression_2);
  tcase_add_test(tc1_1, expression_3);
  tcase_add_test(tc1_1, expression_4);
  tcase_add_test(tc1_1, expression_5);
  tcase_add_test(tc1_1, expression_6);
  tcase_add_test(tc1_1, expression_7);
  tcase_add_test(tc1_1, expression_8);
  tcase_add_test(tc1_1, expression_9);
  tcase_add_test(tc1_1, expression_10);
  tcase_add_test(tc1_1, expression_11);
  tcase_add_test(tc1_1, expression_12);
  tcase_add_test(tc1_1, expression_13);
  tcase_add_test(tc1_1, expression_14);
  tcase_add_test(tc1_1, expression_15);
  tcase_add_test(tc1_1, expression_16);
  tcase_add_test(tc1_1, expression_17);
  tcase_add_test(tc1_1, expression_18);
  tcase_add_test(tc1_1, expression_19);
  tcase_add_test(tc1_1, expression_20);
  tcase_add_test(tc1_1, expression_21);
  tcase_add_test(tc1_1, expression_22);

  tcase_add_test(tc1_1, credit);
  tcase_add_test(tc1_1, deposit);

  srunner_add_suite(sr, suit_1);
}

int main() {
  Suite *s = suite_create("calc's tests");
  SRunner *sr = srunner_create(s);
  int err;

  srunner_calculator_test(sr);

  srunner_run_all(sr, CK_NORMAL);
  err = srunner_ntests_failed(sr);
  srunner_free(sr);

  return err == 0 ? 0 : 1;
}