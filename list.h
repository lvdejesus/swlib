#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
  void *value;
  struct ListNode *next;
} ListNode;

typedef struct List {
  ListNode *head;
} List;

List *list_new();
void list_push(List *list, void *value);
void *list_pop(List *list);
void *list_peek(List *list);
void list_free(List *list);

#endif
