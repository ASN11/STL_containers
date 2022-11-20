CC = gcc
CFLAGS = -lstdc++ -std=c++17 -Wall -Werror -Wextra
TEST_LIBS = -lgtest

all: tests check

tests: test_array test_list test_map test_queue test_set test_stack test_vector

test_array:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_array/s21_array_tests.cc -o test.out
	./test.out

test_list:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_list/s21_list_tests.cc -o test.out
	./test.out

test_map:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_map/s21_map_tests.cc -o test.out
	./test.out

test_multiset:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_multiset_tests.cc -o test.out
	./test.out

test_queue:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_queue/s21_queue_tests.cc -o test.out
	./test.out

test_set:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_set/s21_set_tests.cc -o test.out
	./test.out

test_stack:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_stack/s21_stack_tests.cc -o test.out
	./test.out

test_vector:
	$(CC) $(CFLAGS) $(TEST_LIBS) s21_vector/s21_vector_tests.cc -o test.out
	./test.out

check:
	cp ../materials/linters/.clang-format .
	clang-format -n s21_array/* \
					s21_list/* \
					s21_map/* \
					s21_multiset/* \
					s21_queue/* \
					s21_set/* \
					s21_stack/* \
					s21_vector/* \
					node.h \
					s21_containers.h \
					s21_containersplus.h

	rm -f .clang-format


clean:
	rm -f test.out
