#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "../common/tree.h"

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

// A tree `t' is balanced iff no sub-trees differ in height by more than one.
bool is_balanced(Tree* t) {
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
  Tree* t = example_tree();

  Tree* curr = NULL;
  curr = t;
  while (curr->left != NULL && curr->left->val != 2) {
    curr = curr->left;
  }
  curr->right = singleton(42);
  assert(is_balanced(t) == true);

  curr = t;
  while (curr->left != NULL) {
    curr = curr->left;
  }
  curr->left = singleton(42);
  assert(is_balanced(t) == false);

  free_tree(t);
}
