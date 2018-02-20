#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

typedef int32_t pixel;

struct square_matrix_t {
  pixel** pixels;
  size_t size;
};
typedef struct square_matrix_t SquareMatrix;

void
print_n_of(char c, size_t n)
{
  for (size_t i = 0; i < n; ++i)
  {
    if ((i+1) == n)
    {
      printf("\n");
    } else
    {
      printf("%c", c);
    }
  }
}

void
print_matrix(SquareMatrix m, char* name)
{
  printf("%s\n", name);
  print_n_of('-', m.size*2);
  for (size_t i = 0; i < m.size; ++i)
  {
    for (size_t j = 0; j < m.size; ++j)
    {
      if (j+1 == m.size)
      {
        printf("%d", m.pixels[i][j]);
      } else
      {
        printf("%d ", m.pixels[i][j]);
      }
    }
    printf("\n");
  }
  print_n_of('-', m.size*2);
  printf("\n");
}

void
map_matrix(SquareMatrix m, void (*f)(pixel*, size_t, size_t))
{
  for (size_t i = 0; i < m.size; ++i)
  {
    for (size_t j = 0; j < m.size; ++j)
    {
      f(&m.pixels[i][j], i, j);
    }
  }
}

SquareMatrix
square_matrix(size_t n)
{
  SquareMatrix m;

  // Allocate.
  pixel** ps = malloc(sizeof(pixel*) * n);
  for (size_t i = 0; i < n; ++i)
  {
    *(ps+i) = calloc(sizeof(pixel) * n, sizeof(pixel));
  }

  // Assign.
  m.pixels = ps;
  m.size = n;

  return m;
}

SquareMatrix
rot90_tmp_buf(SquareMatrix m)
{
  SquareMatrix q = square_matrix(m.size);

  for (size_t i = 0; i < m.size; ++i)
  {
    for (size_t j = 0; j < m.size; ++j)
    {
      q.pixels[j][(m.size-1)-i] = m.pixels[i][j];
    }
  }

  return q;
}

void
xorSwap(pixel* a, pixel* b)
{
  // XXX This will fail if a and b are the same pointer.
  // Since we're clobbering the value held in the other ptr.
  assert(a != b);

  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

void
swap4_xor(pixel* a, pixel* b, pixel* c, pixel* d)
{
  xorSwap(a, b);
  xorSwap(b, c);
  xorSwap(c, d);
}

void
swap4(pixel* a, pixel* b, pixel* c, pixel* d)
{
  pixel tmp = *a;
  *a = *b;
  *b = *c;
  *c = *d;
  *d = tmp;
}

// N.B.
// The dirty white lie we tell ourselves is that this inplace sort does not use
// 'any extra memory' but the reality is that we'll always need at least one
// extra cell element to stash away the temporary value. On extremely memory
// constrained systems (e.g. embedded contexts) another alternative needs to be
// taken, such as bit fiddling approaches involving XOR swaps.
void
rot90_in_place(SquareMatrix m)
{
  for (size_t i = 0; i < m.size/2; ++i)
  {
    for (size_t j = i; j < (m.size-1)-i; ++j)
    {
      swap4_xor(
                                               // Initially ...
        &m.pixels[i][j],                       // upper left.
        &m.pixels[(m.size-1)-j][i],            // lower left.
        &m.pixels[(m.size-1)-i][(m.size-1)-j], // lower right.
        &m.pixels[j][(m.size-1)-i]             // upper right.
      );
    }
  }
}

// `lambdas'.

// TODO make a lambda that generates a random number to assign.
void
set(pixel* p, size_t i, size_t j)
{
  *p = i+j;
}


int
main(void)
{
  SquareMatrix p = square_matrix(4);
  map_matrix(p, &set);
  SquareMatrix q = rot90_tmp_buf(p);

  print_matrix(p, "P (original)");
  print_matrix(q, "Q (after tmp_buf rotation)");

  SquareMatrix a = square_matrix(4);
  map_matrix(a, &set);
  print_matrix(a, "A (before rotation)");
  rot90_in_place(a);
  print_matrix(a, "A (after rotation)");

  SquareMatrix b = square_matrix(5);
  map_matrix(b, &set);
  print_matrix(b, "B (before rotation)");
  rot90_in_place(b);
  print_matrix(b, "B (after rotation)");

  SquareMatrix c = square_matrix(2);
  map_matrix(c, &set);
  print_matrix(c, "C (before rotation)");
  rot90_in_place(c);
  print_matrix(c, "C (after rotation)");
}
