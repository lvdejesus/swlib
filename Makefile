test: test_vector.c vector.c
	gcc test_vector.c vector.c -Wall -fsanitize=address -o test_vector.out
	./test_vector.out
