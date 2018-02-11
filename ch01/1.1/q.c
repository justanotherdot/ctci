#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define bool int8_t
#define true 1
#define false 0

void run(void);
bool is_unique_no_ds(char* str, size_t len);

struct example_t {
  char* string;
  size_t size;
};
typedef struct example_t Example;

int
main(void)
{
  // 1.1 Is Unique
  // TODO Make this UTF-8 aware?

  run();
}

void
run()
{
  Example examples[] =
  {
    { "a" , 1 }
  , { "ab", 2 }
  , { "aab", 3 }
  , { "apple", 5 }
  , { "brew", 4 }
  };
  bool expected[] =
  {
    true
  , true
  , false
  , false
  , true
  };
  char* yes_or_no[] =
  {
    "no"
  , "yes"
  };
  int is_unique = 0;
  char* example;
  size_t size = 0;

  for (size_t i = 0; i < sizeof(examples)/sizeof(Example); ++i)
  {
    example = examples[i].string;
    size = examples[i].size;
    is_unique = is_unique_no_ds(example, size);
    printf("%s is unique? %s\n", example, yes_or_no[is_unique]);
    assert(is_unique == expected[i]);
  }
}


// O(n^2)
bool
is_unique_no_ds(char* str, size_t str_len)
{
  bool rv = true;
  char c;

  for (size_t i = 0; i < str_len; ++i)
  {
    c = str[i];
    for (size_t j = i+1; j < str_len; ++j)
    {
      if (c == str[j])
      {
        return false;
      }
    }
  }
  return rv;
}
