#include "s21_decimal.h"

float_as_ints decompose_float(const float f) {
  float_uint_t x;
  x.f = f;
  float_as_ints result;
  if (f != 0.0f && f != -0.0f) {
    result.power = 0;
    uint32_t n = x.u;
    result.sign = n >> (BITS_PER_INT - 1) & 1u;
    n &= ~(1u << (BITS_PER_INT - 1));
    result.mantissa = (1u << (FLOAT_MANTISSA_BITS_COUNT - 1)) |
                      (n & (~(0777u << (FLOAT_MANTISSA_BITS_COUNT - 1))));
    int add_to_power = -FLOAT_MANTISSA_BITS_COUNT;
    int under_log2 = result.mantissa & ~(result.mantissa - 1);
    int shift = under_log2 != 0 ? log2(under_log2) : 0;
    result.mantissa >>= shift;
    add_to_power += shift;
    result.power |= (n >> (FLOAT_MANTISSA_BITS_COUNT - 1));
    result.power -= 0x7F;
    result.power += add_to_power + 1;
  } else {
    result.mantissa = 0;
    result.power = 0;
    result.sign = f == -0.0f;
  }
  return result;
}

char get_significant_digit_count(const size_t *const arr) {
  size_t helper[HELPER_ARR_SIZE];
  copy_helper_array(arr, helper, HELPER_ARR_SIZE);
  char count = 0;
  while (!array_filled_by_zeroes(helper)) {
    divide_array(helper, IMPLICIT_BASE);
    ++count;
  }
  return count;
}

char round_arr_to_n_digit(size_t *const arr, char digit_count) {
  char power = 0;
  char cur_digit_count = get_significant_digit_count(arr);
  char last_digit = get_last_digit_of_helper_array_number(arr), pre_last_digit;
  size_t to_add[HELPER_ARR_SIZE] = {1, 0, 0, 0, 0};
  while (cur_digit_count-- > digit_count) {
    divide_array(arr, IMPLICIT_BASE);
    ++power;
    pre_last_digit = get_last_digit_of_helper_array_number(arr);
    if (last_digit > 5) {
      add_arrays(arr, to_add, arr, HELPER_ARR_SIZE);
      last_digit = (pre_last_digit + 1) % IMPLICIT_BASE;
    } else if (last_digit == 5 && (pre_last_digit & 1u)) {
      add_arrays(arr, to_add, arr, HELPER_ARR_SIZE);
      last_digit = (pre_last_digit + 1) % IMPLICIT_BASE;
    } else {
      last_digit = pre_last_digit % IMPLICIT_BASE;
    }
  }
  return power;
}

void round_decimal_to_nth_digits(s21_decimal *const d, char digit_count) {
  size_t arr[HELPER_ARR_SIZE];
  initialize_bytes(arr, HELPER_ARR_SIZE * sizeof(size_t));
  copy_decimal_to_helper(d, arr);
  char extra_power = round_arr_to_n_digit(arr, digit_count);
  s21_decimal multiplyer;
  s21_from_int_to_decimal(IMPLICIT_BASE, &multiplyer);
  s21_pow(multiplyer, (size_t)extra_power, &multiplyer);
  assign_decimal(d, arr, *get_power(d));
  s21_mul(*d, multiplyer, d);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  return s21_from_float_to_decimal_opt_rounding(src, dst, 1);
}

int s21_from_float_to_decimal_opt_rounding(float src, s21_decimal *dst,
                                           const char round) {
  int error = dst == NULL;
  float_as_ints f = decompose_float(src);
  s21_from_int_to_decimal(f.mantissa, dst);
  s21_decimal one, multiplyer;
  s21_from_int_to_decimal(2, &multiplyer);
  s21_from_int_to_decimal(1, &one);
  if (f.power < 0) {
    f.power = -f.power;
    s21_div(one, multiplyer, &multiplyer);
  }
  while (f.power != 0) {
    int power = min(f.power, 32);
    s21_decimal tmp;
    s21_pow(multiplyer, power, &tmp);
    error += s21_mul(*dst, tmp, dst);
    f.power -= power;
  }
  if (round) {
    round_decimal_to_nth_digits(dst, MAX_DECIMAL_DIGITS_IN_FLOAT);
  }
  if (f.sign) {
    make_negative(dst);
  }
  if (error || (src != -0.0f && src != 0.0f &&
                is_zero(dst->bits, DECIMAL_ARR_INT_COUNT - 1))) {
    error = 1;
    s21_from_int_to_decimal(0, dst);
  }
  return error;
}

