#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "tree.h"

#define TRUE 1
#define FALSE 0

Tree* singleton(size_t val)
{
  Tree* t = malloc(sizeof(Tree));
  t->val = val;
  t->left = NULL;
  t->right = NULL;
  return t;
}

// FIXME I believe to_list to be broken.
Tree* from_dist_asc_list(Slice xs)
{
  if (xs.size == 0)
  {
    return NULL;
  }
  else if (xs.size == 1)
  {
    Tree* rv = singleton(xs.arr[xs.beg]);
    return rv;
  }
  else // n > 2
  {
    size_t root_ix = floor(xs.size/2);
    Tree* root = singleton(xs.arr[xs.beg + root_ix]);

    // Copies (shallow).
    Slice ls = xs;
    Slice rs = xs;

    // Ignore the middle element.
    ls.end = xs.beg+root_ix-1;
    rs.beg = xs.beg+root_ix+1;

    ls.size = (ls.beg <= ls.end) ? ls.end - ls.beg + 1 : 0;
    rs.size = (rs.beg <= rs.end) ? rs.end - rs.beg + 1 : 0;

    root->left = from_dist_asc_list(ls);
    root->right = from_dist_asc_list(rs);
    return root;
  }
}

size_t tree_size(Tree* t)
{
  if (t == NULL)
  {
    return 0;
  }

  size_t size = 0;
  size += tree_size(t->left);
  size += tree_size(t->right);
  return size+1;
}

// FIXME this won't work. The ixes aren't in the correct places for them to lay
// out properly.
void to_list_go(Tree* t, List* xs)
{
  if (t == NULL)
    return;
  to_list_go(t->left, xs);
  // Using `xs->size' is fine because it's not yet incremented.
  *(xs->arr+xs->size) = t->val;
  xs->size += 1;
  to_list_go(t->right, xs);
}

List to_list(Tree* t)
{
  size_t size = tree_size(t);
  int* buf = malloc(size*sizeof(int));
  List xs = {
    .arr = buf,
    .size = 0,
    .beg = 0,
    .end = size-1,
    .capacity = size,
  };
  to_list_go(t, &xs);
  return xs;
}

char* list_to_str(List xs, char virt_arr)
{
  if (xs.capacity == 0)
  {
    return NULL;
  }

  size_t sz = 4096;
  size_t len = 0;
  char* str = malloc(sz);

  size_t beg = virt_arr ? xs.beg : 0;
  size_t end = virt_arr ? xs.end+1 : xs.capacity;

  len += sprintf(str, "[");
  for (size_t i = beg; i < end; ++i)
  {
    len += sprintf(str + len, "%d", *(xs.arr+i));
    if (i+1 != end)
    {
      len += sprintf(str + len, ", ");
    }
  }
  len += sprintf(str + len, "]");
  return str;
}

void print_list(List xs)
{
  if (xs.size == 0)
  {
    return;
  }

  char* arr_str = list_to_str(xs, TRUE);
  printf("%s\n", arr_str);
  free(arr_str);
}

void debug_slice(Slice* xs)
{
  if (xs == NULL) {
    return;
  }

  char* arr_str = list_to_str(*xs, FALSE);
  char* virt_arr_str = list_to_str(*xs, TRUE);
  printf("Slice {\n");
  printf("  arr: %s,\n", arr_str);
  printf("  (virt. arr): %s,\n", virt_arr_str);
  printf("  beg: %ld\n", xs->beg);
  printf("  end: %ld\n", xs->end);
  printf("  size: %ld\n", xs->size);
  printf("  capacity: %ld\n", xs->capacity);
  printf("}\n");
  free(arr_str);
  free(virt_arr_str);
}

// TODO do in order conversion to list.
// Then we can just printfthe list.
void print_tree(Tree* t)
{
  if (t == NULL)
  {
    return;
  }

  print_tree(t->left);
  printf("%ld ", t->val);
  print_tree(t->right);
}

void free_tree(Tree* t)
{
  if (t == NULL)
  {
    return;
  }

  free_tree(t->left);
  free_tree(t->right);
  free(t);
}

void free_list(List xs)
{
  free(xs.arr);
}
