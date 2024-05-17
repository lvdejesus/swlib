#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"

char *string = "Hello world!";
Vector *vector;

bool test_push() {
  vector_push(vector, &string[0]);
  char *value = vector_get(vector, 0);

  return value != NULL;
}

bool test_out_of_bounds() {
  void *value = vector_get(vector, 1);

  return value == NULL;
}

bool test_pop() {
  char *value = vector_pop(vector);

  return *value == 'H';
}

// should be size 12
bool test_resize_up() {
  for (size_t i = 0; i < strlen(string); i++) {
    vector_push(vector, &string[i]);
  }

  return vector->capacity > 8;
}

// should be size 0
bool test_resize_down() {
  for (size_t i = 0; i < strlen(string); i++) {
    vector_pop(vector);
  }

  return vector->capacity < 8;
}

int main() {
  vector = vector_new(8, sizeof(char));
  char *test_names[] = {
      "test_push",      "test_out_of_bounds", "test_pop",
      "test_resize_up", "test_resize_down",
  };

  bool (*tests[])() = {test_push, test_out_of_bounds, test_pop, test_resize_up,
                       test_resize_down};

  unsigned int n = sizeof(tests) / sizeof(*(tests));
  unsigned int failed = 0;

  for (size_t i = 0; i < n; i++) {
    bool result = (*tests[i])();

    printf("%s - ", test_names[i]);
    printf(result ? "PASS" : "FAIL");
    printf("\n");

    if (!result) {
      failed += 1;
    }
  }

  printf("=== %u out of %u test(s) failed ===\n", failed, n);

  vector_free(vector);
}
