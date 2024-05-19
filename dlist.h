#ifndef dlist_H
#define dlist_H

typedef struct DListNode {
  void *value;
  struct DListNode *front;
  struct DListNode *back;
} DListNode;

typedef struct DList {
  DListNode *head;
  DListNode *tail;
} DList;

DList *dlist_new();
void dlist_init(DList *dlist);
void dlist_push(DList *dlist, void *value);
void dlist_unshift(DList *dlist, void *value);
void *dlist_pop(DList *dlist);
void *dlist_shift(DList *dlist);
void *dlist_peek(DList *dlist);
void *dlist_peek_last(DList *dlist);
void dlist_free(DList *dlist, void (*destructor)(void *));

#endif
