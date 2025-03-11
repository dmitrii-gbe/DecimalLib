#include "s21_test_main.h"

START_TEST(test_negate_positive) {
  s21_decimal src = {0};
  src.bits[0] = 15;
  src.bits[3] = 0x00000000;

  s21_decimal expected = {0};
  expected.bits[0] = 15;
  expected.bits[3] = 0x80000000;

  s21_decimal result = {0};
  int flag = s21_negate(src, &result);

  ck_assert_int_eq(flag, 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal src = {0};
  src.bits[0] = 15;
  src.bits[3] = 0x80000000;

  s21_decimal expected = {0};
  expected.bits[0] = 15;
  expected.bits[3] = 0x00000000;

  s21_decimal result = {0};
  int flag = s21_negate(src, &result);

  ck_assert_int_eq(flag, 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal src = {0};
  src.bits[0] = 0;
  src.bits[3] = 0x00000000;

  s21_decimal expected = {0};
  expected.bits[0] = 0;
  expected.bits[3] = 0x80000000;

  s21_decimal result = {0};
  int flag = s21_negate(src, &result);

  ck_assert_int_eq(flag, 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_negate_min_negative) {
  s21_decimal src = {0};
  src.bits[0] = 0x80000000;
  src.bits[3] = 0x80000000;

  s21_decimal expected = {0};
  expected.bits[0] = 0x80000000;
  expected.bits[3] = 0x00000000;

  s21_decimal result = {0};
  int flag = s21_negate(src, &result);

  ck_assert_int_eq(flag, 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_negate_max_positive) {
  s21_decimal src = {0};
  src.bits[0] = 0x7FFFFFFF;
  src.bits[1] = 0xFFFFFFFF;
  src.bits[2] = 0xFFFFFFFF;
  src.bits[3] = 0x00000000;

  s21_decimal expected = {0};
  expected.bits[0] = 0x7FFFFFFF;
  expected.bits[1] = 0xFFFFFFFF;
  expected.bits[2] = 0xFFFFFFFF;
  expected.bits[3] = 0x80000000;

  s21_decimal result = {0};
  int flag = s21_negate(src, &result);

  ck_assert_int_eq(flag, 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_negate_null_result) {
  s21_decimal src = {0};
  src.bits[0] = 0x12345678;
  src.bits[1] = 0x87654321;
  src.bits[2] = 0xABCDEF01;
  src.bits[3] = 0x80000000;

  s21_decimal *result = NULL;

  int flag = s21_negate(src, result);

  ck_assert_int_eq(flag, 1);
}
END_TEST

Suite *negate_suite(void) {
  Suite *suite = suite_create("s21_negate");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_negate_positive);
  tcase_add_test(tc_core, test_negate_negative);
  tcase_add_test(tc_core, test_negate_zero);
  tcase_add_test(tc_core, test_negate_min_negative);
  tcase_add_test(tc_core, test_negate_max_positive);
  tcase_add_test(tc_core, test_negate_null_result);

  suite_add_tcase(suite, tc_core);

  return suite;
}