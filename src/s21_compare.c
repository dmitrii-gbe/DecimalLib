#include "s21_decimal.h"

int get_sign(const s21_decimal *num) {
  return (num->bits[3] & 0x80000000) >> 31;
}

int is_zero_decimal(s21_decimal num) {
  return (num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0);
}

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  if (is_zero_decimal(num1) && is_zero_decimal(num2)) {
    make_non_negative_zero(&num1);
    make_non_negative_zero(&num2);
  }
  int sign_num1 = is_negative(&num1);
  int sign_num2 = is_negative(&num2);
  int comparison_result = compare_decimal(num1, num2);
  if (sign_num1 != sign_num2) {
    comparison_result = sign_num1;
  } else if (sign_num1 == 0) {
    comparison_result = comparison_result == -1;
  } else {
    comparison_result = comparison_result == 1;
  }
  return comparison_result;
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return !s21_is_less(num1, num2) && !s21_is_equal(num1, num2);
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_less(num1, num2) && !s21_is_less(num2, num1);
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
