CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LDFLAGS = -lcheck -lm -lquadmath

TEST_DIR = test
OBJ_DIR = obj

SRCS = $(wildcard *.c)
SRCS := $(filter-out test_main.c, $(SRCS))
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_SRCS))

ADD_LIB = -lcheck

ifeq ($(shell uname), Linux)
    LDFLAGS += -lsubunit
    OPEN = xdg-open
else
    OPEN = open
endif

all: format s21_decimal.a test

test: $(TEST_OBJS) s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_OBJS) s21_decimal.a $(ADD_LIB) $(LDFLAGS) -o s21_test
	./s21_test

s21_decimal.a: $(OBJS)
	ar rcs s21_decimal.a $(OBJS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report: clean
	$(CC) --coverage $(SRCS) $(LDFLAGS) -c
	$(CC) $(TEST_DIR)/*.c $(LDFLAGS) -c
	gcc -o s21_test *.o $(ADD_LIB) $(LDFLAGS) --coverage
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d . && lcov --remove s21_test.info '/usr/local/lib/*' -o s21_test.info --ignore-errors unused
	mkdir -p report
	genhtml -o report s21_test.info
	$(OPEN) ./report/index.html

clean:
	rm -rf $(OBJ_DIR) s21_decimal.a s21_test *.gcno *.gcda s21_test.info report log_valgrind *.o

rebuild: clean s21_decimal.a

format-check:
	@cp ../materials/linters/.clang-format ./
	@clang-format -n *.c *.h 
	@clang-format -n $(TEST_DIR)*.c $(TEST_DIR)*.h 
	@rm .clang-format

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.c *.h 
	@clang-format -i $(TEST_DIR)*.c $(TEST_DIR)*.h 
	@rm .clang-format

cppcheck:
	cppcheck -q --enable=all --inconclusive *.c $(TEST_DIR)/*.c

valgrind: test
	valgrind --leak-check=full --log-file=log_valgrind ./s21_test

.PHONY: all clean test
