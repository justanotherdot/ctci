#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct tree_t Tree;
struct tree_t
{
  size_t val;
  Tree* left;
  Tree* right;
};

typedef struct slice_t Slice;
typedef Slice List;
struct slice_t
{
  int* arr;

  size_t beg;
  size_t end;

  size_t size;
  //size_t capacity; // unused, but normally slices would have this.
};

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

int main(void)
{

  Tree* t;

  int* arr00 = NULL;
  Slice s00 = {
    .arr = arr00,
    .beg = 0,
    .end = 0,
    .size = 0,
  };
  t = from_dist_asc_list(s00);
  assert(t == NULL); // since we just see a newline.
  print_tree(t);
  printf("of size %ld", tree_size(t));
  printf("\n");

  int arr01[] = { 1 };
  Slice s01 = {
    .arr = arr01,
    .beg = 0,
    .end = 0,
    .size = 1,
  };
  t = from_dist_asc_list(s01);
  print_tree(t);
  printf("of size %ld", tree_size(t));
  printf("\n");

  int arr02[] = { 1, 2 };
  Slice s02 = {
    .arr = arr02,
    .beg = 0,
    .end = 2,
    .size = 2,
  };
  t = from_dist_asc_list(s02);
  print_tree(t);
  printf("of size %ld", tree_size(t));
  printf("\n");

  int arr03[] = { 1, 2, 3 };
  Slice s03 = {
    .arr = arr03,
    .beg = 0,
    .end = 2,
    .size = 3,
  };
  t = from_dist_asc_list(s03);
  print_tree(t);
  printf("of size %ld", tree_size(t));
  printf("\n");

  int arr04[] = { 1, 2, 3, 4 };
  Slice s04 = {
    .arr = arr04,
    .beg = 0,
    .end = 3,
    .size = 4,
  };
  t = from_dist_asc_list(s04);
  print_tree(t);
  printf("of size %ld", tree_size(t));
  printf("\n");

  int arr05[] = { 1, 2, 3, 4, 5 };
  Slice s05 = {
    .arr = arr05,
    .beg = 0,
    .end = 4,
    .size = 5,
  };
  t = from_dist_asc_list(s05);
  print_tree(t);
  printf("of size %ld", tree_size(t));
  printf("\n");

  List xs = to_list(t);
  print_list(xs);

}
