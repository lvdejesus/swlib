#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

char *string = "Hello world!";
HashMap *hash_map;

bool test_add() {
  hash_map_add(hash_map, "hello", "world");

  return strcmp(hash_map_get(hash_map, "hello"), "world") == 0;
}

bool test_remove() {
  hash_map_remove(hash_map, "hello");

  return !hash_map_get(hash_map, "hello");
}

bool test_add_multiple() {
  hash_map_add(hash_map, "foo", "bar");
  hash_map_add(hash_map, "bar", "baz");

  return (strcmp(hash_map_get(hash_map, "foo"), "bar") == 0) &&
         strcmp(hash_map_get(hash_map, "bar"), "baz") == 0;
}

bool test_remove_multiple() {
  hash_map_remove(hash_map, "foo");
  hash_map_remove(hash_map, "bar");

  return (!hash_map_get(hash_map, "foo") && !hash_map_get(hash_map, "bar"));
}

int main() {
  hash_map = hash_map_new(16, hash_function);
  char *test_names[] = {
      "test_add",
      "test_remove",
      "test_add_multiple",
      "test_remove_multiple",
  };

  bool (*tests[])() = {test_add, test_remove, test_add_multiple,
                       test_remove_multiple};

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

  hash_map_free(hash_map, NULL);
  free(hash_map);
}
