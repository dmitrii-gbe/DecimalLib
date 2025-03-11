#include "s21_test_main.h"

START_TEST(test_decimal_less) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(15, &d1);
  s21_from_int_to_decimal(20, &d2);

  int result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 1);
  s21_from_int_to_decimal(25, &d1);
  s21_from_int_to_decimal(10, &d2);
  result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 0);

  s21_from_int_to_decimal(-5, &d1);
  s21_from_int_to_decimal(-3, &d2);
  result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_less_floats) {
  s21_decimal d1, d2;
  s21_from_float_to_decimal(2.75f, &d1);
  s21_from_float_to_decimal(3.14f, &d2);

  int result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_float_to_decimal(4.5f, &d1);
  s21_from_float_to_decimal(4.5f, &d2);
  result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 0);

  s21_from_float_to_decimal(-0.5f, &d1);
  s21_from_float_to_decimal(0.5f, &d2);
  result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_less_zero) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(0, &d2);

  int result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_less_neg_num) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-15, &d1);
  s21_from_int_to_decimal(-10, &d2);

  int result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-8, &d1);
  s21_from_int_to_decimal(-12, &d2);
  result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 0);

  s21_from_int_to_decimal(-7, &d1);
  s21_from_int_to_decimal(-7, &d2);
  result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_less_bitwise_repres) {
  s21_decimal d1 = {{54321, 0, 0, 0b00000000000001100000000000000000}};
  s21_decimal d2 = {{30, 0, 0, 0b10000000000000110000000000000000}};

  int result = s21_is_less(d1, d2);
  ck_assert_int_eq(result, 0);

  result = s21_is_less(d2, d1);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_greater_positive_integr) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(10, &d1);
  s21_from_int_to_decimal(5, &d2);

  int result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(5, &d1);
  s21_from_int_to_decimal(5, &d2);
  result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_mixed_sign) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(10, &d1);
  s21_from_int_to_decimal(-10, &d2);

  int result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 1);

  result = s21_is_greater(d2, d1);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_zero_comparisons) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(0, &d2);

  int result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_float_point_num) {
  s21_decimal d1, d2;
  s21_from_float_to_decimal(3.14f, &d1);
  s21_from_float_to_decimal(2.75f, &d2);

  int result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_float_to_decimal(4.5f, &d1);
  s21_from_float_to_decimal(4.5f, &d2);
  result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_equal_positive_num) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(123456, &d1);
  s21_from_int_to_decimal(123456, &d2);

  int result = s21_is_equal(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_equal_negative_num) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-123456, &d1);
  s21_from_int_to_decimal(-123456, &d2);

  int result = s21_is_equal(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_equal_zero) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(0, &d2);

  int result = s21_is_equal(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_not_equal_positive) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(123456, &d1);
  s21_from_int_to_decimal(654321, &d2);

  int result = s21_is_not_equal(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_not_equal_negative) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-123456, &d1);
  s21_from_int_to_decimal(-654321, &d2);

  int result = s21_is_not_equal(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_not_equal_zero) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(1, &d2);

  int result = s21_is_not_equal(d1, d2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_decimal_less_or_equal_positive) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(10, &d1);
  s21_from_int_to_decimal(20, &d2);

  int result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(20, &d1);
  s21_from_int_to_decimal(20, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(30, &d1);
  s21_from_int_to_decimal(20, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_less_or_equal_negative) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-10, &d1);
  s21_from_int_to_decimal(-5, &d2);

  int result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-5, &d1);
  s21_from_int_to_decimal(-5, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-3, &d1);
  s21_from_int_to_decimal(-5, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_less_or_equal_mixed_sign) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-10, &d1);
  s21_from_int_to_decimal(10, &d2);

  int result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(10, &d1);
  s21_from_int_to_decimal(-10, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_less_or_equal_zero) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(0, &d2);

  int result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(1, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(1, &d1);
  s21_from_int_to_decimal(0, &d2);
  result = s21_is_less_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_or_equal_positive) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(20, &d1);
  s21_from_int_to_decimal(10, &d2);

  int result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(10, &d1);
  s21_from_int_to_decimal(10, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(5, &d1);
  s21_from_int_to_decimal(10, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_or_equal_negative) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-5, &d1);
  s21_from_int_to_decimal(-10, &d2);

  int result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-10, &d1);
  s21_from_int_to_decimal(-10, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-15, &d1);
  s21_from_int_to_decimal(-10, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_or_equal_mixed_sign) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(10, &d1);
  s21_from_int_to_decimal(-10, &d2);

  int result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-10, &d1);
  s21_from_int_to_decimal(10, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_decimal_greater_or_equal_zero) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(0, &d2);

  int result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(1, &d1);
  s21_from_int_to_decimal(0, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(0, &d1);
  s21_from_int_to_decimal(1, &d2);
  result = s21_is_greater_or_equal(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_set_new_sign_positive) {
  s21_decimal decimal;
  memset(&decimal, 0, sizeof(s21_decimal));
  set_new_sign(&decimal, 1);
  ck_assert_uint_eq(decimal.bits[3] & SIGN_MASK, SIGN_MASK);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(test_set_new_sign_neg) {
  s21_decimal decimal;
  memset(&decimal, 0, sizeof(s21_decimal));
  set_new_sign(&decimal, 0);
  ck_assert_uint_eq(decimal.bits[3] & SIGN_MASK, 0);
  ck_assert_uint_eq(decimal.bits[0], 0);
  ck_assert_uint_eq(decimal.bits[1], 0);
  ck_assert_uint_eq(decimal.bits[2], 0);
}
END_TEST

START_TEST(s21_equal_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test3) {
  s21_decimal val1 = {
      {(int)4294967290, (int)4294967295, (int)4294967295, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test4) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test5) {
  s21_decimal val1 = {{(int)3270290481, (int)1272579, 0, 0x00000000}};
  s21_decimal val2 = {{(int)3270290481, (int)1272579, 0, 0x00100000}};
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test6) {
  s21_decimal val1 = {{(int)3270290481, (int)1272579, 0, 0x000B0000}};
  s21_decimal val2 = {{(int)3270290481, (int)1272579, 0, 0x00100000}};
  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test9) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_equal(val1, val2));
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_equal_test10) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, s21_is_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test3) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test4) {
  s21_decimal val1 = {{1234567, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1234567, 0, 0, 0b00000000000000110000000000000000}};
  ck_assert_int_eq(0, s21_is_less(val1, val2));
  ck_assert_int_eq(0, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test5) {
  s21_decimal val1 = {{1, 0, 0, 0x00010000}};
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};
  ck_assert_int_eq(1, s21_is_less(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test6) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00010000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_less(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test9) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};

  ck_assert_int_eq(1, s21_is_less(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test10) {
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00000000}};

  ck_assert_int_eq(1, s21_is_less(val1, val2));
  ck_assert_int_eq(1, s21_is_less_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_less_test11) {
  s21_decimal val2 = {{0, 0, 0, 0x00000000}};
  s21_decimal val1 = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, s21_is_less(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test3) {
  s21_decimal val1 = {
      {(int)4294967290, (int)4294967295, (int)4294967295, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test4) {
  s21_decimal val1 = {{1, 0, 0, 0x00000000}};
  s21_decimal val2 = {{1, 0, 0, 0x00070000}};
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test5) {
  s21_decimal val1 = {{(int)3270290481, (int)1272579, 0, 0x00000000}};
  s21_decimal val2 = {{(int)3270290481, (int)1272579, 0, 0x00100000}};
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test6) {
  s21_decimal val1 = {{(int)3270290481, (int)1272579, 0, 0x000B0000}};
  s21_decimal val2 = {{(int)3270290481, (int)1272579, 0, 0x00100000}};
  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test7) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test8) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test9) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(1, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_not_equal_test10) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(0, s21_is_not_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test2) {
  s21_decimal val1 = {{1, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0}};

  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test3) {
  s21_decimal val1 = {{1, 0, 0, 0x00010000}};
  s21_decimal val2 = {{10, 0, 0, 0x00000000}};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
  ck_assert_int_eq(0, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test4) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X80000000}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test5) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test6) {
  s21_decimal val1 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00000000}};
  s21_decimal val2 = {{0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0X00010000}};

  ck_assert_int_eq(1, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test7) {
  s21_decimal val1 = {{10000000, 0, 0, 0x00000000}};
  s21_decimal val2 = {{10000000, 0, 0, 0x80000000}};
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test8) {
  s21_decimal val1 = {{0, 0, 0, 0}};
  s21_decimal val2 = {{0, 0, 0, 0x80000000}};

  ck_assert_int_eq(0, s21_is_greater(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test9) {
  s21_decimal val1 = {{1, 0, 0, 0x000C0000}};
  s21_decimal val2 = {{1, 0, 0, 0x00100000}};
  ck_assert_int_eq(1, s21_is_greater(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_test10) {
  s21_decimal val1 = {{1, 0, 0, 0x000C0000}};
  s21_decimal val2 = {{1, 0, 0, 0x000C0000}};
  ck_assert_int_eq(0, s21_is_greater(val1, val2));
  ck_assert_int_eq(1, s21_is_greater_or_equal(val1, val2));
}
END_TEST

START_TEST(s21_is_greater_negative_numbers) {
  s21_decimal d1, d2;
  s21_from_int_to_decimal(-3, &d1);
  s21_from_int_to_decimal(-5, &d2);

  int result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 1);

  s21_from_int_to_decimal(-5, &d1);
  s21_from_int_to_decimal(-3, &d2);
  result = s21_is_greater(d1, d2);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *compare_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21 Decimal Compare Tests");
  tc = tcase_create("Core");

  tcase_add_test(tc, test_decimal_less);
  tcase_add_test(tc, test_decimal_less_floats);
  tcase_add_test(tc, test_decimal_less_zero);
  tcase_add_test(tc, test_decimal_less_neg_num);
  tcase_add_test(tc, test_decimal_less_bitwise_repres);

  tcase_add_test(tc, test_decimal_greater_positive_integr);
  tcase_add_test(tc, test_decimal_greater_mixed_sign);
  tcase_add_test(tc, test_decimal_greater_zero_comparisons);
  tcase_add_test(tc, test_decimal_greater_float_point_num);

  tcase_add_test(tc, test_decimal_equal_positive_num);
  tcase_add_test(tc, test_decimal_equal_negative_num);
  tcase_add_test(tc, test_decimal_equal_zero);

  tcase_add_test(tc, test_decimal_not_equal_positive);
  tcase_add_test(tc, test_decimal_not_equal_negative);
  tcase_add_test(tc, test_decimal_not_equal_zero);
  tcase_add_test(tc, test_decimal_less_or_equal_positive);
  tcase_add_test(tc, test_decimal_less_or_equal_negative);
  tcase_add_test(tc, test_decimal_less_or_equal_mixed_sign);
  tcase_add_test(tc, test_decimal_less_or_equal_zero);

  tcase_add_test(tc, test_decimal_greater_or_equal_positive);
  tcase_add_test(tc, test_decimal_greater_or_equal_negative);
  tcase_add_test(tc, test_decimal_greater_or_equal_mixed_sign);
  tcase_add_test(tc, test_decimal_greater_or_equal_zero);

  tcase_add_test(tc, test_set_new_sign_positive);
  tcase_add_test(tc, test_set_new_sign_neg);

  tcase_add_test(tc, s21_equal_test);
  tcase_add_test(tc, s21_equal_test2);
  tcase_add_test(tc, s21_equal_test3);
  tcase_add_test(tc, s21_equal_test4);
  tcase_add_test(tc, s21_equal_test5);
  tcase_add_test(tc, s21_equal_test6);
  tcase_add_test(tc, s21_equal_test7);
  tcase_add_test(tc, s21_equal_test8);
  tcase_add_test(tc, s21_equal_test9);
  tcase_add_test(tc, s21_equal_test10);

  tcase_add_test(tc, s21_is_less_test);
  tcase_add_test(tc, s21_is_less_test2);
  tcase_add_test(tc, s21_is_less_test3);
  tcase_add_test(tc, s21_is_less_test4);
  tcase_add_test(tc, s21_is_less_test5);
  tcase_add_test(tc, s21_is_less_test6);
  tcase_add_test(tc, s21_is_less_test7);
  tcase_add_test(tc, s21_is_less_test8);
  tcase_add_test(tc, s21_is_less_test9);
  tcase_add_test(tc, s21_is_less_test10);
  tcase_add_test(tc, s21_is_less_test11);

  tcase_add_test(tc, s21_not_equal_test);
  tcase_add_test(tc, s21_not_equal_test2);
  tcase_add_test(tc, s21_not_equal_test3);
  tcase_add_test(tc, s21_not_equal_test4);
  tcase_add_test(tc, s21_not_equal_test5);
  tcase_add_test(tc, s21_not_equal_test6);
  tcase_add_test(tc, s21_not_equal_test7);
  tcase_add_test(tc, s21_not_equal_test8);
  tcase_add_test(tc, s21_not_equal_test9);
  tcase_add_test(tc, s21_not_equal_test10);

  tcase_add_test(tc, s21_is_greater_test);
  tcase_add_test(tc, s21_is_greater_test2);
  tcase_add_test(tc, s21_is_greater_test3);
  tcase_add_test(tc, s21_is_greater_test4);
  tcase_add_test(tc, s21_is_greater_test5);
  tcase_add_test(tc, s21_is_greater_test6);
  tcase_add_test(tc, s21_is_greater_test7);
  tcase_add_test(tc, s21_is_greater_test8);
  tcase_add_test(tc, s21_is_greater_test9);
  tcase_add_test(tc, s21_is_greater_test10);
  tcase_add_test(tc, s21_is_greater_negative_numbers);

  suite_add_tcase(s, tc);

  return s;
}
