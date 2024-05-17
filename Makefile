test-vector: test_vector.c vector.c
	gcc test_vector.c vector.c -Wall -fsanitize=address -o test_vector.out
	./test_vector.out

test-list: test_list.c list.c
	gcc test_list.c list.c -Wall -fsanitize=address -o test_list.out
	./test_list.out
