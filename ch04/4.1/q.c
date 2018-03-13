#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "q.h"

/*
 * Union Find
 */

UnionFind
union_find(int n)
{
  UnionFind uf = {
    .parent = malloc(sizeof(int)*n),
    .size = malloc(sizeof(int)*n),
    .count = n,
  };

  for (int i = 0; i < n; ++i)
  {
    uf.parent[i] = i;
    uf.size[i] = 1;
  }

  return uf;
}

void
link(UnionFind* uf, int p, int q)
{
  // So named because `union' is a keyword in C.
  int rootP = find(uf, p);
  int rootQ = find(uf, q);
  if (rootP == rootQ)
  {
    return;
  }

  if (uf->size[rootP] < uf->size[rootQ])
  {
    uf->parent[rootP] = rootQ;
    uf->size[rootQ] += uf->size[rootQ];
  }
  else
  {
    uf->parent[rootQ] = rootP;
    uf->size[rootP] += uf->size[rootQ];
  }

  uf->count--;
}

int
find(UnionFind* uf, int p)
{
  int root = p;
  while (root != uf->parent[root])
  {
    root = uf->parent[root];
  }
  while (p != root)
  {
    int newp = uf->parent[p];
    uf->parent[p] = root;
    p = newp;
  }
  return root;
}

bool
connected(UnionFind* uf, int p, int q)
{
  return find(uf, p) == find(uf, q);
}


/*
 * Main
 */

struct pair_t
{
  int x;
  int y;
};
typedef struct pair_t Pair;

Pair*
random_pairs(int n)
{
  Pair* ps = malloc(sizeof(Pair)*n);

  for (int i = 0; i < n; ++i)
  {
    ps[i].x = rand() % n;
    ps[i].y = rand() % n;
  }

  return ps;
}

int
main(void)
{
  srand(time(NULL));

  int n = 4096;
  UnionFind uf = union_find(n);
  Pair* ps = random_pairs(n);

  for (int i = 0; i < n; ++i)
  {
    if ((rand() % n) < (n/3)) {
      link(&uf, ps[i].x, ps[i].y);
    }
  }

  int connected_count = 0;
  printf("Edge   Edge  Status\n");
  for (int i = 0; i < n; ++i)
  {
    bool connect = connected(&uf, ps[i].x, ps[i].y);
    connected_count += connect ? 1 : 0;
    printf("%4d - %4d: %13s\n", ps[i].x, ps[i].y, connect ? "connected" : "NOT connected");
  }
  printf("\n");
  printf("There are %d connected edges.\n", connected_count);
}

