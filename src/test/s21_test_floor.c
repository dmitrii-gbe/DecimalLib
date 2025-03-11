#include "s21_test_main.h"

#line 1 "s21_floor_test.check"

START_TEST(test1) {
#line 4
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(1234.56f, &value);
  s21_floor(value, &result);

  s21_from_float_to_decimal(1234.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test2) {
#line 12
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.9999f, &value);
  s21_floor(value, &result);

  s21_from_float_to_decimal(123.0000f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test3) {
#line 20
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-1234.56f, &value);
  s21_floor(value, &result);

  s21_from_int_to_decimal(-1235, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test4) {
#line 28
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123456.0f, &value);
  s21_floor(value, &result);

  s21_from_float_to_decimal(123456.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test5) {
#line 36
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123456.0f, &value);
  s21_floor(value, &result);

  s21_from_float_to_decimal(-123456.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test6) {
#line 44
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.000f, &value);
  s21_floor(value, &result);

  s21_from_float_to_decimal(-123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test7) {
#line 52
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-0.000001f, &value);
  s21_floor(value, &result);

  s21_from_float_to_decimal(-1.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_fail_0) {
  s21_decimal value;
  s21_from_float_to_decimal(123.456f, &value);
  int code = s21_floor(value, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

Suite *floor_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_floor");
  tc = tcase_create("Core");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test_fail_0);

  suite_add_tcase(s, tc);

  return s;
}