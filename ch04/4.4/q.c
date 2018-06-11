#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "../common/tree.h"

Tree* example_tree_gen(int n)
{
  if (n < 1) {
    return NULL;
  }

  int* arr = malloc(sizeof(int) * n);
  for (int i = 1; i <= n; ++i) {
    arr[i-1] = i;
  }

  Slice slc = {
    .arr = arr,
    .beg = 0,
    .end = n-1,
    .size = n,
    .capacity = n,
  };

  Tree* p = from_dist_asc_list(slc);
  free(arr);
  return p;
}

// A tree `t' is balanced iff no sub-trees differ in height by more than one.
bool is_balanced(Tree* t)
{
  if (t == NULL) {
    return true;
  }
  long lh = tree_height(t->left);
  long rh = tree_height(t->right);
  lh = lh < 0 ? 0 : lh;
  rh = rh < 0 ? 0 : rh;
  bool curr_bal;
  if (lh > rh) {
    curr_bal = (lh-rh) <= 1;
  } else {
    curr_bal = (rh-lh) <= 1;
  }
  return curr_bal && is_balanced(t->left) && is_balanced(t->right);
}

int main(void)
{
  Tree* t = example_tree_gen(8);

  // Add to it in a balanced way (next avail. slot).
  Tree* curr = NULL;
  Tree* tmp  = NULL;
  curr = t;
  while (curr->left != NULL && curr->val != 2) {
    curr = curr->left;
  }
  tmp = singleton(42);
  curr->right = tmp;
  assert(is_balanced(t) == true);
  free(tmp);
  tmp = NULL;
  curr->right = NULL;

  // Make it lop-sided to the left.
  curr = t;
  while (curr->left != NULL) {
    curr = curr->left;
  }
  tmp = singleton(42);
  curr->left = tmp;
  assert(is_balanced(t) == false);
  free(tmp);
  tmp = NULL;
  curr->left = NULL;

  free_tree(t);
  t = NULL;

  // Verify `from_dist_asc_list'
  int ul = 100;
  for (int i = 0; i < ul; ++i) {
    Tree* k = example_tree_gen(i);
    assert(is_balanced(k) == true);
    free_tree(k);
  }

}
