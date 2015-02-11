/* Author: Jared Klingenberger <klinge2@clemson.edu> */

#ifndef LLIST_H
#define LLIST_H


#include <stdint.h>

/* Fields */
typedef struct _node {
  struct _node *next, *prev;
  void *data;
} node;

typedef struct {
  node *head, *tail;
  size_t size;
} llist;

typedef enum {FALSE, TRUE} bool;

typedef void (*nodefunc)(node *);
typedef bool (*nodeiter)(node *);
typedef bool (*nodetest)(void *, void *);

/* Methods */
void llist_init(llist *l);
void llist_node_init(node *n);

void map(llist *l, nodefunc f);
void *llist_iter(llist *l, nodeiter f);
void *llist_test(llist *l, void *q, nodetest t);
void *llist_find(llist *l, void *data, nodetest equals);

void llist_append(llist *l, node *n);
void llist_remove(llist *l, node *n);
void llist_destroy(llist *l, nodefunc node_free);


#endif
