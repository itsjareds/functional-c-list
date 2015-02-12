/* Author: Jared Klingenberger <klinge2@clemson.edu> */

    #include <stdio.h>
    #include <stdlib.h>
    #include "llist.h"

    void iter_print(node *n) {
      printf("value: %d\n", *(int*)n->data);
    }

    bool test_equals(void *a, void *b) {
      return *(int*)a == *(int*)b;
    }

    void node_free(node *n) { free(n); }

    void *llist_find(llist *l, void *data) {
      return llist_test(l, data, test_equals);
    }

    void llist_print(llist *l);
    bool find_and_remove(llist *l, int value);
    node *alloc_node(int *data);

    int main() {
      llist *l = malloc(sizeof(llist));
      llist_init(l);

      int x = 4, y = 8;

      printf("Adding some...\n");

      llist_append(l, alloc_node(&x));
      llist_append(l, alloc_node(&y));
      llist_append(l, alloc_node(&x));
      llist_append(l, alloc_node(&y));
      llist_append(l, alloc_node(&x));
      llist_append(l, alloc_node(&y));

      llist_print(l);

      printf("Removing some...\n");

      int q = x, p = y+1;
      if (!find_and_remove(l, q))
        printf("Value %d not present in list\n", q);
      if (!find_and_remove(l, p))
        printf("Value %d not present in list\n", p);

      void iter_remove(node *n) {
        iter_print(n);
        llist_remove(l, n);
        node_free(n);
      }
      llist_map(l, iter_remove);

      llist_print(l);

      llist_destroy(l, node_free);
      free(l);

      return 0;
    }

    void llist_print(llist *l) {
      llist_map(l, iter_print);
    }

    bool find_and_remove(llist *l, int value) {
      node *n = llist_find(l, &value);
      if (n) {
        llist_remove(l, n);
        node_free(n);
      }
      return (n != NULL);
    }

    node *alloc_node(int *data) {
      node *n = malloc(sizeof(node));
      llist_node_init(n);
      n->data = data;
      return n;
    }
