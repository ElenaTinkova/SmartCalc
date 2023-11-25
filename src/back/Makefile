FLAGS = -Wall -Wextra -Werror -std=c11
TESTFLAGS = -lcheck --coverage
SOURCES_FUN:=$(shell find . -not -name "test_calc.c" -name "*.c")

ifeq ($(shell uname), Linux)
TESTFLAGS += -lm -lsubunit
else
TESTFLAGS += -fprofile-arcs -ftest-coverage
endif

all:


install:


uninstall:


clean:
	@rm -rf *.o testing.c testing *.a *.gcno *.gcda *.gcov *.info *.out *a. *.dSYM
	@rm -rf html_report s21_smart_calc s21_calc_test html_report

dvi:


dist:


test:


gcov_report:
	gcc $(TESTFLAGS) *.c -o calc_work $(TESTFLAGS)
	./calc_work
	gcov -f $(SOURCES_FUN)
	lcov --no-external -t test -o coverage.info -c -d . 
	@genhtml -o html_report coverage.info
	@open html_report/index.html



lint:
	clang-format --style=Google -i *.c *.h