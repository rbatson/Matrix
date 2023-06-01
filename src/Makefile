.PHONY: all re s21_matrix clean check test
#.PHONY если есть файлы с именем как цель, они игнорируются

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
TST_LIBS :=  -lcheck -lm -lpthread
OS := $(shell uname -s)

ifeq ($(OS),Linux)
	CFLAGS+=-D LINUX
else
	ifeq ($(OS),Darwin)
		CFLAGS+=-D MAC
	endif
endif

all: test s21_matrix.a gcov_report

re: clean test gcov_report

test: s21_matrix.a s21_test.o
	$(CC) $(CFLAGS) s21_test.o s21_matrix.a $(TST_LIBS) -o test
	./test

s21_test.o: s21_test_matrix.c
	$(CC) $(CFLAGS) -c s21_test_matrix.c -o s21_test.o

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o: s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c -o s21_matrix.o

gcov_report: gcov_test.info
	genhtml -o report/ gcov_test.info
	open report/index.html

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: s21_test_matrix.c s21_matrix.c
	$(CC) $(CFLAGS) --coverage s21_test_matrix.c s21_matrix.c $(TST_LIBS) -o gcov_test

gcov_test.gcda:
	chmod +x *
	./gcov_test

clean: 
	rm -rf test gcov_test *.gcno *.gcda *.info report *.o *.a gcov_test.dSYM

check:
	cppcheck *.h *.c
	clang-format -n -style=Google *.c *.h
	make test
	leaks --atExit -- test
	
valgrind:
	valgrind --leak-check=full --track-origins=yes --trace-children=yes -s ./test
