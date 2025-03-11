#include "s21_test_main.h"

#include <check.h>

int main(void) {
  int number_failed = 0;

  SRunner *sr = srunner_create(NULL);

  srunner_add_suite(sr, mul_suite());
  srunner_add_suite(sr, sub_suite());
  srunner_add_suite(sr, div_suite());
  srunner_add_suite(sr, add_suite());
  srunner_add_suite(sr, floor_suite());
  srunner_add_suite(sr, round_suite());
  srunner_add_suite(sr, compare_suite());
  srunner_add_suite(sr, negate_suite());
  srunner_add_suite(sr, truncate_suite());
  srunner_add_suite(sr, decimal_to_float_suite());
  srunner_add_suite(sr, decimal_to_int_suite());
  srunner_add_suite(sr, float_to_decimal_suite());
  srunner_add_suite(sr, int_to_decimal_suite());
  srunner_add_suite(sr, rand_arithmetics_suite());
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
