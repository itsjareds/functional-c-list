#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "llist.h"

void llist_init(llist *l) {
  l->head = NULL;
  l->tail = NULL;
  l->size = 0;
}

void llist_node_init(node *n) {
  n->data = NULL;
  n->next = NULL;
  n->prev = NULL;
}

void *llist_iter(llist *l, nodeiter f) {
  node *n = l->head, *next = NULL;
  intptr_t result = 0;

  while (n != NULL && result == 0) {
    next = n->next;
    if (!f(n))
      result = (intptr_t)n;
    n = next;
  }

  return (void*)result;
}

void *llist_test(llist *l, void *q, nodetest t) {
  bool iter_test(node *n) {
    return !( t((void*)n->data, q) );
  }
  return llist_iter(l, iter_test);
}

// not a true map since f can have side effects
void map(llist *l, nodefunc f) {
  bool iter_true(node *n) {
    f(n);
    return TRUE;
  }
  llist_iter(l, iter_true);
}

void *llist_find(llist *l, void *data, nodetest equals) {
  return llist_test(l, data, equals);
}

void llist_append(llist *l, node *n) {
  if (l->size == 0) {
    l->head = n;
    l->tail = n;
  } else {
    n->prev = l->tail;
    l->tail->next = n;
    l->tail = n;
  }

  l->size++;
}

void llist_remove(llist *l, node *n) {
  if (n) {
    if (n->prev)
      n->prev->next = n->next;
    else
      l->head = n->next;

    if (n->next)
      n->next->prev = n->prev;
    else
      l->tail = n->prev;

    l->size--;
  }
}

void llist_destroy(llist *l, nodefunc node_free) {
  void iter_remove(node *n) {
    llist_remove(l, n);
    node_free(n);
  }
  map(l, iter_remove);
}
