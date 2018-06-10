#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../common/tree.h"

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
