CC = g++
CCFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS = -lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
REPORT_DIR = report

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXE = $(BUILD_DIR)/test.out

OS = $(shell uname)
ifeq ($(OS), Linux)
        CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
        OPEN_CMD = xdg-open
else
        CHECK_FLAGS = -lcheck
        OPEN_CMD = open
endif


all: test gcov_report

test: clean $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE):
	mkdir -p $(BUILD_DIR)
	$(CC) $(CCFLAGS) -I$(SRC_DIR) $(TEST_SRCS) -o $(TEST_EXE) $(GTEST_FLAGS)

gcov_report: clean
	@mkdir -p $(BUILD_DIR) $(REPORT_DIR)
	$(CC) $(CCFLAGS) $(GCOV_FLAGS) -I. $(TEST_SRCS) -o $(TEST_EXE) $(GTEST_FLAGS)
	./$(TEST_EXE)
	gcovr -r . \
		--filter ".*s21_.*" \
		--html --html-details -o $(REPORT_DIR)/index.html \
		--print-summary
	$(OPEN_CMD) ./report/index.html

clean:
	rm -rf $(BUILD_DIR) $(REPORT_DIR) *.gcda *.gcno *.css

clang_format:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i *.h ./tests/*
	rm -f .clang-format

clang_check:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n *.h ./tests/*
	rm -f .clang-format

leaks: test
ifeq ($(OS), Darwin)
	leaks --atExit -- build/test.out
else
	valgrind --leak-check=full --show-leak-kinds=all build/test.out
endif


.PHONY: all test gcov_report clean clang_format clang_check