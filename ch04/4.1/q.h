#ifndef Q_H
#define Q_H

struct union_find_t
{
  int* parent;
  int* size;
  int count;
};
typedef struct union_find_t UnionFind;

UnionFind
union_find(int n);

void
link(UnionFind* uf, int p, int q);

int
find(UnionFind* uf, int p);

bool
connected(UnionFind* uf, int p, int q);

#endif
