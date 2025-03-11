#include "s21_test_main.h"

START_TEST(test_add6) {
  s21_decimal d1, d2, result;
  s21_from_int_to_decimal(111111, &d1);
  s21_from_int_to_decimal(222222, &d2);
  char *pow_d1 = get_power(&d1);
  char *pow_d2 = get_power(&d2);
  *pow_d1 = 3;
  *pow_d2 = 8;

  int code = s21_add(d1, d2, &result);
  ck_assert_int_eq(code, 0);
  char *res = decimal_to_string(&result);
  ck_assert_str_eq(res, "111.11322222");
  free(res);
}
END_TEST

START_TEST(test_add_fail_0) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_add(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_1) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_2) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add_fail_4) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_add0) {
  s21_decimal val1 = {{(int)3550036140, (int)3631355950, 77886739, 0x000F0000}};
  s21_decimal val2 = {{(int)4230301616, 1342635, 0, 0x00090000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], (int)2897644716);
  ck_assert_int_eq(res.bits[1], (int)1942577246);
  ck_assert_int_eq(res.bits[2], 77887052);
  ck_assert_uint_eq(res.bits[3], 983040);
}
END_TEST

START_TEST(test_add1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = TEST_ARITHMETIC_POS_INF;

  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, check);
}
END_TEST

START_TEST(test_add2) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(test_add3) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], check.bits[0]);
  ck_assert_int_eq(result.bits[1], check.bits[1]);
  ck_assert_int_eq(result.bits[2], check.bits[2]);
  ck_assert_int_eq(result.bits[3], check.bits[3]);
}
END_TEST

START_TEST(test_add4) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int check = TEST_ARITHMETIC_NEG_INF;

  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(code, check);
}
END_TEST

START_TEST(test_add5) {
  s21_decimal val1 = {{291, 1110, 1929, 0x800D0000}};
  s21_decimal val2 = {{(int)2327839011, (int)3886551757, 302, 0x00100000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
  ck_assert_int_eq(res.bits[0], 1967419285);
  ck_assert_int_eq(res.bits[1], 409525538);
  ck_assert_int_eq(res.bits[2], 1928697);
  ck_assert_uint_eq(res.bits[3], (int)2148532224);
}
END_TEST

START_TEST(test_pos_inf_add) {
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {5, 0, 0};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);

  int code = s21_add(d1, d2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_POS_INF);
}
END_TEST

START_TEST(test_div_correct_4) {
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {43567, 0, 0};
  size_t arr1[HELPER_ARR_SIZE] = {1, 1, 1};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  make_negative(&d2);

  int code = s21_div(d1, d2, &result);
  ck_assert_int_eq(code, 0);

  char *res = decimal_to_string(&result);
  ck_assert_str_eq(res, "-0.0000000000000236177180188391");
  free(res);
}
END_TEST

START_TEST(test_div_fail_0) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_div(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_div_fail_1) {
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, TEST_ARITHMETIC_DIV_BY_ZERO);
}
END_TEST

START_TEST(test_div_correct_1) {
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF, 0x0}};

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_div_correct_2) {
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF, 0x00000000}};

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_div_correct_3) {
  s21_decimal decimal1 = {{10, 0, 0, 0}};
  s21_decimal decimal2 = {{5, 0, 0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{2, 0, 0, 0x80000000}};
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_decimal_subtraction) {
  s21_decimal d1, d2, result;
  s21_from_int_to_decimal(-111111, &d1);
  s21_from_int_to_decimal(-222222, &d2);
  char *pow_d1 = get_power(&d1);
  char *pow_d2 = get_power(&d2);
  *pow_d1 = 3;
  *pow_d2 = 3;

  int code = s21_sub(d1, d2, &result);
  ck_assert_int_eq(code, 0);
  char *res = decimal_to_string(&result);
  ck_assert_str_eq(res, "111.111");
  free(res);
}
END_TEST

START_TEST(test_sub_fail_0) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_sub(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_1) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_2) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_fail_4) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_sub2) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int check = TEST_ARITHMETIC_POS_INF;

  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, check);
}
END_TEST

START_TEST(test_sub3) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, TEST_ARITHMETIC_POS_INF);
}
END_TEST

START_TEST(test_sub4) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_sub5) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int check = TEST_ARITHMETIC_NEG_INF;

  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_eq(code, check);
}
END_TEST

START_TEST(test_decimal_multiplication) {
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {62959, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {5, 0, 0};
  assign_decimal(&d1, arr, 12);
  assign_decimal(&d2, arr1, 12);
  make_negative(&d2);

  int code = s21_mul(d1, d2, &result);
  ck_assert_int_eq(code, 0);
  char *res = decimal_to_string(&result);
  ck_assert_str_eq(res, "-396140.81257132168794624523");
  free(res);
}
END_TEST

START_TEST(test_mul_fail_0) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_mul(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, TEST_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_mul_fail_1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_NEG_INF);
}
END_TEST

START_TEST(test_mul_fail_2) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_POS_INF);
}
END_TEST

