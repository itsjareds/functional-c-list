/* Author: Jared Klingenberger <klinge2@clemson.edu> */

#include <stdlib.h>
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

node* llist_iter(llist *l, nodeiter f) {
  node *n = l->head, *next = NULL;
  void *result = 0;

  while (n != NULL && result == 0) {
    next = n->next;
    if (!f(n))
      result = (node*)n;
    n = next;
  }

  return result;
}

node* llist_test(llist *l, void *q, nodetest t) {
  bool iter_test(node *n) {
    return !( t(q, (void*)n->data) );
  }
  return llist_iter(l, iter_test);
}

// not a true map since f can have side effects
void llist_map(llist *l, nodefunc f) {
  bool iter_true(node *n) {
    f(n);
    return TRUE;
  }
  llist_iter(l, iter_true);
}

void llist_prepend(llist *l, node *n) {
  if (l->size == 0) {
    l->head = n;
    l->tail = n;
  } else {
    n->next = l->head;
    l->head->prev = n;
    l->head = n;
  }

  l->size++;
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

void llist_insert_before(llist *l, node *after, node *n) {
  if (after) {
    if (after->prev) {
      after->prev->next = n;
      n->prev = after->prev;
    } else {
      l->head = n;
      n->prev = NULL;
    }
    n->next = after;
    after->prev = n;

    l->size++;
  }
}

void llist_insert_after(llist *l, node *before, node *n) {
  if (before) {
    if (before->next) {
      before->next->prev = n;
      n->next = before->next;
    } else {
      l->tail = n;
      n->next = NULL;
    }
    n->prev = before;
    before->next = n;

    l->size++;
  }
}

void llist_remove(llist *l, node *n) {
  if (n) {
    if (n->prev)
      n->prev->next = n->next;
    else if (l->head == n)
      l->head = n->next;

    if (n->next)
      n->next->prev = n->prev;
    else if (l->tail == n)
      l->tail = n->prev;

    l->size--;
  }
}

void llist_destroy(llist *l, nodefunc node_free) {
  void iter_remove(node *n) {
    llist_remove(l, n);
    node_free(n);
  }
  llist_map(l, iter_remove);
}

// mergesort since other sorting algs won't work on linked lists...
// runtime complexity: O(nlogn) (mergesort) + \Theta(n) (find tail) = O(nlogn)
void llist_sort(llist *l, nodetest test_compare) {
  node* merge(node *a, node *b) {
    node *ret = NULL;

    if (!a)
      return b;
    if (!b)
      return a;

    if (test_compare(a->data, b->data)) {
      ret = a;
      ret->next = merge(a->next, b);
      ret->next->prev = ret;
    } else {
      ret = b;
      ret->next = merge(a, b->next);
      ret->next->prev = ret;
    }

    return ret;
  }

  void divide(node *orig, node **left, node **right) {
    node *fast = NULL, *slow = NULL;

    if (orig == NULL || orig->next == NULL) {
      *left = orig;
      *right = NULL;
    } else {
      slow = orig;
      fast = orig->next;

      while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
          slow = slow->next;
          fast = fast->next;
        }
      }

      *left = orig;
      *right = slow->next;
      slow->next = NULL;
    }
  }

  void merge_sort(node **n) {
    node *head = *n;
    node *a = NULL, *b = NULL;

    if (!head || !head->next)
      return;

    divide(head, &a, &b);

    merge_sort(&a);
    merge_sort(&b);

    *n = merge(a, b);
    l->head = *n;
    l->head->prev = NULL;
  }



  // merge sort in O(nlogn) (according to wikipedia)
  // this clobbers l->tail
  merge_sort(&(l->head));

  // reassign l->tail in \Theta(n)
  void map_tail(node *n) {
    if (n->next == NULL)
      l->tail = n;
  }
  llist_map(l, map_tail);
}
