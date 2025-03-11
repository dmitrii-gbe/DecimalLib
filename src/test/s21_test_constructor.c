#include "s21_test_main.h"

START_TEST(test_dec_to_float_1) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147680256;
  src.bits[0] = 18122;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_2) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147483648;
  src.bits[0] = 1812;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_3) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0XFFFFFF;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_4) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147745792;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_5) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 4294967295;
  src.bits[0] = c;
  src.bits[1] = c;
  src.bits[2] = 0;
  src.bits[3] = 0;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
}
END_TEST

START_TEST(test_dec_to_float_6) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 2147483648;
  dec.bits[0] = 1812;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = c;

  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_7) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0XFFFFFF;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;

  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_8) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 2147745792;
  dec.bits[0] = 23450987;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = c;

  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_9) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  long int c = 4294967295;
  dec.bits[0] = c;
  dec.bits[1] = c;
  dec.bits[2] = 0;
  dec.bits[3] = 0;

  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_float_10) {
  s21_decimal src1;
  float src2;
  float *srcp = &src2;
  src1.bits[0] = 0b00000000000000000110001101111001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;

  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 2546.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(test_dec_to_float_11) {
  s21_decimal src1;
  float src2;
  float *srcp = &src2;
  src1.bits[0] = 0b00000000000000001011010101110101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001010000000000000000;

  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -0.46453);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(test_dec_to_float_12) {
  s21_decimal src1;
  float src2;
  float *srcp = &src2;
  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;

  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 3.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(test_dec_to_float_13) {
  s21_decimal src1;
  float src2;
  float *srcp = &src2;
  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;

  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 4.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(test_dec_to_float_14) {
  s21_decimal src1;
  float src2;
  float *srcp = &src2;
  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;

  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -4.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(test_dec_to_float_15) {
  s21_decimal src1;
  float src2;
  float *srcp = &src2;
  src1.bits[0] = 0b00000000000010000110000110010001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001010000000000000000;

  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -5.49265);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(test_dec_to_int_1) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = INT_MAX;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;

  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2147483647);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_int_2) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 133141;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;

  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 133141);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_int_3) {
  s21_decimal src;
  int result = 0, number = 0;
  src.bits[0] = 123451234;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0b10000000000000000000000000000000;

  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -123451234);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_int_4) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 2147483648;
  src.bits[0] = 18;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;

  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -18);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_dec_to_int_5) {
  s21_decimal src;
  int result = 0, number = 0;
  long int c = 4294967295;
  src.bits[0] = c;
  src.bits[1] = c;
  src.bits[2] = 0;
  src.bits[3] = 0;

  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_float_to_dec_1) {
  s21_decimal val;
  float fl1 = 3;
  float fl2 = 127.1234;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_float_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_float_eq_tol(fl2, fl2_res, 1e-28);
}
END_TEST

START_TEST(test_float_to_dec_2) {
  s21_decimal val;
  float fl1 = -128.023;
  float fl2 = 12345.37643764;
  float fl1_res = 0;
  float fl2_res = 0;

  s21_from_float_to_decimal(fl1, &val);
  s21_from_decimal_to_float(val, &fl1_res);
  ck_assert_float_eq_tol(fl1, fl1_res, 1e-28);

  s21_from_float_to_decimal(fl2, &val);
  s21_from_decimal_to_float(val, &fl2_res);
  ck_assert_float_eq_tol(fl2, fl2_res, 1e-2);
}
END_TEST

START_TEST(test_float_to_dec_3) {
  s21_decimal val;
  float a = 1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_float_to_dec_4) {
  s21_decimal val;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_float_to_dec_5) {
  s21_decimal val;
  float a = 1e-30;
  s21_from_float_to_decimal(a, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_float_to_dec_6) {
  s21_decimal dec;
  float tmp = 0;
  float tmp1 = 0.03;
  s21_from_float_to_decimal(tmp1, &dec);
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, tmp1, 1e-06);
}
END_TEST

START_TEST(test_float_to_dec_7) {
  s21_decimal dec;
  s21_from_float_to_decimal(-128.023, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -128.023, 1e-06);
}
END_TEST

START_TEST(test_float_to_dec_8) {
  s21_decimal dec;
  s21_from_float_to_decimal(1.02E+08, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, 1.02E+08, 1e-06);
}
END_TEST

START_TEST(test_float_to_dec_9) {
  s21_decimal dec;
  s21_from_float_to_decimal(-333.2222, &dec);
  float tmp = 0;
  s21_from_decimal_to_float(dec, &tmp);
  ck_assert_float_eq_tol(tmp, -333.2222, 1e-2);
}
END_TEST