START_TEST(test_mul_fail_small_value) {
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x001C0000}};
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x001C0000}};
  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);

  s21_decimal expected = {{0x0, 0x0, 0x0, 0x001C0000}};
  ck_assert_int_eq(s21_is_equal(result, expected), 1);
}
END_TEST

START_TEST(test_mul_correct_1) {
  s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal decimal2 = {{0x3, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_decimal check = {{0x6, 0x0, 0x0, 0x0}};
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_mul_correct_2) {
  s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x80000000}};
  s21_decimal decimal2 = {{0x3, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0x6, 0x0, 0x0, 0x0}};

  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_mul_correct_3) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_mul_correct_4) {
  s21_decimal decimal1 = {{0x2, 0x0, 0x0, 0x10000}};
  s21_decimal decimal2 = {{0x3, 0x0, 0x0, 0x20000}};
  s21_decimal result;
  s21_decimal check = {{0x6, 0x0, 0x0, 0x30000}};

  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_mul_correct_5) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(test_mul_correct_6) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(rand_arithmetic) { ck_assert_int_eq(arithmetics_test(), 0); }
END_TEST

Suite *add_suite(void) {
  Suite *s = suite_create("add_suite");

  TCase *tc_fail = tcase_create("add_fail");
  tcase_add_test(tc_fail, test_add_fail_0);
  tcase_add_test(tc_fail, test_add_fail_1);
  tcase_add_test(tc_fail, test_add_fail_2);
  tcase_add_test(tc_fail, test_add_fail_3);
  tcase_add_test(tc_fail, test_add_fail_4);
  suite_add_tcase(s, tc_fail);

  TCase *tc_correct = tcase_create("add_correct");
  tcase_add_test(tc_correct, test_add0);
  tcase_add_test(tc_correct, test_add1);
  tcase_add_test(tc_correct, test_add2);
  tcase_add_test(tc_correct, test_add3);
  tcase_add_test(tc_correct, test_add4);
  tcase_add_test(tc_correct, test_add5);
  tcase_add_test(tc_correct, test_add6);
  tcase_add_test(tc_correct, test_pos_inf_add);
  suite_add_tcase(s, tc_correct);

  return s;
}

Suite *div_suite(void) {
  Suite *s = suite_create("div_suite");

  TCase *tc_fail = tcase_create("div_fail");
  tcase_add_test(tc_fail, test_div_fail_0);
  tcase_add_test(tc_fail, test_div_fail_1);
  suite_add_tcase(s, tc_fail);

  TCase *tc_correct = tcase_create("div_correct");
  tcase_add_test(tc_correct, test_div_correct_1);
  tcase_add_test(tc_correct, test_div_correct_2);
  tcase_add_test(tc_correct, test_div_correct_3);
  tcase_add_test(tc_correct, test_div_correct_4);
  suite_add_tcase(s, tc_correct);

  return s;
}

Suite *sub_suite(void) {
  Suite *s = suite_create("sub_suite");

  TCase *tc_fail = tcase_create("sub_fail");
  tcase_add_test(tc_fail, test_sub_fail_0);
  tcase_add_test(tc_fail, test_sub_fail_1);
  tcase_add_test(tc_fail, test_sub_fail_2);
  tcase_add_test(tc_fail, test_sub_fail_3);
  tcase_add_test(tc_fail, test_sub_fail_4);
  suite_add_tcase(s, tc_fail);

  TCase *tc_correct = tcase_create("sub_correct");
  tcase_add_test(tc_correct, test_sub1);
  tcase_add_test(tc_correct, test_sub2);
  tcase_add_test(tc_correct, test_sub3);
  tcase_add_test(tc_correct, test_sub4);
  tcase_add_test(tc_correct, test_sub5);
  tcase_add_test(tc_correct, test_decimal_subtraction);
  suite_add_tcase(s, tc_correct);

  return s;
}

Suite *rand_arithmetics_suite() {
  Suite *s = suite_create("rand_arithmetic_suite");
  TCase *tc = tcase_create("rand_arithmetic");
  tcase_add_test(tc, rand_arithmetic);
  suite_add_tcase(s, tc);
  return s;
}

Suite *mul_suite(void) {
  Suite *s = suite_create("mul_suite");

  TCase *tc_fail = tcase_create("mul_fail");
  tcase_add_test(tc_fail, test_mul_fail_0);
  tcase_add_test(tc_fail, test_mul_fail_1);
  tcase_add_test(tc_fail, test_mul_fail_2);
  tcase_add_test(tc_fail, test_mul_fail_small_value);
  suite_add_tcase(s, tc_fail);

  TCase *tc_correct = tcase_create("mul_correct");
  tcase_add_test(tc_correct, test_mul_correct_1);
  tcase_add_test(tc_correct, test_mul_correct_2);
  tcase_add_test(tc_correct, test_mul_correct_3);
  tcase_add_test(tc_correct, test_mul_correct_4);
  tcase_add_test(tc_correct, test_mul_correct_5);
  tcase_add_test(tc_correct, test_mul_correct_6);
  tcase_add_test(tc_correct, test_decimal_multiplication);
  tcase_add_test(tc_correct, test_mul_fail_small_value);
  suite_add_tcase(s, tc_correct);

  return s;
}
