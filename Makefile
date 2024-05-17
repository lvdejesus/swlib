test-vector: tests/test_vector.c vector.c
	gcc tests/test_vector.c vector.c -I. -g -Wall -fsanitize=address -o test_vector.out
	./test_vector.out

test-list: tests/test_list.c list.c
	gcc tests/test_list.c list.c -I. -g -Wall -fsanitize=address -o test_list.out
	./test_list.out

test-hashmap: tests/test_hashmap.c hashmap.c vector.c list.c
	gcc tests/test_hashmap.c hashmap.c vector.c list.c -I. -g -Wall -fsanitize=address -o test_hashmap.out
	./test_hashmap.out	