START_TEST(test_float_to_dec_10) {
  s21_decimal dec;
  float a = 1.0 / 0.0;
  int ret = s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_float_to_dec_11) {
  s21_decimal dec;
  float a = -1.0 / 0.0;
  s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(test_int_to_dec_1) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_int_to_dec_2) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(123, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 123);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_int_to_dec_3) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(-456, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], 456);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((uint32_t)val.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_int_to_dec_4) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MAX, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(val.bits[0], INT_MAX);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(test_int_to_dec_5) {
  s21_decimal val;
  int result = s21_from_int_to_decimal(INT_MIN, &val);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq((uint32_t)val.bits[0], 0x80000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((uint32_t)val.bits[3], 0x80000000);
}
END_TEST

START_TEST(test_from_decimal_to_int) {
  float arr[] = {-79228.2e21,
                 -0.0f,
                 2346457.0f,
                 42315278.0f,
                 42318.0f,
                 5278.0f,
                 4231.0f,
                 43158.0f,
                 2346457738291836451735263476.0f,
                 4234567890980765432.0f,
                 615235176345123187361982367.0f,
                 61347895637.0f,
                 26345283746867.0f,
                 6152351763453874568.0f,
                 6157238456834751982367.0f,
                 -273468237423187361982367.0f,
                 -1233143.0f,
                 62874587235642873463.70e-5f,
                 1.0e-27f,
                 123314323434.0e-5f,
                 123314323434.0e-6f,
                 123314323434.0e-7f,
                 123314323434.0e-8f,
                 123314323434.0e-9f,
                 123314323434.0e-10f,
                 123314323434.0e-11f,
                 11234.65e-2f,
                 6463.70e-5f,
                 1.0e-21f,
                 -2.4e-21,
                 134.0e-5f,
                 14.0e-6f,
                 1234.0e-7f,
                 1323434.0e-8f,
                 134.0e-9f,
                 134.0e-10f,
                 134.0e-11f,
                 -6152351763451231243781235682e-19f,
                 1152351763451231243781235682e-18f,
                 -1152351763451231243781235682e-17f,
                 1152351763451231243781235682e-20f,
                 -1152351763451231243781235682e-21f,
                 1152351763451231243781235682e-22f,
                 -1152351763451231243781235682e-23f,
                 1152351763451231243781235682e-24f,
                 -14.65e-2f};
  int error[] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};

  for (size_t i = 0; i < sizeof(arr) / sizeof(float); ++i) {
    int dst = 0;
    s21_decimal d;
    s21_from_float_to_decimal_opt_rounding(arr[i], &d, 0);
    ck_assert_int_eq(s21_from_decimal_to_int(d, &dst), error[i]);
    if (error[i] == 0) {
      ck_assert_int_eq(dst, (int)arr[i]);
    }
  }
}
END_TEST

START_TEST(float_to_decimal_and_back_test) {
  ck_assert_int_eq(test_decimal_to_float_external(), 0);
}
END_TEST

Suite *decimal_to_float_suite(void) {
  Suite *s = suite_create("Decimal to Float Tests");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_dec_to_float_1);
  tcase_add_test(tc, test_dec_to_float_2);
  tcase_add_test(tc, test_dec_to_float_3);
  tcase_add_test(tc, test_dec_to_float_4);
  tcase_add_test(tc, test_dec_to_float_5);
  tcase_add_test(tc, test_dec_to_float_6);
  tcase_add_test(tc, test_dec_to_float_7);
  tcase_add_test(tc, test_dec_to_float_8);
  tcase_add_test(tc, test_dec_to_float_9);
  tcase_add_test(tc, test_dec_to_float_10);
  tcase_add_test(tc, test_dec_to_float_11);
  tcase_add_test(tc, test_dec_to_float_12);
  tcase_add_test(tc, test_dec_to_float_13);
  tcase_add_test(tc, test_dec_to_float_14);
  tcase_add_test(tc, test_dec_to_float_15);
  tcase_add_test(tc, float_to_decimal_and_back_test);

  suite_add_tcase(s, tc);
  return s;
}

Suite *decimal_to_int_suite(void) {
  Suite *s = suite_create("Decimal to Int Tests");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_dec_to_int_1);
  tcase_add_test(tc, test_dec_to_int_2);
  tcase_add_test(tc, test_dec_to_int_3);
  tcase_add_test(tc, test_dec_to_int_4);
  tcase_add_test(tc, test_dec_to_int_5);
  tcase_add_test(tc, test_from_decimal_to_int);

  suite_add_tcase(s, tc);
  return s;
}

Suite *float_to_decimal_suite(void) {
  Suite *s = suite_create("Float to Decimal Tests");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_float_to_dec_1);
  tcase_add_test(tc, test_float_to_dec_2);
  tcase_add_test(tc, test_float_to_dec_3);
  tcase_add_test(tc, test_float_to_dec_4);
  tcase_add_test(tc, test_float_to_dec_5);
  tcase_add_test(tc, test_float_to_dec_6);
  tcase_add_test(tc, test_float_to_dec_7);
  tcase_add_test(tc, test_float_to_dec_8);
  tcase_add_test(tc, test_float_to_dec_9);
  tcase_add_test(tc, test_float_to_dec_10);
  tcase_add_test(tc, test_float_to_dec_11);

  suite_add_tcase(s, tc);
  return s;
}

Suite *int_to_decimal_suite(void) {
  Suite *s = suite_create("Int to Decimal Tests");
  TCase *tc = tcase_create("Core");
  tcase_add_test(tc, test_int_to_dec_1);
  tcase_add_test(tc, test_int_to_dec_2);
  tcase_add_test(tc, test_int_to_dec_3);
  tcase_add_test(tc, test_int_to_dec_4);
  tcase_add_test(tc, test_int_to_dec_5);

  suite_add_tcase(s, tc);
  return s;
}
