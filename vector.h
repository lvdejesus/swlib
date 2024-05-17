#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct Vector {
  void *data;
  size_t size;
  size_t capacity;
  size_t data_size;
} Vector;

Vector *vector_new(size_t initial_capacity, size_t data_size);
void vector_init(Vector *vector, size_t initial_capacity, size_t data_size);
void *vector_push(Vector *vector, void *value);
void *vector_get(Vector *vector, size_t index);
void *vector_pop(Vector *vector);
void vector_free(Vector *vector, void (*destructor)(void *));

#endif
