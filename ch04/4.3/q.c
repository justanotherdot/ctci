#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "../common/tree.h"

#define FALSE 0
#define TRUE 1

Tree* example_tree() {
  int arr01[] = { 1, 2, 3, 4, 5 };
  Slice s01 = {
    .arr = arr01,
    .beg = 0,
    .end = 4,
    .size = 5,
  };
  return from_dist_asc_list(s01);
}

// START INTEGER QUEUE

// A dyanmically sized integer queue.
struct int_queue_t {
  int* arr;
  size_t size;
  size_t capacity;
  size_t front;
  size_t back; // as `size' != `back'
};
typedef struct int_queue_t IntQueue;

IntQueue empty_int_queue()
{
  IntQueue iq = {
    .arr = NULL,
    .size = 0,
    .capacity = 0,
    .front = 0,
    .back = 0,
  };
  return iq;
}

// XXX TMP
void print_int_queue(IntQueue* iq);

void resize_int_queue(IntQueue* iq, size_t new_size)
{
  assert(new_size > 0);

  if (iq->arr != NULL) {
    // XXX Could also malloc and memcpy.
    int* tmp = iq->arr;
    iq->arr = realloc(iq->arr, sizeof(int) * new_size);

    if (iq->arr == NULL) {
      fprintf(stderr, "WARNING: Failed realloc in `resize_int_queue'\n");
      iq->arr = tmp;
    }
  } else {
    iq->arr = malloc(sizeof(int) * new_size);
    assert(iq->arr != NULL);
  }
  iq->capacity = new_size;
}

// Assumes you will grow before enqueuing.
void grow_int_queue(IntQueue* iq)
{
  if (iq->arr == NULL) {
    // Init. queue if we're fresh.
    resize_int_queue(iq, 1);
  } else if ((iq->size+1) >= iq->capacity) {
    // Double queue if we're about to hit cap.
    resize_int_queue(iq, iq->capacity*2);
  }
}

// Assumes you will shrink after dequeuing.
void shrink_int_queue(IntQueue* iq)
{
  if (iq == NULL) {
    return;
  }

  if (iq->size == 0) {
    // Free the backing store.
    free(iq->arr);
    iq->arr = NULL;
    iq->capacity = 0;
    iq->front = 0;
    iq->back = 0;
  } else {
    // FIXME This should be generalised.
    // It should also more intelligently shrink in an amortised manner.
    int* old = iq->arr;
    size_t sz = iq->back - iq->front;
    iq->arr = malloc(sizeof(int) * sz);
    size_t j = iq->front;
    for (size_t i = 0; i < iq->back; ++i, ++j) {
      iq->arr[i] = old[j];
    }
    iq->capacity = iq->size;
    iq->front = 0;
    iq->back = sz;
    iq->size = sz;
    free(old);
  }
}

void enqueue_int(int v, IntQueue* iq)
{
  grow_int_queue(iq);
  iq->arr[iq->back] = v;
  iq->size += 1;
  if (iq->size > 0) {
    iq->back += 1;
  }
}

int dequeue_int(IntQueue* iq)
{
  assert(iq != NULL);
  assert(iq->arr != NULL);
  assert(iq->capacity > 0);
  assert(iq->front < iq->back);

  // XXX The following line makes this a stack!
  /*int rv = iq->arr[iq->size];*/
  int rv = iq->arr[iq->front];
  iq->front += 1;
  iq->size -= 1;

  shrink_int_queue(iq);
  return rv;
}

void free_int_queue(IntQueue* iq)
{
  if (iq != NULL && iq->arr != NULL) {
    free(iq->arr);
  }
}

char* int_queue_array_to_string(IntQueue* iq, char debug) {
  if (iq == NULL || iq->size == 0) {
    return NULL;
  }

  // FIXME
  // Flat scheme to avoid complicated checks for digit lenghts.
  size_t str_size = 4096;

  char* str = malloc(str_size);
  size_t sl = 0;
  size_t bottom = debug ? 0 : iq->front;
  size_t top = debug ? iq->capacity : iq->size;
  for (size_t i = bottom; i < top; ++i) {
    if (i == bottom) {
      sl += sprintf(str, "[ ");
    }

    if (i >= iq->front && i < iq->back) {
      sl += sprintf(str + sl, "%d", iq->arr[i]);
    } else {
      sl += sprintf(str + sl, "X");
    }

    if ((i+1) != top) {
      sl += sprintf(str + sl, ", ");
    }
    if ((i+1) == top) {
      sl += sprintf(str + sl, " ]");
    }
  }

  return str;
}

void print_int_queue(IntQueue* iq)
{
  if (iq == NULL) {
    return;
  }

  char* str = int_queue_array_to_string(iq, FALSE);
  printf("%s\n", str);
  free(str);
}

void debug_int_queue(IntQueue* iq)
{
  char* arr_str = int_queue_array_to_string(iq, TRUE);
  printf("IntQueue {\n");
  printf("  arr: %s,\n", arr_str);
  printf("  size: %ld\n", iq->size);
  printf("  capacity: %ld\n", iq->capacity);
  printf("  front: %ld\n", iq->front);
  printf("  back: %ld\n", iq->back);
  printf("}\n");
  free(arr_str);
}

char is_empty_int_queue(IntQueue* iq)
{
  return iq->arr == NULL;
}

char is_member_of_int_queue(int needle, IntQueue* iq)
{
  char rv = FALSE;
  for (size_t i = iq->front; i < iq->back; ++i) {
    if (iq->arr[i] == needle) {
      rv = TRUE;
    }
  }
  return rv;
}

// END INTEGER QUEUE

// We cheat a bit here.
// For starters I'm not going to worry about transmuting the levels into linked
// lists but rather arrays as those can be trivially converted into linked-lists.
//
// This also has a serious flow in that it assumes that all items of the tree
// are unique, which should technically be true but may not be if the tree is
// malformed.
void tree_to_lists(Tree* t)
{
  if (t == NULL) {
    return;
  }

  IntQueue seen = empty_int_queue();
  IntQueue q = empty_int_queue();
  enqueue_int(t->val, &q);

  while (!is_empty_int_queue(&q)) {
    int curr = dequeue_int(&q);
    if (is_member_of_int_queue(curr, &q)) {
      continue;
    }
    enqueue_int(curr, &seen);
  }
}

int main(void)
{
  Tree* t = example_tree();

  List xs = to_list(t);
  print_list(xs);

  free_tree(t);
  free_list(xs);
}
