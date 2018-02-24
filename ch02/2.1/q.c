#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../common/linked_list.h"

void
nub(Node* head)
{
  // Nub (meaning "essence")
}

int
main(void)
{
  int a = 13;
  int b = 12;
  int c = 13;
  int d = 11;
  int e = 14;
  int f = 12;
  int* xs[] = {
    &a,
    &b,
    &c,
    &d,
    &e,
    &f,
  };
  Node* n = from_arr((void*)&xs, sizeof xs/sizeof(int*));

  print_as_int_list(n);
}
