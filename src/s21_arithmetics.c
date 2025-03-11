#include "s21_decimal.h"

char max(const char lhs, const char rhs) { return lhs > rhs ? lhs : rhs; }

int min(size_t lhs, size_t rhs) { return lhs < rhs ? lhs : rhs; }

void s21_pow(s21_decimal d, size_t pow, s21_decimal *const result) {
  s21_from_int_to_decimal(1, result);
  while (pow != 0) {
    if (pow % 2 == 0) {
      s21_mul(d, d, &d);
      pow /= 2;
    } else {
      s21_mul(d, *result, result);
      --pow;
    }
  }
}

char compare_helper_arrays(const size_t *const arr1, const size_t *const arr2) {
  int elder_digit_index1 = get_max_set_bit(arr1, HELPER_ARR_SIZE);
  int elder_digit_index2 = get_max_set_bit(arr2, HELPER_ARR_SIZE);
  int idx = max(elder_digit_index1, elder_digit_index2);
  idx = max(idx, 0);
  while (arr1[idx] == arr2[idx] && idx > 0) {
    --idx;
  }
  return arr1[idx] > arr2[idx] ? 1 : (arr1[idx] == arr2[idx] ? 0 : -1);
}

char compare_decimal(s21_decimal value_1, s21_decimal value_2) {
  int power1 = *get_power(&value_1);
  int power2 = *get_power(&value_2);
  size_t arr1[HELPER_ARR_SIZE], arr2[HELPER_ARR_SIZE];
  initialize_bytes(arr1, sizeof(size_t) * HELPER_ARR_SIZE);
  initialize_bytes(arr2, sizeof(size_t) * HELPER_ARR_SIZE);
  copy_decimal_to_helper(&value_1, arr1);
  copy_decimal_to_helper(&value_2, arr2);
  if (power2 > power1) {
    equalize_powers(arr1, &power1, power2);
  } else if (power1 > power2) {
    equalize_powers(arr2, &power2, power1);
  }
  return compare_helper_arrays(arr1, arr2);
}

void make_non_negative(s21_decimal *const d) {
  unset_nth_bit(d, SIGN_BIT_INDEX);
}

void make_negative(s21_decimal *const d) { set_nth_bit(d, SIGN_BIT_INDEX); }

char is_negative(const s21_decimal *const d) {
  return get_nth_bit(d, SIGN_BIT_INDEX);
}

void invert_sign(s21_decimal *const d) { invert_nth_bit(d, SIGN_BIT_INDEX); }

int add_arrays(size_t *const arr1, size_t *const arr2, size_t *const result,
               int size) {
  size_t *tmp = calloc(size, sizeof(size_t));
  copy_helper_array(arr1, tmp, size);
  initialize_bytes(result, size * sizeof(size_t));
  for (int i = 0; i < size; ++i) {
    result[i] += tmp[i] + arr2[i];
    if (i + 1 < size) {
      result[i + 1] += result[i] / BASE;
    }
    result[i] = result[i] % BASE;
  }
  free(tmp);
  return 0;
}

char all_of(const size_t *const arr, const size_t size, const size_t val) {
  char res = 1;
  for (size_t i = 0; i < size && res; ++i) {
    res = arr[i] == val;
  }
  return res;
}

char is_zero(const int *const arr, const size_t size) {
  char res = 1;
  for (size_t i = 0; i < size && res; ++i) {
    res = arr[i] == 0;
  }
  return res;
}

char approaches_limit(const size_t *const digits, const int n) {
  return all_of(digits, n, UINT32_MAX);
}

