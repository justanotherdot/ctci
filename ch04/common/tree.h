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

  size_t beg; // Inclusive.
  size_t end;

  size_t size; // Current size.
  size_t capacity;
};

Tree* singleton(size_t val);

Tree* from_dist_asc_list(Slice xs);

size_t tree_size(Tree* t);

void to_list_go(Tree* t, List* xs);

List to_list(Tree* t);

void print_list(List xs);

void print_tree(Tree* t);

void free_tree(Tree* t);

void free_list(List xs);

void debug_slice(Slice* xs);

#endif
