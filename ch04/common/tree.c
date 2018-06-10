#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "tree.h"

Tree* singleton(size_t val)
{
  Tree* t = malloc(sizeof(Tree));
  t->val = val;
  t->left = NULL;
  t->right = NULL;
  return t;
}

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
    ls.end = root_ix-1;
    rs.beg = root_ix+1;

    // Sizes are deltas from root_ix / slices size.
    size_t offset_middle = xs.beg + root_ix;
    ls.size = offset_middle - ls.beg;
    rs.size = xs.size - rs.beg;

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
    //.capacity = size,
  };
  to_list_go(t, &xs);
  return xs;
}

void print_list(List xs)
{
  if (xs.size == 0)
  {
    return;
  }

  printf("[");
  for (size_t i = 0; i < xs.size; ++i)
  {
    printf("%d", *(xs.arr+i));
    if (i+1 != xs.size)
    {
      printf(", ");
    }
  }
  printf("]\n");
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
