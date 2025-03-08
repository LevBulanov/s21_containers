CC = gcc
FLAGS = -g -Wall -Wextra -std=c++17
TEST_DIR = tests
TEST_RUNNER = tests/build/test_runner
CLANG_FORMAT = clang-format-18 
СLANG_FORMAT_FILE = ../materials/linters/.clang-format

TEST_SRC = tests/*.cc
HEADER_SRC = *.h

TBD = tests/build

LINK_LIBS = -lstdc++
LINK_TEST_LIBS = -lgtest -lgtest_main -lm
VALGRIND = valgrind --tool=memcheck --leak-check=full ./$(TEST_RUNNER)

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf $(TBD)
	rm -rf *.html
	rm -rf *.css
	rm -rf *.out
	rm -rf *.gcno

.PHONY: test
test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

tests/build/test_runner: $(TEST_SRC) $(HEADER_SRC)
	mkdir -p tests/build
	$(CC) $(TEST_SRC) $(LINK_TEST_LIBS) $(LINK_LIBS) $(FLAGS) -o $@

.PHONY: check_valgrind
check_valgrind: $(TEST_RUNNER)
	$(VALGRIND)

.PHONY: gcov_report
gcov_report: 
	mkdir -p tests/build
	$(CC) --coverage -fPIC $(TEST_SRC) $(LINK_TEST_LIBS) $(LINK_LIBS) $(FLAGS) -o $(TEST_RUNNER)
	./$(TEST_RUNNER)
	gcovr -e 'tests/*' --html-details gcovr-report.html

.PHONY: clang_format
clang_format:
	cp $(СLANG_FORMAT_FILE) ./
	cp $(СLANG_FORMAT_FILE) ./tests/
	$(CLANG_FORMAT) -i *.h
	$(CLANG_FORMAT) -i tests/*.cc