char *GetUniformString(const char c, const size_t count) {
  char *str = calloc(count + 1, 1);
  for (size_t i = 0; i < count; ++i) {
    str[i] = c;
  }
  str[count] = '\0';
  return str;
}

void NativeInsert(char **const to, const char *const from,
                  const size_t position) {
  char *tmp = s21_insert(*to, from, position);
  free(*to);
  *to = tmp;
}

void *s21_insert(const char *into, const char *str, size_t start_index) {
  int error = 0;
  char *new_string = NULL;
  size_t into_len = 0;
  size_t str_len = 0;
  if (into && str && !(start_index > (into_len = strlen(into)))) {
    str_len = strlen(str);
    new_string = (char *)calloc(1, into_len + str_len + 1);
    if (new_string) {
      int char_to_copy = (size_t)start_index;
      s21_strcpyn(into, new_string, &char_to_copy, 0);
      char_to_copy = str_len;
      s21_strcpyn(str, new_string + start_index, &char_to_copy, 0);
      char_to_copy = into_len - start_index;
      s21_strcpyn(into + start_index, new_string + start_index + str_len,
                  &char_to_copy, 0);
    }
  }
  return error ? NULL : new_string;
}

void s21_strcpyn(const char *from, char *to, int *const max_char,
                 const int wchar) {
  if (wchar) {
    wchar_t *act = (wchar_t *)to;
    while (*max_char > 0 && (*act++ = *from++)) {
      --(*max_char);
    }
  } else {
    while (*max_char > 0 && (*to++ = *from++)) {
      --(*max_char);
    }
  }
}

void initialize_bytes(void *dst, int n) {
  char *const ptr = (char *)dst;
  for (int i = 0; i < n; ++i) {
    ptr[i] = 0;
  }
}

int s21_from_decimal_to_float(const s21_decimal src, float *dst) {
  int error = dst == NULL;
  if (!error) {
    double value = 0;
    value += (double)(uint32_t)src.bits[0];
    value += (double)(uint32_t)src.bits[1] * pow(2.0, 32);
    value += (double)(uint32_t)src.bits[2] * pow(2.0, 64);
    int scale = *get_power(&src);
    value /= pow(10.0, scale);
    value *= is_negative(&src) ? -1.0 : 1.0;
    *dst = (float)value;
  }
  return error;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = dst == NULL;
  if (!error) {
    initialize_bytes(dst->bits, DECIMAL_ARR_INT_COUNT * sizeof(int));
    uint8_t negative = src < 0 ? 1u << 7 : 0;
    src = src < 0 ? -src : src;
    dst->bits[0] = src;
    char *third_byte_of_bits_3 =
        ((char *)(dst->bits + DECIMAL_ARR_INT_COUNT - 1)) + sizeof(int) - 1;
    *third_byte_of_bits_3 |= negative;
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = dst == NULL;
  int power = *get_power(&src);
  size_t arr[HELPER_ARR_SIZE];
  initialize_bytes(arr, HELPER_ARR_SIZE * sizeof(size_t));
  copy_decimal_to_helper(&src, arr);
  while (power != 0) {
    divide_array(arr, Pow(IMPLICIT_BASE, min(power, 9)));
    power -= min(power, 9);
  }
  int elder_set_bit_index = get_max_set_bit(arr, HELPER_ARR_SIZE);
  if (elder_set_bit_index > 0 ||
      (elder_set_bit_index == 0 && arr[elder_set_bit_index] > INT_MAX)) {
    error = 1;
  } else if (elder_set_bit_index == -1) {
    *dst = 0;
  } else {
    *dst = is_negative(&src) ? -arr[0] : arr[0];
  }
  return error;
}

char get_nth_bit(const s21_decimal *const d, const int n) {
  assert(n >= 0 && n < 128);
  return d->bits[n / BITS_PER_INT] >> n % BITS_PER_INT & 1u;
}

void set_nth_bit(s21_decimal *const d, const int n) {
  assert(n >= 0 && n < 128);
  uint32_t u = 1u << n % BITS_PER_INT;
  d->bits[n / BITS_PER_INT] |= u;
}

void unset_nth_bit(s21_decimal *const d, const int n) {
  assert(n >= 0 && n < 128);
  uint32_t u = ~(1u << (n % BITS_PER_INT));
  d->bits[n / BITS_PER_INT] &= u;
}

void invert_nth_bit(s21_decimal *const d, const int n) {
  assert(n >= 0 && n < 128);
  uint32_t u = 1u << (n % BITS_PER_INT);
  d->bits[n / BITS_PER_INT] ^= u;
}