int divide_arrays(size_t *const dividend, size_t *divider, size_t *result,
                  const int size) {
  size_t multiplyer[DIV_HELP_ARR_SIZE], divd[DIV_HELP_ARR_SIZE],
      divr[DIV_HELP_ARR_SIZE];
  initialize_bytes(multiplyer, sizeof(size_t) * size);
  initialize_bytes(divd, sizeof(size_t) * size);
  initialize_bytes(divr, sizeof(size_t) * size);
  initialize_bytes(result, HELPER_ARR_SIZE * sizeof(size_t));
  int elder_set_bit = DECIMAL_ARR_INT_COUNT - 2;
  int found = 0;
  for (int i = DECIMAL_ARR_INT_COUNT - 2; !found && elder_set_bit >= 0; --i) {
    found = divider[i] != 0;
    elder_set_bit = i;
  }
  for (int i = elder_set_bit, j = FRACTION_DIGITS - 1; i >= 0; --i, --j) {
    divr[j] = divider[i];
  }
  for (int i = 0; i < DECIMAL_ARR_INT_COUNT - 1; ++i) {
    divd[FRACTION_DIGITS - 1 - elder_set_bit + i] = dividend[i];
  }

  size_t two[DIV_HELP_ARR_SIZE];
  initialize_bytes(two, sizeof(size_t) * DIV_HELP_ARR_SIZE);
  two[FRACTION_DIGITS] = 2;
  subtract_arrays(two, divr, multiplyer, DIV_HELP_ARR_SIZE);
  while (!approaches_limit(divr + 1, 2)) {
    multiply_arrays_div(divd, multiplyer, divd);
    multiply_arrays_div(divr, multiplyer, divr);
    subtract_arrays(two, divr, multiplyer, DIV_HELP_ARR_SIZE);
  }
  int power = 0;
  if (!all_of(divd, DIV_HELP_ARR_SIZE, 0)) {
    while (divd[FRACTION_DIGITS + DECIMAL_ARR_INT_COUNT - 1] == 0LLU) {
      multiply_array(divd, IMPLICIT_BASE, DIV_HELP_ARR_SIZE);
      ++power;
    }
  }
  copy_helper_array(divd + FRACTION_DIGITS, result, HELPER_ARR_SIZE);
  return power;
}

void multiply_arrays_div(size_t *const arr1, size_t *const arr2,
                         size_t *const result) {
  size_t tmp[DIV_HELP_ARR_SIZE];
  copy_helper_array(arr1, tmp, DIV_HELP_ARR_SIZE);
  initialize_bytes(result, DIV_HELP_ARR_SIZE * sizeof(size_t));
  for (int i = 0; i < FRACTION_DIGITS + DECIMAL_ARR_INT_COUNT - 1; ++i) {
    for (int j = 0; j < FRACTION_DIGITS + DECIMAL_ARR_INT_COUNT - 1; ++j) {
      int idx = i + j - FRACTION_DIGITS;
      if (idx >= 0) {
        result[idx] += tmp[i] * arr2[j];
        result[idx + 1] += result[idx] / BASE;
        result[idx] = result[idx] % BASE;
      }
    }
  }
}

int multiply_arrays(size_t *const arr1, size_t *const arr2,
                    size_t *const result, int size) {
  size_t *tmp = calloc(size, sizeof(size_t));
  copy_helper_array(arr1, tmp, size);
  initialize_bytes(result, size * sizeof(size_t));
  for (int i = 0; i < DECIMAL_ARR_INT_COUNT - 1; ++i) {
    for (int j = 0; j < DECIMAL_ARR_INT_COUNT - 1; ++j) {
      result[i + j] += tmp[i] * arr2[j];
      result[i + j + 1] += result[i + j] / BASE;
      result[i + j] = result[i + j] % BASE;
    }
  }
  free(tmp);
  return 0;
}

char get_max_set_bit(const size_t *const arr, int size) {
  char res = -1;
  for (int i = 0; i < size; ++i) {
    if (arr[i] > 0lu) {
      res = i;
    }
  }
  return res;
}

void rebalance_array_for_subtraction(size_t *const arr, int size) {
  for (int i = get_max_set_bit(arr, size); i > 0; --i) {
    --arr[i];
    arr[i - 1] += BASE;
  }
}

int subtract_arrays(size_t *const arr1, size_t *const arr2,
                    size_t *const result, int size) {
  size_t *tmp = calloc(size, sizeof(size_t));
  copy_helper_array(arr1, tmp, size);
  rebalance_array_for_subtraction(tmp, size);
  initialize_bytes(result, size * sizeof(size_t));
  for (int i = 0; i < size; ++i) {
    size_t diff = tmp[i] - arr2[i];
    result[i] = diff % BASE;
    if (i + 1 < size) {
      tmp[i + 1] += diff / BASE;
    }
  }
  free(tmp);
  return 0;
}

void copy_helper_array(const size_t *const from, size_t *const to,
                       const size_t n) {
  initialize_bytes(to, sizeof(size_t) * n);
  for (size_t i = 0; i < n; ++i) {
    to[i] = from[i];
  }
}

