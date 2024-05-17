#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

char *string = "Hello world!";
List *list;

bool test_push() {
  list_push(list, &string[0]);
  char *value = list_peek(list);

  return value != NULL;
}

bool test_pop() {
  char *value = list_pop(list);

  return *value == 'H';
}

bool test_pop_multiple() {
  size_t n = strlen(string);
  for (size_t i = 0; i < n; i++) {
    list_push(list, &string[i]);
  }

  for (size_t i = 0; i < n; i++) {
    char *value = list_pop(list);

    if (*value != string[(n - 1) - i]) {
      return false;
    }
  }

  return true;
}

int main() {
  list = list_new();
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

  list_free(list, NULL);
  free(list);
}
