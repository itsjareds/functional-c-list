functional-list
===============
### Author

* Jared Klingenberger <klinge2@clemson.edu>

This program is a C library that implements a doubly-linked list. As an added
twist, methods to interact with the list mimic functional programming style. For
example, you can map a function over the entire list with a function passed as
a parameter.

Common methods
==============
* `void map(llist *l, nodefunc f)`
* `void* llist_iter(llist *l, nodeiter f)`
* `void* llist_test(llist *l, void *q, nodetest t)`
* `void* llist_find(llist *l, void *data, nodetest equals)`

