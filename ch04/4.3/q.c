#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "../common/tree.h"

#define FALSE 0
#define TRUE 1

Tree* example_tree() {
  int arr01[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
  Slice s01 = {
    .arr = arr01,
    .beg = 0,
    .end = 7,
    .size = 8,
    .capacity = 8,
  };
  return from_dist_asc_list(s01);
}

// START INTEGER QUEUE

// A dyanmically sized integer queue.
struct queue_t {
  void** arr;
  size_t size;
  size_t capacity;
  size_t front;
  size_t back; // as `size' != `back'
};
typedef struct queue_t Queue;

Queue* empty_queue()
{
  Queue* iq = malloc(sizeof(Queue));
  iq->arr = NULL;
  iq->size = 0;
  iq->capacity = 0;
  iq->front = 0;
  iq->back = 0;
  return iq;
}

// XXX TMP
void print_queue(Queue* iq);
void debug_queue(Queue* iq);

void resize_queue(Queue* iq, size_t new_size)
{
  assert(new_size > 0);

  if (iq->arr != NULL) {
    void** old = iq->arr;
    iq->arr = malloc(sizeof(void*) * new_size);
    assert(iq->arr != NULL);

    size_t j = 0;
    for (size_t i = iq->front; i < iq->back; ++i) {
      iq->arr[j] = old[i];
      j += 1;
    }

    free(old);
  } else {
    // Init.
    iq->arr = malloc(sizeof(void*) * new_size);
    assert(iq->arr != NULL);
  }
  iq->capacity = new_size;
}

// Assumes you will grow before enqueuing.
void grow_queue(Queue* iq)
{
  if (iq->arr == NULL) {
    // Init. queue if we're fresh.
    resize_queue(iq, 1);
  } else if ((iq->size+1) >= iq->capacity) {
    // Double queue if we're about to hit cap.
    resize_queue(iq, iq->capacity*2);
  }
}

// Assumes you will shrink after dequeuing.
void shrink_queue(Queue* iq)
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
    void** old = iq->arr;
    size_t sz = iq->back - iq->front;
    iq->arr = malloc(sizeof(void*) * sz);
    size_t j = 0;
    for (size_t i = iq->front; i < iq->back; ++i, ++j) {
      iq->arr[j] = old[i];
    }
    iq->capacity = iq->size;
    iq->front = 0;
    iq->back = sz;
    iq->size = sz;
    free(old);
  }
}

void enqueue(void* v, Queue* iq)
{
  grow_queue(iq);
  iq->arr[iq->back] = v;
  iq->size += 1;
  if (iq->size > 0) {
    iq->back += 1;
  }
}

void* dequeue(Queue* iq)
{
  assert(iq != NULL);
  assert(iq->arr != NULL);
  assert(iq->capacity > 0);
  assert(iq->front < iq->back);

  // XXX The following line makes this a stack!
  /*int rv = iq->arr[iq->size];*/
  void* rv = iq->arr[iq->front];
  iq->front += 1;
  iq->size -= 1;

  shrink_queue(iq);
  return rv;
}

void free_queue(Queue* iq)
{
  if (iq != NULL && iq->arr != NULL) {
    free(iq->arr);
  }
  free(iq);
}

char* queue_array_to_string(Queue* iq, char debug) {
  if (iq == NULL || iq->capacity == 0) {
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
      sl += sprintf(str + sl, "%p", iq->arr[i]);
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

void print_queue(Queue* iq)
{
  if (iq == NULL) {
    return;
  }

  char* str = queue_array_to_string(iq, FALSE);
  printf("%s\n", str);
  free(str);
}

void debug_queue(Queue* iq)
{
  char* arr_str = queue_array_to_string(iq, TRUE);
  printf("Queue {\n");
  printf("  arr: %s,\n", arr_str);
  printf("  size: %ld\n", iq->size);
  printf("  capacity: %ld\n", iq->capacity);
  printf("  front: %ld\n", iq->front);
  printf("  back: %ld\n", iq->back);
  printf("}\n");
  free(arr_str);
}

char is_empty_queue(Queue* iq)
{
  return iq->arr == NULL;
}

char is_member_of_queue(void* needle, Queue* iq)
{
  char rv = FALSE;
  for (size_t i = iq->front; i < iq->back; ++i) {
    if (iq->arr[i] == needle) {
      rv = TRUE;
    }
  }
  return rv;
}

struct depth_node_t {
  void* node;
  size_t depth;
};
typedef struct depth_node_t DepthNode;

DepthNode* singleton_dn(void* node, size_t depth)
{
  DepthNode* dn = malloc(sizeof(DepthNode));
  dn->node = node;
  dn->depth = depth;
  return dn;
}
void free_dn(DepthNode* dn)
{
  free(dn);
}

// END INTEGER QUEUE

// We cheat a bit here.
// For starters I'm not going to worry about transmuting the levels into linked
// lists but rather arrays as those can be trivially converted into linked-lists.
//
// This also has a serious flow in that it assumes that all items of the tree
// are unique, which should technically be true but may not be if the tree is
// malformed.
Queue** tree_to_lists(Tree* t)
{
  if (t == NULL) {
    return NULL;
  }

  Queue* seen = empty_queue();
  Queue* q = empty_queue();
  enqueue(singleton_dn(t, 0), q);

  int num_lists = tree_height(t) + 1;

  // ptr to queues
  // Law: each layer must have as many items as it's (index+1).
  Queue** layers = malloc(num_lists * sizeof(Queue*));
  for (int i = 0; i < num_lists; ++i) {
    layers[i] = empty_queue();
  }

  while (!is_empty_queue(q)) {
    DepthNode* curr_dn = dequeue(q);
    Tree* curr = curr_dn->node;
    if (curr == NULL || is_member_of_queue(curr_dn, seen)) {
      continue;
    }

    enqueue(curr_dn, layers[curr_dn->depth]);

    double ul = pow(2, curr_dn->depth+1);
    assert(layers[curr_dn->depth]->size <= ul);

    enqueue(curr_dn, seen);
    if (curr->left != NULL) {
      enqueue(singleton_dn(curr->left, curr_dn->depth+1), q);
    }
    if (curr->right != NULL) {
      enqueue(singleton_dn(curr->right, curr_dn->depth+1), q);
    }
  }

  free_queue(q);
  free_queue(seen);

  return layers;
}

int main(void)
{
  Tree* t = example_tree();

  List xs = to_list(t);
  print_list(xs);

  Queue** layers = tree_to_lists(t);

  for (size_t i = 0; i < (size_t)tree_height(t) + 1; ++i) {
    Queue* q = layers[i];
    while (!is_empty_queue(q)) {
      DepthNode* x = dequeue(q);
      Tree* y = x->node;
      printf("Queue at depth %ld stored the value %ld\n", x->depth, y->val);

      free_dn(x);
    }
    free_queue(q);
  }

  free_tree(t);
  free_list(xs);
  free(layers);
}
