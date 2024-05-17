#ifndef DEQUE_H
#define DEQUE_H

typedef struct DequeNode {
  void *value;
  struct DequeNode *next;
  struct DequeNode *prev;
} DequeNode;

typedef struct Deque {
  DequeNode *head;
  DequeNode *tail;
} Deque;

Deque *deque_new();
void deque_push(Deque *deque, void *value);
void deque_unshift(Deque *deque, void *value);
void *deque_pop(Deque *deque);
void *deque_shift(Deque *deque);
void *deque_peek(Deque *deque);
void deque_free(Deque *deque);

#endif
