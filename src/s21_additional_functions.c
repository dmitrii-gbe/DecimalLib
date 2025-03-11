#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 1;
  if (result != NULL) {
    *result = value;
    invert_nth_bit(result, 127);
    status = 0;
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  int scale = get_scale(&value);
  if (scale > 0 && scale < 28) {
    *result = value;
    for (int i = 0; i < scale; i++) {
      div_ten(result);
      uint32_t sign_mask = 1 << SIGN_SHIFT;
      result->bits[3] = value.bits[3] & sign_mask;
    }
  } else if (scale >= 28) {
    status = 1;
  } else {
    *result = value;
  }
  return status;
}

int s21_is_zero(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = 1;

  if (result != NULL) {
    initialize_bytes(result->bits, DECIMAL_ARR_INT_COUNT);
    *result = value;

    s21_decimal num_five = {.bits = {5, 0, 0, 0}};
    set_new_sign(&num_five, 0);
    char *num_five_scale = get_power(&num_five);
    *num_five_scale = 1;

    int sign = get_sign(&value);

    if (sign) {
      s21_sub(*result, num_five, result);
    } else {
      s21_add(*result, num_five, result);
    }
    s21_truncate(*result, result);

    s21_decimal truncate_num;
    s21_truncate(value, &truncate_num);
    s21_decimal fractional_part;
    s21_sub(value, truncate_num, &fractional_part);

    status = 0;
  }

  return status;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = 1;

  if (result != NULL) {
    initialize_bytes(result->bits, DECIMAL_ARR_INT_COUNT * sizeof(int));
    *result = value;

    int scale = get_scale(&value);
    int sign = get_sign(&value);

    s21_truncate(value, result);

    if (sign && scale > 0) {
      s21_decimal fractional_part = {0};
      s21_sub(value, *result, &fractional_part);

      if (!s21_is_zero(fractional_part)) {
        s21_decimal number_one = {.bits = {1, 0, 0, 0}};
        s21_sub(*result, number_one, result);
      }
    }

    status = 0;
  }

  return status;
}

void set_new_sign(s21_decimal *decimal, int new_sign) {
  if (new_sign) {
    decimal->bits[3] |= SIGN_MASK;
  } else {
    decimal->bits[3] &= ~SIGN_MASK;
  }
}

int get_scale(const s21_decimal *decimal) {
  int scale_info = decimal->bits[3] & SCALE_MASK;
  return scale_info >> SCALE_SHIFT;
}

uint64_t calculate_current_value(int ostatok, uint32_t bit) {
  return ((uint64_t)ostatok << 32) | bit;
}

void update_value_and_ostatok(uint64_t current, uint32_t *bit, int *ostatok) {
  *bit = (uint32_t)(current / 10);
  *ostatok = current % 10;
}

void div_ten(s21_decimal *decimal) {
  int ostatok = 0;
  for (int i = 2; i >= 0; i--) {
    uint64_t current = calculate_current_value(ostatok, decimal->bits[i]);
    update_value_and_ostatok(current, (uint32_t *)&decimal->bits[i], &ostatok);
  }
}

char is_valid_decimal(const s21_decimal *const d) {
  int error = 0;
  char *first_byte_of_last_int = (char *)(d->bits + DECIMAL_ARR_INT_COUNT - 1);

  for (int i = 0; i < (BITS_PER_INT / BITS_PER_BYTE); ++i) {
    if (i < 2) {
      error += *(first_byte_of_last_int + i) != 0;
    } else if (i == 3) {
      error += !(*(first_byte_of_last_int + i) == 0 ||
                 *(unsigned char *)(first_byte_of_last_int + i) == 0x80);
    }
  }
  return error == 0 && valid_power(*get_power(d));
}