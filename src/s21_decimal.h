#pragma once

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITS_PER_BYTE 8
#define BITS_PER_INT 32
#define HELPER_ARR_SIZE 6
#define DECIMAL_ARR_INT_COUNT 4
#define POWER_BYTE_INDEX 2
#define MAX_POWER 28
#define MIN_POWER 0
#define IMPLICIT_BASE 10lu
#define SIGN_BIT_INDEX 127
#define MAX_BUFFER_SIZE 128
#define BASE (1LLU << 32)
#define FRACTION_DIGITS 6
#define DIV_HELP_ARR_SIZE (FRACTION_DIGITS + HELPER_ARR_SIZE)
#define FLOAT_MANTISSA_BITS_COUNT 24
#define MAX_DECIMAL_DIGITS_IN_FLOAT 7
#define MAX_FLOAT_MANTISSA 0xFFFFFF
#define SCALE_SHIFT 16
#define SCALE_MASK 0x00FF0000
#define SIGN_SHIFT 31
#define SIGN_MASK 0x80000000

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef enum s21_arithmetic_result {
  TEST_ARITHMETIC_OK = 0,
  TEST_ARITHMETIC_POS_INF,
  TEST_ARITHMETIC_NEG_INF,
  TEST_ARITHMETIC_DIV_BY_ZERO,
  INVALID_INPUT
} s21_arithmetic_result;

typedef struct float_as_ints {
  uint32_t mantissa;
  int power;
  char sign;
} float_as_ints;

typedef union float_uint_t {
  float f;
  uint32_t u;
} float_uint_t;

enum OPERATION_MODE { ADD_SUB, MUL, DIV };

#define TRUE 1
#define FALSE 0

// COMPARE
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

// CONSTRUCTORS
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_float_to_decimal_opt_rounding(float src, s21_decimal *dst,
                                           const char round);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ARITHMETICS
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// ADDITIONAL
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// Helper functions for COMPARE
int get_sign(const s21_decimal *num);

// Helper functions for ADDITIONAL
void set_new_sign(s21_decimal *decimal, int new_sign);
int get_scale(const s21_decimal *decimal);
uint64_t calculate_current_value(int ostatok, uint32_t bit);
void update_value_and_ostatok(uint64_t current, uint32_t *bit, int *ostatok);
void div_ten(s21_decimal *decimal);
int s21_is_zero(s21_decimal value);
char is_valid_decimal(const s21_decimal *const d);

// Helper functions for CONSTRUCTORS
float_as_ints decompose_float(const float f);
char *GetUniformString(const char c, const size_t count);
void NativeInsert(char **const to, const char *const from,
                  const size_t position);
void *s21_insert(const char *into, const char *str, size_t start_index);
void s21_strcpyn(const char *from, char *to, int *const max_char,
                 const int wchar);
char get_significant_digit_count(const size_t *const arr);
char round_arr_to_n_digit(size_t *const arr, char digit_count);
void round_decimal_to_nth_digits(s21_decimal *const d, char digit_count);
// Functions for working with bits - CONSTRUCTORS
char get_nth_bit(const s21_decimal *const d, const int n);
void set_nth_bit(s21_decimal *const d, const int n);
void unset_nth_bit(s21_decimal *const d, const int n);
void invert_nth_bit(s21_decimal *const d, const int n);
void initialize_bytes(void *dst, int n);
char get_elder_set_bit(int n);

// Helper functions for ARITHMETICS
char max(const char lhs, const char rhs);
int min(size_t lhs, size_t rhs);
void s21_pow(s21_decimal d, size_t pow, s21_decimal *const result);
char compare_decimal(s21_decimal value_1, s21_decimal value_2);
void make_non_negative(s21_decimal *const d);
void make_negative(s21_decimal *const d);
char is_negative(const s21_decimal *const d);
void invert_sign(s21_decimal *const d);
int add_arrays(size_t *const arr1, size_t *const arr2, size_t *const result,
               int size);
char all_of(const size_t *const arr, const size_t size, const size_t val);
char is_zero(const int *const arr, const size_t size);
char approaches_limit(const size_t *const digits, const int n);
int divide_arrays(size_t *const dividend, size_t *divider, size_t *result,
                  const int size);
void multiply_arrays_div(size_t *const arr1, size_t *const arr2,
                         size_t *const result);
int multiply_arrays(size_t *const arr1, size_t *const arr2,
                    size_t *const result, int size);
char get_max_set_bit(const size_t *const arr, int size);
void rebalance_array_for_subtraction(size_t *const arr, int size);
int subtract_arrays(size_t *const arr1, size_t *const arr2,
                    size_t *const result, int size);
void copy_helper_array(const size_t *const from, size_t *const to,
                       const size_t n);
char are_equal_helper_arrays(const size_t *const arr1,
                             const size_t *const arr2);
void divide_array(size_t *const arr, const size_t divider);
void multiply_array(size_t *const arr, const size_t multiplyer, int size);
char *get_power(const s21_decimal *const d);
void copy_decimal(const s21_decimal *const from, s21_decimal *const to);
void swap_decimal(s21_decimal *d1, s21_decimal *const d2);
void swap_power(int *const power1, int *const power2);
void copy_decimal_to_helper(const s21_decimal *const from, size_t *const to);
size_t Pow(size_t base, int power);
void equalize_powers(size_t *const arr, int *const low, const int hight);
char in_range(const size_t *const arr);
void assign_decimal(s21_decimal *const d, const size_t *const arr,
                    const char power);
char is_dividable(size_t *arr, int number);
void free_extra_digits(size_t *const arr, int *const power);
void reduce_representation(size_t *const arr, int *const power);
char valid_power(const int power);
void assign_decimal_or_set_error(int *const error, s21_decimal *const result,
                                 const size_t *const res_arr,
                                 const int res_power, enum OPERATION_MODE mode,
                                 const char sign_lhs, const char sign_rhs);
void make_non_negative_zero(s21_decimal *const val);
int make_arithmetic_pre_check(const enum OPERATION_MODE mode,
                              const s21_decimal value_1,
                              const s21_decimal value_2,
                              const s21_decimal *const result);
int make_arithmetics_routine(s21_decimal value_1, s21_decimal value_2,
                             s21_decimal *result,
                             int (*operation)(size_t *, size_t *, size_t *,
                                              int),
                             enum OPERATION_MODE mode);
int s21_add_inner(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);
int s21_sub_inner(s21_decimal value_1, s21_decimal value_2,
                  s21_decimal *result);
char array_filled_by_zeroes(const size_t *const array);
char get_last_digit_of_helper_array_number(const size_t *const arr);
char *array_to_string(const size_t *const arr);
char *decimal_to_string(const s21_decimal *const d);
