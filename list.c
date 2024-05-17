#include <stdlib.h>

#include "list.h"

List *list_new() {
  List *list = malloc(sizeof(List));
  list->head = NULL;

  return list;
}

void list_push(List *list, void *value) {
  ListNode *node = malloc(sizeof(ListNode));
  node->value = value;
  node->next = list->head;

  list->head = node;
}

void *list_pop(List *list) {
  if (list->head) {
    ListNode *node = list->head;
    list->head = node->next;

    void *value = node->value;
    free(node);
    return value;
  }

  return NULL;
}

void *list_peek(List *list) { return list->head; }

void list_free(List *list) { free(list); }
