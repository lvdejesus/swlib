test-vector: test_vector.c vector.c
	gcc test_vector.c vector.c -g -Wall -fsanitize=address -o test_vector.out
	./test_vector.out

test-list: test_list.c list.c
	gcc test_list.c list.c -g -Wall -fsanitize=address -o test_list.out
	./test_list.out

test-hashmap: test_hashmap.c hashmap.c vector.c list.c
	gcc test_hashmap.c hashmap.c vector.c list.c -g -Wall -fsanitize=address -o test_hashmap.out
	./test_hashmap.out	
