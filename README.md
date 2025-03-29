# DecimalLib - High-Precision Decimal Arithmetic Library in C

![C](https://img.shields.io/badge/C-99-blue)
![License](https://img.shields.io/badge/License-MIT-green)

DecimalLib is a high-performance decimal arithmetic library implemented in C, designed to provide accurate decimal floating-point operations without the rounding errors inherent in binary floating-point representations. This library is particularly suitable for financial calculations, scientific computations, and other applications requiring precise decimal arithmetic.

## Key Features

- **Precise Decimal Arithmetic**: Supports addition, subtraction, multiplication, and division with exact decimal representation
- **Extended Functionality**:
  - Rounding (`s21_round`)
  - Truncation (`s21_truncate`)
  - Floor/ceiling operations (`s21_floor`)
  - Negation (`s21_negate`)
- **Type Conversion**:
  - Float ↔ Decimal conversion
  - Integer ↔ Decimal conversion
- **Comparison Operations**: Full set of comparison functions (eq, neq, lt, gt, etc.)
- **Arbitrary Precision**: Supports numbers with up to 28 decimal places
- **Memory Efficient**: Compact 128-bit internal representation (4x32-bit words)

## API Documentation

### Basic Arithmetic Operations

```c
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

### Comparison Operations
int s21_is_less(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int is_equal(s21_decimal num1, s21_decimal num2);

### Conversion Functions
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

### Additional Functions
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
```
### Usage Example

```c
#include "s21_decimal.h"

int main() {
    s21_decimal a, b, result;
    
    // Initialize from integers
    s21_from_int_to_decimal(12345, &a);
    s21_from_int_to_decimal(6789, &b);
    
    // Perform arithmetic
    s21_add(a, b, &result);
    
    // Convert back to int
    int sum;
    s21_from_decimal_to_int(result, &sum);
    printf("Sum: %d\n", sum);  // Output: 19134
    
    return 0;
}
```
## Error Handling
**The library returns error codes for exceptional cases:**

- TEST_ARITHMETIC_OK (0) - Success

- TEST_ARITHMETIC_POS_INF - Positive infinity (overflow)

- TEST_ARITHMETIC_NEG_INF - Negative infinity (underflow)

- TEST_ARITHMETIC_DIV_BY_ZERO - Division by zero

- INVALID_INPUT - Invalid input parameters

## Internal Representation
Numbers are stored in a s21_decimal structure:

```c
typedef struct s21_decimal {
    int bits[4];  // 128 bits total (32 bits × 4)
} s21_decimal;
```

**The bits are organized as follows:**

- Bits 0-95: Value (three 32-bit words)

- Bits 96-126: Unused

- Bit 127: Sign bit (1 for negative)

- Bits 112-119 (16-23): Scale factor (exponent)

## Building and Installation

Clone the repository:
```bash
git clone https://github.com/dmitrii-gbe/DecimalLib.git
cd DecimalLib
make
gcc your_app.c -I/path/to/DecimalLib -L/path/to/DecimalLib/build -ldecimal -o your_app
```
## Testing
The library includes comprehensive test coverage. To run tests:
```
make test
```
## License
MIT License.

## Contributing
- Fork the repository

- Create your feature branch (git checkout -b feature/fooBar)

- Commit your changes (git commit -am 'Add some fooBar')

- Push to the branch (git push origin feature/fooBar)

- Create a new Pull Request

