#include <stdlib.h>

#include "dlist.h"

DList *dlist_new() {
  DList *dlist = malloc(sizeof(DList));
  dlist_init(dlist);

  return dlist;
}

void dlist_init(DList *dlist) {
  dlist->head = NULL;
  dlist->tail = NULL;
}

void dlist_push(DList *dlist, void *value) {
  DListNode *node = malloc(sizeof(DListNode));
  node->value = value;
  node->back = dlist->head;
  node->front = NULL;

  if (dlist->head == NULL) {
    dlist->tail = node;
  } else {
    dlist->head->front = node;
  }
  dlist->head = node;
}

void dlist_unshift(DList *dlist, void *value) {
  DListNode *node = malloc(sizeof(DListNode));
  node->value = value;
  node->back = NULL;
  node->front = dlist->tail;

  if (dlist->tail == NULL) {
    dlist->head = node;
  } else {
    dlist->tail->back = node;
  }
  dlist->tail = node;
}

void *dlist_pop(DList *dlist) {
  if (dlist->head) {
    DListNode *node = dlist->head;
    dlist->head = node->back;

    if (dlist->head == NULL) {
      dlist->tail = NULL;
    }

    void *value = node->value;
    free(node);
    return value;
  }

  return NULL;
}

void *dlist_shift(DList *dlist) {
  if (dlist->tail) {
    DListNode *node = dlist->tail;
    dlist->tail = node->front;

    if (dlist->tail == NULL) {
      dlist->head = NULL;
    }

    void *value = node->value;
    free(node);
    return value;
  }

  return NULL;
}

void *dlist_peek_last(DList *dlist) {
  if (dlist->tail) {
    return dlist->tail->value;
  }

  return NULL;
}

void *dlist_peek(DList *dlist) {
  if (dlist->head) {
    return dlist->head->value;
  }

  return NULL;
}

void dlist_free(DList *dlist, void (*destructor)(void *)) {
  if (destructor != NULL) {
    DListNode *curr = dlist->head;

    if (curr == NULL) {
      return;
    }

    while (curr != NULL) {
      destructor(curr->value);

      DListNode *temp = curr->back;
      free(curr);
      curr = temp;
    }
  }
}
