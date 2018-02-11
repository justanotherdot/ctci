#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

// Data.
struct example_t {
  int64_t a;
  int64_t b;
  int64_t result;
};
typedef struct example_t Example;

struct pair_t {
  int64_t fst;
  int64_t snd;
};
typedef struct pair_t Pair;

// Prototypes.
int64_t
bin_add(int64_t x, int64_t y);

Pair*
adder_2bit(int64_t a, int64_t b, int8_t carry);

// Program.
// TODO
//  * Make hardcode of int64_t to something more portable.
//  * Make addition two's complement aware (?).
int
main(void)
{
  Example examples[] =
  {
    { 1, 1, 1+1 }
  , { 2, 1, 2+1 }
  , { 10, 5, 10+5 }
  , { 10, -5, 10+(-5) }
  , { -10, 5, (-10)+5 }
  , { LONG_MAX, LONG_MAX, LONG_MAX+LONG_MAX } // Overflow
  , { LONG_MAX, -LONG_MAX, LONG_MAX+(-LONG_MAX) } // Inverse
  , { -LONG_MAX, -1, (-LONG_MAX)+(-1) } // Underflow
  };

  size_t bound = sizeof(examples)/sizeof(Example);
  for (size_t i = 0; i < bound; ++i)
  {
    Example e = examples[i];
    int64_t k = bin_add(e.a, e.b);
    printf("%ld + %ld = %ld? %s\n", e.a, e.b, k, k == e.result ? "yes" : "no");
    if (k != e.result) {
      printf("FAIL: %ld should actually be %ld\n", k, e.result);
    }
    assert(k == e.result);
  }
}

Pair*
pair(int64_t fst_val, int64_t snd_val)
{
  Pair* tup = malloc(sizeof(Pair));
  assert(tup != NULL);

  tup->fst = fst_val;
  tup->snd = snd_val;
  return tup;
}

Pair*
adder_2bit(int64_t a, int64_t b, int8_t carry)
{
  Pair* tup = pair(0, 0);

  if (a == 1 && b == 1)
  {
    tup->fst = carry ? 1 : 0;
    tup->snd = 1;
  }
  else if (a == 1 || b == 1)
  {
    tup->fst = carry ? 0 : 1;
    tup->snd = carry ? 1 : 0;
  }
  else
  {
    tup->fst = carry ? 1 : 0;
    tup->snd = 0;
  }

  return tup;
}

int64_t
bin_add(int64_t x, int64_t y)
{
  int8_t carry = 0;
  int64_t rv = 0;
  for (int64_t i = 0; i < 64; ++i)
  {
    int64_t a = (x >> i) & 1;
    int64_t b = (y >> i) & 1;

    Pair* tup = adder_2bit(a, b, carry);

    rv |= (tup->fst << i);
    carry = tup->snd;

    free(tup);
  }

  return rv;
}
