#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../common/tree.h"

int main(void)
{
  Tree* t;

  int arr01[] = { 1, 2, 3, 4, 5 };
  Slice s01 = {
    .arr = arr01,
    .beg = 0,
    .end = 4,
    .size = 5,
  };
  t = from_dist_asc_list(s01);

  List xs = to_list(t);
  print_list(xs);

}
