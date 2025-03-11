#include "s21_test_main.h"

#line 1 "s21_round_test.check"

START_TEST(test1) {
#line 4
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.456f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test2) {
#line 12
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.456f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test3) {
#line 20
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test4) {
#line 28
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test5) {
#line 36
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123456.0f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(123456.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test6) {
#line 44
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(0.00001f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(0.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test7) {
#line 52
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(0.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(1.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test8) {
#line 60
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-1.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-2.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test9) {
  s21_decimal value, result, expected;

  s21_from_float_to_decimal(123.5f, &value);
  s21_round(value, &result);
  s21_from_float_to_decimal(124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test10) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.5f, &value);
  s21_round(value, &result);
  s21_from_float_to_decimal(-124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test11) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.0f, &value);
  s21_round(value, &result);
  s21_from_float_to_decimal(123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test12) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.0f, &value);
  s21_round(value, &result);
  s21_from_float_to_decimal(-123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_fail_0) {
  s21_decimal value;
  s21_from_float_to_decimal(123.456f, &value);
  int code = s21_round(value, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_round_half_positive) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_round_half_negative) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_round_half_odd_positive) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_round_half_odd_negative) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-124.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_set_sign_negative) {
  s21_decimal value, result;
  s21_from_float_to_decimal(-123.456f, &value);
  s21_round(value, &result);

  ck_assert_int_eq(get_sign(&result), 1);
}
END_TEST

START_TEST(test_round_half_even_positive) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(124.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(125.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_round_half_even_negative) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-124.5f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-125.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_round_near_half_positive) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(123.4999f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

START_TEST(test_round_near_half_negative) {
  s21_decimal value, result, expected;
  s21_from_float_to_decimal(-123.499f, &value);
  s21_round(value, &result);

  s21_from_float_to_decimal(-123.0f, &expected);
  ck_assert_int_eq(compare_decimal(result, expected), 0);
}
END_TEST

Suite *round_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_round");
  tc = tcase_create("Core");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test8);
  tcase_add_test(tc, test9);
  tcase_add_test(tc, test10);
  tcase_add_test(tc, test11);
  tcase_add_test(tc, test12);
  tcase_add_test(tc, test_fail_0);
  tcase_add_test(tc, test_round_half_positive);
  tcase_add_test(tc, test_round_half_negative);
  tcase_add_test(tc, test_round_half_odd_positive);
  tcase_add_test(tc, test_round_half_odd_negative);
  tcase_add_test(tc, test_set_sign_negative);
  tcase_add_test(tc, test_round_half_even_positive);
  tcase_add_test(tc, test_round_half_even_negative);
  tcase_add_test(tc, test_round_near_half_positive);
  tcase_add_test(tc, test_round_near_half_negative);

  suite_add_tcase(s, tc);

  return s;
}