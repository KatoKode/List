Just Another Armchair Programmer

List Library Written in Assembly Language with C Interface

by Jerry McIntosh

---

## List Library

---

The List Library stores objects of the same size that can be: sorted and searched; deleted from the list; and iterated through, forward or backward.

```c
void * list_alloc();
```

`list_alloc()` allocates a list structure on the Heap.  Returns an address on success, or `NULL` on failure.

---

```c
int list_add (list_t *list, void const *object);
```

`list_add()` adds whatever `object` points to to the list.  Returns 0 on success, or -1 on failure.  **NOTE:** A slot is allocated for the contents of `object` which is then copied into that slot.  Adding to a list amounts to copying the contents of an object into the next available slot in a list.

---

```c
void * list_at (list_t *list, size_t const index);
```

`list_at()` returns the address of a list member at `index` in a list, or `NULL` on failure (for instance, index out-of-bounds).

---

```c
void * list_begin (list_t *list);
```

`list_begin()` initializes the list iterator and returns the address of the first member in a list or `NULL` if list is empty.

---

```c
size_t list_count (list_t const *list);
```

`list_count()` returns the number of objects in a list.

---

```c
void * list_curr (list_t *list);
```

`list_curr()` returns the address to the current list member during iteration.

---

```c
int list_delete (list_t *list, void const *key,
    int (*find_cb) (void const *key, void const *mbr),
    void (*delete_cb) (void *mbr));
```

`list_delete()` attempts to delete a list member with a matching `key`.  Returns 0 on success, or -1 on failure.  **NOTE:** All list members after the deleted member are shifted (left) one slot to fill the gap left by a deleted member.

`find_cb()` is a user supplied function.  This function must return an integer less-than, equal-to, or greater-than zero if parameter `key` is less-than, equal-to, or greater-than the key of parameter `mbr`.

`delete_cb()` is a user supplied function.  **NOTE:** This parameter can be `NULL`.  This function is passed the list member prior to the deletion of the list member.  This function allows the user access to a list member to deal with any resources (file/socket descriptor, Heap memory, etc.) or data in same.

**NOTE:** `list_sort()` must be called prior to using `list_delete()`.  If a list can not be sorted then `list_remove()` can be used to remove a list member.

---

```c
void * list_end (list_t *);
```

`list_end()` initializes the list iterator and returns the address of the last member in a list or `NULL` if a list is empty.

---

```c
void * list_find (list_t const *list, void const *key,
    int (*find_cb) (void const *key, void const *mbr));
```

`list_find()` returns the first member in a list with a matching key, or `NULL` if no match is found.

`find_cb()` is a user supplied function.  This function must return an integer less-than, equal-to, or greater-than zero if parameter `key` is less-than, equal-to, or greater-than the key of parameter `mbr`.

---

```c
void list_free(list_t *list);
```

`list_free()` deallocates a list structure from the Heap.

---

```c
int list_init (list_t *list, size_t const size);
```

`size` of the objects that will be stored in the list.

`list_init()` must be called on a list before a list can be used.

---

```c
void * list_next (list_t *list);
```

`list_next()` increments the list iterator and returns the address of the next object in a list, or `NULL` when no successor exists.  **NOTE:** `list_begin()` must be called prior to calling this function.

---

```c
size_t list_object_size (list_t *list);
```

`list_object_size()` returns the size that was passed to `list_init()`.

---

```c
void * list_pred (list_t *list);
```

`list_pred()` returns the address of the predecessor to the current member in a list, or `NULL` when no predecessor exists.  **NOTE:**  `list_end()` must be called prior to calling this function.

---

```c
void * list_prev (list_t *list);
```

`list_prev()` decrements the list iterator and returns the address of the previous object in a list, or `NULL` when no predecessor exists.  **NOTE:** `list_end()` must be called prior to calling this function.

---

```c
void list_remove (list_t *list, void const *mbrber, void (*delete_cb) (void *));
```

`list_remove()` removes the list member pointed to by parameter `member`.  Calls `delete_cb` (if not `NULL`) prior to removing the list member.  **NOTE:** the address passed in parameter `member` must point to a list member or `list_remove()` will do nothing.

---

```c
size_t list_slot_size (list_t *list);
```

`list_slot_size()` returns the size of a slot in parament `list`.

---

```c
void list_sort (list_t *list, int (*sort_cb) (void const *mbr1, void const *mbr2));
```

`sort_cb()` is a user supplied function.  Both parameters point to list members being compared.  This function must return an integer less-than, equal-to, or greater-than zero if the key of parameter `mbr1` is less-than, equal-to, or greater-than the key of parameter `mbr2`.  If two members compare as equal, their order in the sorted array is undefined.

`list_sort()` sorts a list in ascending order according to a comparison function pointed to by `sort_cb`.

---

```c
void * list_succ (list_t *list);
```

`list_succ()` returns the address of the successor to the current member in a list, or `NULL` when no successor exists.  **NOTE:** `list_begin()` must be called prior to calling this function.

---

```c
void list_term (list_t *list);
```

`list_term()` terminates a list.

---

