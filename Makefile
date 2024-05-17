FLAGS=-I. -g -Wall -fsanitize=address

test: test-vector test-list test-hashmap test-deque
	make test-vector
	make test-list
	make test-hashmap
	make test-deque

test-vector: tests/test_vector.c vector.c
	gcc tests/test_vector.c vector.c ${FLAGS} -o test_vector.out
	./test_vector.out
	rm test_vector.out

test-list: tests/test_list.c list.c
	gcc tests/test_list.c list.c ${FLAGS} -o test_list.out
	./test_list.out
	rm test_list.out

test-hashmap: tests/test_hashmap.c hashmap.c vector.c list.c
	gcc tests/test_hashmap.c hashmap.c vector.c list.c ${FLAGS} -o test_hashmap.out
	./test_hashmap.out	
	rm test_hashmap.out

test-deque: tests/test_deque.c deque.c
	gcc tests/test_deque.c deque.c ${FLAGS} -o test_deque.out
	./test_deque.out
	rm test_deque.out
