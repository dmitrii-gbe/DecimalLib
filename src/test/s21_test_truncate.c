#include "s21_test_main.h"

START_TEST(s21_truncate_test1) {
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00030000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2645699854);
  ck_assert_int_eq(res.bits[1], 1271310319);
  ck_assert_int_eq(res.bits[2], 4294967);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test2) {
  s21_decimal val1 = {
      {(int)2576980378, (int)2576980377, 429496729, 0x80020000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)2645699854);
  ck_assert_int_eq(res.bits[1], 1271310319);
  ck_assert_int_eq(res.bits[2], 4294967);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);
}
END_TEST

START_TEST(s21_truncate_test3) {
  s21_decimal val1 = {{11, 0, 0, 0x00010000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test4) {
  s21_decimal val1 = {{(int)4092717806, 360108, 0, 0x00090000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 1546656);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test5) {
  s21_decimal val1 = {{0, 0, 0, 0x80030000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);
}
END_TEST

START_TEST(s21_truncate_test6) {
  s21_decimal val1 = {{1579388472, 2069605721, 0, 0x80090000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 298954296);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);
}
END_TEST

START_TEST(s21_truncate_test7) {
  s21_decimal val1 = {{2033164565, 2043353280, 66926059, 0x80090000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], (int)3000119458);
  ck_assert_int_eq(res.bits[1], 287445236);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], (int)2147483648);
}
END_TEST

START_TEST(s21_truncate_test8) {
  s21_decimal val1 = {{0, 0, 0, 0x00000000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test9) {
  s21_decimal val1 = {{589056, 0, 0, 0x00060000}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val1, &res));
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_uint_eq(res.bits[3], 0);
}
END_TEST

START_TEST(s21_truncate_test_status_1) {
  s21_decimal val1 = {{589056, 0, 0, 0x001C0000}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_truncate(val1, &res));
}
END_TEST

Suite *truncate_suite(void) {
  Suite *s = suite_create("truncate");
  TCase *tc = tcase_create("truncate");

  tcase_add_test(tc, s21_truncate_test1);
  tcase_add_test(tc, s21_truncate_test2);
  tcase_add_test(tc, s21_truncate_test3);
  tcase_add_test(tc, s21_truncate_test4);
  tcase_add_test(tc, s21_truncate_test5);
  tcase_add_test(tc, s21_truncate_test6);
  tcase_add_test(tc, s21_truncate_test7);
  tcase_add_test(tc, s21_truncate_test8);
  tcase_add_test(tc, s21_truncate_test9);
  tcase_add_test(tc, s21_truncate_test_status_1);

  suite_add_tcase(s, tc);
  return s;
}
