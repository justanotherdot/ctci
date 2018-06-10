#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

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

Tree* singleton(size_t val);

Tree* from_dist_asc_list(Slice xs);

size_t tree_size(Tree* t);

void to_list_go(Tree* t, List* xs);

List to_list(Tree* t);

void print_list(List xs);

void print_tree(Tree* t);

#endif