char are_equal_helper_arrays(const size_t *const arr1,
                             const size_t *const arr2) {
  char result = 1;
  for (int i = 0; i < HELPER_ARR_SIZE && result; ++i) {
    if (arr1[i] != arr2[i]) {
      result = 0;
    }
  }
  return result;
}

void divide_array(size_t *const arr, const size_t divider) {
  for (int i = HELPER_ARR_SIZE - 1; i >= 0; --i) {
    if (i - 1 >= 0) {
      arr[i - 1] += (arr[i] % divider) * BASE;
    }
    arr[i] /= divider;
  }
}

void multiply_array(size_t *const arr, const size_t multiplyer, int size) {
  size_t in_mind = 0;
  for (int i = 0; i < size; ++i) {
    arr[i] = arr[i] * multiplyer + in_mind;
    in_mind = arr[i] / BASE;
    arr[i] = arr[i] % BASE;
  }
}

char *get_power(const s21_decimal *const d) {
  return ((char *)(d->bits + DECIMAL_ARR_INT_COUNT - 1) + POWER_BYTE_INDEX);
}

void copy_decimal(const s21_decimal *const from, s21_decimal *const to) {
  for (int i = 0; i < DECIMAL_ARR_INT_COUNT; ++i) {
    to->bits[i] = from->bits[i];
  }
}

void swap_decimal(s21_decimal *const d1, s21_decimal *const d2) {
  s21_decimal tmp;
  copy_decimal(d1, &tmp);
  copy_decimal(d2, d1);
  copy_decimal(&tmp, d2);
}

void swap_power(int *const power1, int *const power2) {
  int tmp = *power1;
  *power1 = *power2;
  *power2 = tmp;
}

void copy_decimal_to_helper(const s21_decimal *const from, size_t *const to) {
  for (int i = 0; i < DECIMAL_ARR_INT_COUNT - 1; ++i) {
    to[i] = *(uint32_t *)(from->bits + i);
  }
}

size_t Pow(size_t base, int power) {
  size_t result;
  if (power == 0) {
    result = 1;
  } else if (power % 2 == 0) {
    size_t tmp = Pow(base, power / 2);
    result = tmp * tmp;
  } else {
    result = base * Pow(base, power - 1);
  }
  return result;
}

void equalize_powers(size_t *const arr, int *const low, const int hight) {
  while (*low != hight) {
    size_t multiplyer = min(1000000000LLU, Pow(IMPLICIT_BASE, hight - *low));
    multiply_array(arr, multiplyer, HELPER_ARR_SIZE);
    (*low) += min(hight - *low, 9);
  }
}

char in_range(const size_t *const arr) {
  char result = 1;
  for (int i = DECIMAL_ARR_INT_COUNT - 1; i < HELPER_ARR_SIZE && result; ++i) {
    if (arr[i] != 0) {
      result = 0;
    }
  }
  return result;
}

void assign_decimal(s21_decimal *const d, const size_t *const arr,
                    const char power) {
  for (int i = 0; i < DECIMAL_ARR_INT_COUNT - 1; ++i) {
    d->bits[i] = arr[i];
  }
  d->bits[DECIMAL_ARR_INT_COUNT - 1] = 0;
  char *ptr = get_power(d);
  *ptr = power;
}

char is_dividable(size_t *arr, int number) {
  size_t tmp[HELPER_ARR_SIZE];
  copy_helper_array(arr, tmp, HELPER_ARR_SIZE);
  divide_array(tmp, number);
  multiply_array(tmp, number, HELPER_ARR_SIZE);
  return are_equal_helper_arrays(tmp, arr);
}

void free_extra_digits(size_t *const arr, int *const power) {
  char last_digit = get_last_digit_of_helper_array_number(arr), pre_last_digit;
  size_t to_add[HELPER_ARR_SIZE] = {1, 0, 0, 0, 0};
  while ((!in_range(arr) || !valid_power(*power)) && *power >= 0) {
    divide_array(arr, IMPLICIT_BASE);
    pre_last_digit = get_last_digit_of_helper_array_number(arr);
    --(*power);
    if (last_digit > 5) {
      add_arrays(arr, to_add, arr, HELPER_ARR_SIZE);
      last_digit = pre_last_digit + 1;
    } else if (last_digit == 5 && pre_last_digit % 2 != 0) {
      add_arrays(arr, to_add, arr, HELPER_ARR_SIZE);
      last_digit = pre_last_digit + 1;
    } else {
      last_digit = pre_last_digit;
    }
  }
}

