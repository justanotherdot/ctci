#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../common/tree.h"

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

int main(void)
{
  Tree* t = example_tree();

  List xs = to_list(t);
  print_list(xs);

  free_tree(t);
}
