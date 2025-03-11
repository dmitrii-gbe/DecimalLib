#pragma once
#include <check.h>
#include <limits.h>
#include <quadmath.h>
#include <time.h>

#include "../s21_decimal.h"

int test_decimal_to_float_external();
int arithmetics_test();
Suite *mul_suite(void);
Suite *sub_suite(void);
Suite *div_suite(void);
Suite *add_suite(void);
Suite *compare_suite(void);
Suite *floor_suite(void);
Suite *round_suite(void);
Suite *negate_suite(void);
Suite *truncate_suite(void);
Suite *decimal_to_float_suite(void);
Suite *decimal_to_int_suite(void);
Suite *float_to_decimal_suite(void);
Suite *int_to_decimal_suite(void);
Suite *rand_arithmetics_suite();
