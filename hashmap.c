#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"
#include "list.h"
#include "vector.h"

HashMap *hash_map_new(size_t num_buckets, unsigned int (*hash_function)(void *),
                      int (*cmp)(void *, void *)) {
  HashMap *hash_map = malloc(sizeof(HashMap));
  hash_map_init(hash_map, num_buckets, hash_function, cmp);

  return hash_map;
}

void hash_map_init(HashMap *hash_map, size_t num_buckets,
                   unsigned int (*hash_function)(void *),
                   int (*cmp)(void *, void *)) {
  hash_map->hash_function = hash_function;
  hash_map->num_buckets = num_buckets;
  hash_map->cmp = cmp;

  vector_init(&hash_map->buckets, num_buckets, sizeof(List));

  for (size_t i = 0; i < num_buckets; i++) {
    list_init(hash_map->buckets.data + hash_map->buckets.data_size * i);
  }

  hash_map->buckets.size = hash_map->buckets.capacity;
}

HashMapNode *hash_map_node_new(void *key, void *value) {
  HashMapNode *node = malloc(sizeof(HashMapNode));
  node->key = key;
  node->value = value;

  return node;
}

void hash_map_add(HashMap *hash_map, void *key, void *value) {
  size_t bucket = hash_map->hash_function(key) % hash_map->num_buckets;
  List *list = vector_get(&hash_map->buckets, bucket);
  list_push(list, hash_map_node_new(key, value));
}

void *hash_map_get(HashMap *hash_map, void *key) {
  size_t bucket = hash_map->hash_function(key) % hash_map->num_buckets;
  List *list = vector_get(&hash_map->buckets, bucket);
  ListNode *list_node = list->head;

  void *result = NULL;

  if (!list->head) {
    return NULL;
  }

  do {
    HashMapNode *node = list_node->value;
    if (hash_map->cmp(node->key, key) == 0) {
      result = node->value;
      break;
    }

    list_node = list_node->next;
  } while (list_node);

  return result;
}

void hash_map_remove(HashMap *hash_map, void *key) {
  size_t bucket = hash_map->hash_function(key) % hash_map->num_buckets;
  List *list = vector_get(&hash_map->buckets, bucket);
  ListNode *list_node = list->head;

  if (!list->head) {
    return;
  }

  ListNode *list_node_parent = NULL;
  HashMapNode *node = NULL;

  do {
    node = list_node->value;
    if (hash_map->cmp(node->key, key) == 0) {
      break;
    }

    list_node_parent = list_node;
    list_node = list_node->next;
  } while (list_node);

  if (list_node_parent) {
    list_node_parent->next = list_node->next;

    free(list_node);
  } else {
    // only one element
    HashMapNode *node = list_pop(list);
    free(node);
  }
}

void hash_map_free(HashMap *hash_map, void (*destructor)(void *)) {
  if (destructor != NULL) {
    for (size_t i = 0; i < hash_map->num_buckets; i++) {
      List *bucket = vector_get(&hash_map->buckets, i);
      list_free(bucket, destructor);
    }
  }

  free(hash_map->buckets.data);
}

// FNV-1A from https://softwareengineering.stackexchange.com/a/145633
unsigned int hash_function(char *data) {
  unsigned int hash = 2166136261;
  for (int i = 0; data[i] != 0; i++) {
    hash = hash ^ data[i];
    hash = hash * 16777619;
  }

  return hash;
}
