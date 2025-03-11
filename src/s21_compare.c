#include "s21_decimal.h"

int get_sign(const s21_decimal *num) {
  return (num->bits[3] & 0x80000000) >> 31;
}

int is_zero_decimal(s21_decimal num) {
  return (num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0);
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = 0;
  int sign_num1 = is_negative(&num1);
  int sign_num2 = is_negative(&num2);

  if (sign_num1 != sign_num2) {
    result = sign_num1;
  } else {
    int comparison_result = compare_decimal(num1, num2);
    if (comparison_result == -1) {
      result = (sign_num1) ? 0 : 1;
    } else if (comparison_result == 0) {
      result = 0;
    } else {
      result = (sign_num1) ? 1 : 0;
    }
  }

  return result;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return !s21_is_less(num1, num2) && !s21_is_equal(num1, num2);
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int result = 1;
  int sign_num1 = get_sign(&num1);
  int sign_num2 = get_sign(&num2);

  if (is_zero_decimal(num1) && is_zero_decimal(num2)) {
    result = 1;
  } else if (sign_num1 != sign_num2) {
    result = 0;
  } else {
    int scale1 = get_scale(&num1);
    int scale2 = get_scale(&num2);

    if (scale1 != scale2) {
      result = 0;
    } else {
      for (int i = 0; i < 4; i++) {
        if (num1.bits[i] != num2.bits[i]) {
          result = 0;
        }
      }
    }
  }

  return result;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return s21_is_less(num1, num2) || s21_is_equal(num1, num2);
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_less(num1, num2);
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}
