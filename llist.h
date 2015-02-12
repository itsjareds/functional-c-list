/* Author: Jared Klingenberger <klinge2@clemson.edu> */

#ifndef LLIST_H
#define LLIST_H


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

void llist_map(llist *l, nodefunc f);
node* llist_iter(llist *l, nodeiter f);
node* llist_test(llist *l, void *q, nodetest t);

void llist_prepend(llist *l, node *n);
void llist_append(llist *l, node *n);
void llist_insert_before(llist *l, node *after, node *n);
void llist_insert_after(llist *l, node *before, node *n);
void llist_remove(llist *l, node *n);
void llist_destroy(llist *l, nodefunc node_free);

void llist_sort(llist *l, nodetest test_compare);


#endif