void reduce_representation(size_t *const arr, int *const power) {
  while (is_dividable(arr, IMPLICIT_BASE) && !array_filled_by_zeroes(arr) &&
         valid_power(*power - 1)) {
    divide_array(arr, IMPLICIT_BASE);
    --(*power);
  }
}

char valid_power(const int power) {
  return power >= MIN_POWER && power <= MAX_POWER;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  char negative_1 = is_negative(&value_1), negative_2 = is_negative(&value_2);
  make_non_negative(&value_1);
  make_non_negative(&value_2);
  if (!negative_1 && !negative_2) {
    error = s21_add_inner(value_1, value_2, result);
  } else if (negative_1 && !negative_2) {
    error = s21_sub(value_2, value_1, result);
  } else if (!negative_1 && negative_2) {
    error = s21_sub(value_1, value_2, result);
  } else {
    error = s21_add_inner(value_1, value_2, result);
    if (!error) {
      invert_sign(result);
    } else {
      error = TEST_ARITHMETIC_NEG_INF;
    }
  }
  return error;
}

void assign_decimal_or_set_error(int *const error, s21_decimal *const result,
                                 const size_t *const res_arr,
                                 const int res_power, enum OPERATION_MODE mode,
                                 const char sign_lhs, const char sign_rhs) {
  if (!*error && valid_power(res_power)) {
    assign_decimal(result, res_arr, res_power);
    if (sign_lhs != sign_rhs && mode != ADD_SUB) {
      set_nth_bit(result, SIGN_BIT_INDEX);
    }
  } else if (!*error && res_power < MIN_POWER && sign_lhs != sign_rhs) {
    *error = TEST_ARITHMETIC_NEG_INF;
  } else if (!*error && res_power < MIN_POWER && sign_lhs == sign_rhs) {
    *error = TEST_ARITHMETIC_POS_INF;
  }
}

void make_non_negative_zero(s21_decimal *const val) {
  if (is_zero(val->bits, 3)) {
    make_non_negative(val);
  }
}

int make_arithmetic_pre_check(const enum OPERATION_MODE mode,
                              const s21_decimal value_1,
                              const s21_decimal value_2,
                              const s21_decimal *const result) {
  return (mode == DIV && is_zero(value_2.bits, DECIMAL_ARR_INT_COUNT - 1))
             ? TEST_ARITHMETIC_DIV_BY_ZERO
             : ((!is_valid_decimal(&value_1) || !is_valid_decimal(&value_2) ||
                 result == NULL)
                    ? INVALID_INPUT
                    : 0);
}

int make_arithmetics_routine(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result,
                             int (*operation)(size_t *, size_t *, size_t *,
                                              int),
                             enum OPERATION_MODE mode) {
  int error = make_arithmetic_pre_check(mode, value_1, value_2, result);
  if (!error) {
    make_non_negative_zero(&value_1);
    make_non_negative_zero(&value_2);
    initialize_bytes(result->bits, sizeof(int) * DECIMAL_ARR_INT_COUNT);
    char sign_lhs = get_nth_bit(&value_1, SIGN_BIT_INDEX);
    char sign_rhs = get_nth_bit(&value_2, SIGN_BIT_INDEX);
    int power1 = *get_power(&value_1), power2 = *get_power(&value_2);
    if (power1 > power2 && mode == ADD_SUB) {
      swap_decimal(&value_1, &value_2);
      swap_power(&power1, &power2);
    }
    size_t arr1[HELPER_ARR_SIZE], arr2[HELPER_ARR_SIZE],
        res_arr[HELPER_ARR_SIZE];
    initialize_bytes(arr1, sizeof(size_t) * HELPER_ARR_SIZE);
    initialize_bytes(arr2, sizeof(size_t) * HELPER_ARR_SIZE);
    copy_decimal_to_helper(&value_1, arr1);
    copy_decimal_to_helper(&value_2, arr2);
    if (mode == ADD_SUB) {
      equalize_powers(arr1, &power1, power2);
    }
    int res_power = mode == ADD_SUB
                        ? power1
                        : (mode == MUL ? power1 + power2 : power1 - power2);
    res_power +=
        error ? 0
              : operation(arr1, arr2, res_arr,
                          (mode == ADD_SUB || mode == MUL) ? HELPER_ARR_SIZE
                                                           : DIV_HELP_ARR_SIZE);
    free_extra_digits(res_arr, &res_power);

    reduce_representation(res_arr, &res_power);
    assign_decimal_or_set_error(&error, result, res_arr, res_power, mode,
                                sign_lhs, sign_rhs);
  }
  return error;
}

