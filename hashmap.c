#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"
#include "list.h"
#include "vector.h"

HashMap *hash_map_new(size_t num_buckets,
                      unsigned int (*hash_function)(char *)) {
  HashMap *hash_map = malloc(sizeof(HashMap));
  hash_map->hash_function = hash_function;
  hash_map->num_buckets = num_buckets;

  vector_init(&hash_map->buckets, num_buckets, sizeof(List));

  for (size_t i = 0; i < num_buckets; i++) {
    List *list = list_new();
    vector_push(&hash_map->buckets, list);

    list_free(list);
  }

  return hash_map;
}

HashMapNode *hash_map_node_new(char *key, void *value) {
  HashMapNode *node = malloc(sizeof(HashMapNode));
  node->key = key;
  node->value = value;

  return node;
}

void hash_map_add(HashMap *hash_map, char *key, void *value) {
  size_t bucket = hash_map->hash_function(key) % hash_map->num_buckets;
  List *list = vector_get(&hash_map->buckets, bucket);
  list_push(list, hash_map_node_new(key, value));
}

void *hash_map_get(HashMap *hash_map, char *key) {
  size_t bucket = hash_map->hash_function(key) % hash_map->num_buckets;
  List *list = vector_get(&hash_map->buckets, bucket);
  ListNode *list_node = list->head;

  void *result = NULL;

  if (!list->head) {
    return NULL;
  }

  do {
    HashMapNode *node = list_node->value;
    if (strcmp(node->key, key) == 0) {
      result = node->value;
      break;
    }

    list_node = list_node->next;
  } while (list_node);

  return result;
}

void hash_map_remove(HashMap *hash_map, char *key) {
  size_t bucket = hash_map->hash_function(key) % hash_map->num_buckets;
  List *list = vector_get(&hash_map->buckets, bucket);
  ListNode *list_node = list->head;

  if (!list->head) {
    return;
  }

  ListNode *list_node_parent = NULL;
  void *result = NULL;

  do {
    HashMapNode *node = list_node->value;
    if (strcmp(node->key, key) == 0) {
      result = node->value;
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

void hash_map_free(HashMap *hash_map) {
  free(hash_map->buckets.data);
  free(hash_map);
}