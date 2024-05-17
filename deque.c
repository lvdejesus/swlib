#include <stdlib.h>

#include "deque.h"

Deque *deque_new() {
  Deque *deque = malloc(sizeof(Deque));
  deque->head = NULL;
  deque->tail = NULL;

  return deque;
}

void deque_push(Deque *deque, void *value) {
  DequeNode *node = malloc(sizeof(DequeNode));
  node->value = value;
  node->back = deque->head;
  node->front = NULL;

  if (deque->head == NULL) {
    deque->tail = node;
  } else {
    deque->head->front = node;
  }
  deque->head = node;
}

void deque_unshift(Deque *deque, void *value) {
  DequeNode *node = malloc(sizeof(DequeNode));
  node->value = value;
  node->back = NULL;
  node->front = deque->tail;

  if (deque->tail == NULL) {
    deque->head = node;
  } else {
    deque->tail->back = node;
  }
  deque->tail = node;
}

void *deque_pop(Deque *deque) {
  if (deque->head) {
    DequeNode *node = deque->head;
    deque->head = node->back;

    if (deque->head == NULL) {
      deque->tail = NULL;
    }

    void *value = node->value;
    free(node);
    return value;
  }

  return NULL;
}

void *deque_shift(Deque *deque) {
  if (deque->tail) {
    DequeNode *node = deque->tail;
    deque->tail = node->front;

    if (deque->tail == NULL) {
      deque->head = NULL;
    }

    void *value = node->value;
    free(node);
    return value;
  }

  return NULL;
}

void *deque_peek_last(Deque *deque) {
  if (deque->tail) {
    return deque->tail->value;
  }

  return NULL;
}

void *deque_peek(Deque *deque) {
  if (deque->head) {
    return deque->head->value;
  }

  return NULL;
}

void deque_free(Deque *deque, void (*destructor)(void *)) {
  if (destructor != NULL) {
    for (DequeNode *curr = deque->head; deque->head != NULL;
         curr = curr->back) {
      destructor(curr->value);
    }
  }
}