int s21_add_inner(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  return make_arithmetics_routine(value_1, value_2, result, add_arrays,
                                  ADD_SUB);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return make_arithmetics_routine(value_1, value_2, result, multiply_arrays,
                                  MUL);
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  return make_arithmetics_routine(value_1, value_2, result, divide_arrays, DIV);
}

int s21_sub_inner(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result) {
  return make_arithmetics_routine(value_1, value_2, result, subtract_arrays,
                                  ADD_SUB);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  char negative_1 = is_negative(&value_1), negative_2 = is_negative(&value_2);
  make_non_negative(&value_1);
  make_non_negative(&value_2);
  char compare_absolute_values_1_2 = compare_decimal(value_1, value_2);
  if (!negative_1 && !negative_2) {
    if (compare_absolute_values_1_2 == 1 || compare_absolute_values_1_2 == 0) {
      error = s21_sub_inner(value_1, value_2, result);
    } else {
      error = s21_sub_inner(value_2, value_1, result);
      if (!error) {
        invert_sign(result);
      } else {
        error = TEST_ARITHMETIC_NEG_INF;
      }
    }
  } else if (negative_1 && !negative_2) {
    error = s21_add(value_1, value_2, result);
    if (!error) {
      invert_sign(result);
    } else {
      error = TEST_ARITHMETIC_NEG_INF;
    }
  } else if (!negative_1 && negative_2) {
    error = s21_add(value_1, value_2, result);
  } else if (negative_1 && negative_2) {
    error = s21_sub(value_2, value_1, result);
  }
  return error;
}

char array_filled_by_zeroes(const size_t *const array) {
  char result = 1;
  for (int i = 0; i < HELPER_ARR_SIZE && result; ++i) {
    result = array[i] == 0;
  }
  return result;
}

char get_last_digit_of_helper_array_number(const size_t *const arr) {
  size_t tmp[HELPER_ARR_SIZE], copy[HELPER_ARR_SIZE];
  copy_helper_array(arr, tmp, HELPER_ARR_SIZE);
  copy_helper_array(arr, copy, HELPER_ARR_SIZE);
  size_t result[HELPER_ARR_SIZE];
  initialize_bytes(result, sizeof(size_t) * HELPER_ARR_SIZE);
  divide_array(copy, IMPLICIT_BASE);
  multiply_array(copy, IMPLICIT_BASE, HELPER_ARR_SIZE);
  subtract_arrays(tmp, copy, result, HELPER_ARR_SIZE);
  return result[0];
}

char *array_to_string(const size_t *const arr) {
  char *str = calloc(MAX_BUFFER_SIZE, sizeof(char));
  size_t idx = MAX_BUFFER_SIZE - 1;
  size_t copy[HELPER_ARR_SIZE];
  copy_helper_array(arr, copy, HELPER_ARR_SIZE);
  while (!array_filled_by_zeroes(copy)) {
    str[idx--] = get_last_digit_of_helper_array_number(copy) + '0';
    divide_array(copy, IMPLICIT_BASE);
  }
  ++idx;
  int i = 0;
  for (; idx < MAX_BUFFER_SIZE;) {
    str[i++] = str[idx++];
  }
  str[i] = '\0';
  return str;
}

char *decimal_to_string(const s21_decimal *const d) {
  size_t arr[HELPER_ARR_SIZE];
  initialize_bytes(arr, sizeof(size_t) * HELPER_ARR_SIZE);
  copy_decimal_to_helper(d, arr);
  char *mantissa = array_to_string(arr);
  int power = *get_power(d);
  int len = strlen(mantissa);
  int zeroes_count = power - len + 1;
  zeroes_count = zeroes_count > 0 ? zeroes_count : 0;
  char *zeroes = GetUniformString('0', zeroes_count);
  NativeInsert(&mantissa, zeroes, 0);
  NativeInsert(&mantissa, power == 0 ? "" : ".",
               zeroes_count > 0 ? 1 : len - power);
  NativeInsert(&mantissa, is_negative(d) ? "-" : "", 0);
  free(zeroes);
  return mantissa;
}