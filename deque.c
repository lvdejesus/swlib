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

  // if there is a first node,
  if (deque->head) {
    // the node before it is the new node.
    deque->head->prev = node;
  } else {
    // the only node should be head and rear
    deque->tail = node;
  }

  // first node becomes second node
  node->next = deque->head;

  // new node becomes first node,
  deque->head = node;
}

void deque_unshift(Deque *deque, void *value) {
  DequeNode *node = malloc(sizeof(DequeNode));
  node->value = value;

  // if there is a last node,
  if (deque->tail) {
    // the node after it is the new node.
    deque->head->next = node;
  } else {
    // the only node should be head and rear
    deque->head = node;
  }

  // last node becomes second last node
  node->prev = deque->tail;

  // new node becomes last node,
  deque->tail = node;
}

void *deque_pop(Deque *deque) {
  if (deque->head) {
    DequeNode *node = deque->head;

    // second node becomes first node,
    deque->head = node->next;

    if (!deque->head) {
      // if first node doesn't exist,
      // then there is no last node
      deque->tail = NULL;
    } else {
      // second node becomes first node,
      // and will have nothing before it
      deque->head->prev = NULL;
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

    // second to last node becomes last node,
    deque->tail = node->prev;

    if (!deque->tail) {
      // if last node doesn't exist,
      // then there is no first node
      deque->head = NULL;
    } else {
      // second to last node becomes last node,
      // and will have nothing after it
      deque->tail->next = NULL;
    }

    void *value = node->value;
    free(node);
    return value;
  }

  return NULL;
}

void *deque_peek(Deque *deque) { return deque->head; }

void deque_free(Deque *deque) { free(deque); }
