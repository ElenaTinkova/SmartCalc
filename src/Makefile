CFLAGS = -Wall -Wextra -Werror -std=c11
TESTFLAGS = -lcheck --coverage
SOURCES_FUN:=back/*.c
TESTS_FUN:= test/test_calculations.c
DIR_DIST:= SmartCalc-1.0


ifeq ($(shell uname), Linux)
TESTFLAGS += -lm -lsubunit
OPEN:= xdg-open 
else
TESTFLAGS += -fprofile-arcs -ftest-coverage
OPEN:= open 
endif

all: install


install:  uninstall
	@mkdir build
	@cd ./ui && qmake && make -j && make clean && rm -rf Makefile && mv Calculator.app ../build/SmartCalc.app
	@printf "\033[35;1m\nSmartCalc is installed\033[0m\nYou can find the app in the \033[4mbuild\033[0m directory\n"
	@printf "Also you can run \033[4mmake launch\033[0m to open the app\n\n"



uninstall:
	@rm -rf build
	@rm -rf ui/.qmake.stash
	@rm -rf ui/*.o ui/Calculator.app ui/ui_* ui/Makefile ui/.qtc_clangd


launch:
	@$(OPEN) build/SmartCalc.app


clean:
	@rm -rf *.o testing.c testing *.out *a. *.dSYM
	@rm -rf *.a *.gcno *.gcda *.gcov *.info report_gcov html_report calc_cover


dvi:
	$(OPEN) ../documentation.pdf


dist:
	@mkdir -p $(DIR_DIST)
	@cp -R back ui ../images buttons_icons $(DIR_DIST)
	@cp Makefile ../documentation.pdf $(DIR_DIST)
	@tar --totals -cvf $(DIR_DIST).tar $(DIR_DIST)
	@rm -rf $(DIR_DIST)


clean_dist:
	rm -rf $(DIR_DIST).tar


test: clean
	@gcc $(CFLAGS) $(TESTS_FUN) $(SOURCES_FUN) $(TESTFLAGS) -o testing
	./testing


gcov_report: test
	@gcov -a test_calculations.c
	lcov --no-external -exclude test -t report_gcov -o coverage.info -c -d . 
	@genhtml -o html_report coverage.info
	@open html_report/index.html


lint:
	clang-format --style=Google -i ./back/*.c ./back/*.h ./ui/*.cpp test/*.c test/*.h