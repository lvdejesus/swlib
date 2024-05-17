#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

Vector *vector_new(size_t initial_capacity, size_t data_size) {
  Vector *vector = malloc(sizeof(Vector));

  vector->data = malloc(initial_capacity * data_size);
  vector->size = 0;
  vector->capacity = initial_capacity;
  vector->data_size = data_size;

  return vector;
}

void vector_push(Vector *vector, void *value) {
  if (vector->size == vector->capacity) {
    vector->capacity *= 2;
    vector->data = realloc(vector->data, vector->capacity * vector->data_size);
  }

  memcpy(vector->data + vector->size * vector->data_size, value,
         vector->data_size);
  vector->size += 1;
}

void *vector_get(Vector *vector, size_t index) {
  if (index >= vector->size) {
    printf("Out of bounds\n");
    return NULL;
  }

  return vector->data + index * vector->data_size;
}

void *vector_pop(Vector *vector) {
  if (vector->size == 0) {
    printf("Attempted pop on an empty vector");
    return NULL;
  }

  void *value = vector->data + (vector->size - 1) * vector->data_size;
  vector->size -= 1;

  if (vector->size * 4 < vector->capacity) {
    vector->capacity /= 2;
  }

  return value;
}

void vector_free(Vector *vector) {
  free(vector->data);
  free(vector);
}
