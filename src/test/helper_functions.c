
#include "s21_test_main.h"

void test_decimal_subtraction() {
  printf("\nDecimal subtraction test: \n");
  s21_decimal d1, d2, result;
  s21_from_int_to_decimal(-111111, &d1);
  s21_from_int_to_decimal(-222222, &d2);
  char *pow_d1 = get_power(&d1);
  char *pow_d2 = get_power(&d2);
  *pow_d1 = 3;
  *pow_d2 = 3;
  assert(0 == s21_sub(d1, d2, &result));
  char *res = decimal_to_string(&result);
  printf("%s\n", res);
}

void test_decimal_multiplication() {
  printf("\nDecimal multiplication test:\n");
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {62959, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {5, 0, 0};
  assign_decimal(&d1, arr, 12);
  assign_decimal(&d2, arr1, 12);
  make_negative(&d2);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  char *res_string = NULL;
  assert(s21_mul(d1, d2, &result) == 0);
  res_string = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_string);
  free(str1);
  free(str2);
  free(res_string);
}

int test_pos_inf_add() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {5, 0, 0};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_add(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_add(d1, d2, &result);
}

int test_pos_inf_sub() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {5, 0, 0};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  make_negative(&d2);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_sub(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_sub(d1, d2, &result);
}

int test_div_by_zero() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {0, 0, 0};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  make_negative(&d2);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_div(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_div(d1, d2, &result);
}

int test_pos_inf_mul() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_mul(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_mul(d1, d2, &result);
}

int test_neg_inf_mul() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  make_negative(&d1);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_mul(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_mul(d1, d2, &result);
}

int test_pos_inf_div() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {1, 0, 0};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_div(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_div(d1, d2, &result);
}

int test_neg_inf_div() {
  printf("\n%s\n", __func__);
  s21_decimal d1, d2, result;
  size_t arr[HELPER_ARR_SIZE] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
  size_t arr1[HELPER_ARR_SIZE] = {1, 0, 0};
  assign_decimal(&d1, arr, 0);
  assign_decimal(&d2, arr1, 1);
  make_negative(&d1);
  char *str1 = decimal_to_string(&d1);
  char *str2 = decimal_to_string(&d2);
  s21_div(d1, d2, &result);
  char *res_str = decimal_to_string(&result);
  printf("%s %s %s\n", str1, str2, res_str);
  free(str1);
  free(str2);
  free(res_str);
  return s21_div(d1, d2, &result);
}

void CalculateEulerConstant() {
  printf("\n%s\n", __func__);
  uint32_t i = 1000000000;
  s21_decimal d;
  s21_decimal d1;
  s21_from_int_to_decimal(1, &d1);
  s21_from_int_to_decimal(i, &d);
  s21_pow(d, 3, &d);
  s21_div(d1, d, &d);
  s21_add(d1, d, &d);
  s21_decimal res;
  s21_pow(d, i, &res);
  s21_pow(res, i, &res);
  s21_pow(res, i, &res);
}

void float_to_bits(char *const arr, float f) {
  float_uint_t fu;
  fu.f = f;
  for (int i = 31; i >= 0; --i) {
    arr[i] = fu.u & 1u;
    fu.u = fu.u >> 1;
  }
}

int decimal_to_float_test(float src) {
  s21_decimal d;
  float dst;
  assert(s21_from_float_to_decimal_opt_rounding(src, &d, 0) == 0);
  s21_from_decimal_to_float(d, &dst);
  return src != dst;
}

int test_decimal_to_float_external() {
  int without_fractions_errors = 0;
  int with_fraction_errors = 0;
  float arr_no_fr[] = {-79228.2e21,
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
                       -1233143.0f};
  float arr_with_fraction[] = {62874587235642873463.70e-5f,
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
                               14.65e-2f};

  for (size_t i = 0; i < sizeof(arr_no_fr) / sizeof(float); ++i) {
    without_fractions_errors =
        without_fractions_errors + decimal_to_float_test(arr_no_fr[i]);
  }
  for (size_t i = 0; i < sizeof(arr_with_fraction) / sizeof(float); ++i) {
    with_fraction_errors =
        with_fraction_errors + decimal_to_float_test(arr_with_fraction[i]);
  }
  return without_fractions_errors + without_fractions_errors;
}

void float_internal_structure() {
  printf("\n%s\n", __func__);
  float_uint_t a;
  a.u = 0x7F7FFFFF;
  for (int i = 0; i < 16; ++i) {
    printf("\n%.5f", a.f);
    --a.u;
  }
}