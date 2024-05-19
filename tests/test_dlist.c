#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

char *string = "Hello world!";
DList *dlist;

bool test_push() {
  dlist_push(dlist, &string[0]);
  char *value = dlist_peek(dlist);

  return value != NULL;
}

bool test_pop() {
  char *value = dlist_pop(dlist);

  return *value == 'H';
}

bool test_pop_multiple() {
  size_t n = strlen(string);
  for (size_t i = 0; i < n; i++) {
    dlist_push(dlist, &string[i]);
  }

  for (size_t i = 0; i < n; i++) {
    char *value = dlist_pop(dlist);

    if (*value != string[(n - 1) - i]) {
      return false;
    }
  }

  return true;
}

int main() {
  dlist = dlist_new();
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

  dlist_free(dlist, NULL);
}
