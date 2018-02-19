#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef int32_t pixel;

struct square_matrix_t {
  pixel** pixels;
  size_t size;
};
typedef struct square_matrix_t SquareMatrix;

void
print_matrix(SquareMatrix m)
{
  for (size_t i = 0; i < m.size; ++i)
  {
    for (size_t j = 0; j < m.size; ++j)
    {
      if (j+1 == m.size) {
        printf("%d", m.pixels[i][j]);
      } else {
        printf("%d ", m.pixels[i][j]);
      }
    }
    printf("\n");
  }
}

void
map_matrix(SquareMatrix m, void (*f)(pixel))
{
  for (size_t i = 0; i < m.size; ++i)
  {
    for (size_t j = 0; j < m.size; ++j)
    {
      f(m.pixels[i][j]);
    }
  }
}

SquareMatrix
matrix(size_t n)
{
  SquareMatrix m;

  // Allocate.
  pixel** ps = malloc(sizeof(pixel*) * n);
  for (size_t i = 0; i < n; ++i)
  {
    printf("%ld\n", i);
    *(ps+i) = calloc(sizeof(pixel) * n, sizeof(pixel));
  }

  // Assign.
  m.pixels = ps;
  m.size = n;

  return m;
}

int
main(void)
{
  SquareMatrix m = matrix(5);

  print_matrix(m);
}
