#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "deque.h"

char *string = "Hello world!";
Deque *deque;

bool test_push() {
  deque_push(deque, &string[0]);
  char *value = deque_peek(deque);

  return value != NULL;
}

bool test_pop() {
  char *value = deque_pop(deque);

  return *value == 'H';
}

bool test_pop_multiple() {
  size_t n = strlen(string);
  for (size_t i = 0; i < n; i++) {
    deque_push(deque, &string[i]);
  }

  for (size_t i = 0; i < n; i++) {
    char *value = deque_pop(deque);

    if (*value != string[(n - 1) - i]) {
      return false;
    }
  }

  return true;
}

int main() {
  deque = deque_new();
  char *test_names[] = {
      "test_push",
      "test_pop",
      "test_pop_multiple",
  };

  bool (*tests[])() = {test_push, test_pop, test_pop_multiple};

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

  deque_free(deque);
}
