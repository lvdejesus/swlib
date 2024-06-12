#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

#include "vector.h"

typedef struct HashMapNode {
  void *key;
  void *value;
} HashMapNode;

typedef struct HashMap {
  size_t num_buckets;
  Vector buckets;
  unsigned int (*hash_function)(void *);
  int (*cmp)(void *, void *);
} HashMap;

HashMap *hash_map_new(size_t num_buckets, unsigned int (*hash_function)(void *),
                      int (*cmp)(void *, void *));
void hash_map_init(HashMap *hash_map, size_t num_buckets,
                   unsigned int (*hash_function)(void *),
                   int (*cmp)(void *, void *));
void hash_map_add(HashMap *hash_map, void *key, void *value);
void *hash_map_get(HashMap *hash_map, void *key);
void hash_map_remove(HashMap *hash_map, void *key);
void hash_map_free(HashMap *hash_map, void (*destructor)(void *));

unsigned int hash_function(char *data);

#endif
