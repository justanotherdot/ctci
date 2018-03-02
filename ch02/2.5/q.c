#include <stdio.h>
#include "../common/linked_list.h"

struct sum_int_t {
  int val;
  int carry;
};
typedef struct sum_int_t SumInt;

SumInt
sum_int_nodes(Node* x, Node* y)
{
  SumInt rv;

  rv.val = 0;
  rv.carry = 0;

  if (x == NULL || y == NULL)
  {
    rv.val = x == NULL ? *(int*)y->payload : *(int*)x->payload;
    return rv;
  }

  int val = (*(int*)x->payload + *(int*)y->payload);

  rv.val = val > 10 ? (val-10) : val;
  rv.carry = val > 10 ? 1 : 0;

  return rv;
}

int
sum_int_list_forward(Node* x, Node* y)
{
  int rv = 0;

  SumInt si = {
    .val = 0,
    .carry = 0
  };

  size_t xlen = list_len(x);
  size_t ylen = list_len(y);
  size_t len = xlen > ylen ? xlen : ylen;

  Node* a = x;
  Node* b = y;

  unsigned radix = 1;

  for (size_t i = 0; i < len; ++i)
  {
    rv += si.carry * radix;

    si = sum_int_nodes(a, b);

    rv += si.val * radix;

    a = a->next;
    b = b->next;

    radix *= 10;

    if ((i+1) == len && si.carry > 0)
    {
      rv += si.carry * radix;
    }
  }

  return rv;
}

int
main(void)
{
  int x0 = 4;
  int x1 = 1;
  int x2 = 6;
  int* xs[] = {
    &x0,
    &x1,
    &x2,
  };

  int y0 = 1;
  int y1 = 0;
  int y2 = 6;
  int* ys[] = {
    &y0,
    &y1,
    &y2,
  };

  // n.b.
  // TODO
  // If stored in forward order:
  // the solution goes a little differently (and is a bit annoying).
  // 1. We have to find the largest of the two numbers
  // 2. We have to pad the smaller of the two lists with zeroes
  // 3. We have to start at the largest radix and divide by 10 each time.

  Node* head0 = from_arr((void*)&xs, sizeof xs/sizeof(int*));
  Node* head1 = from_arr((void*)&ys, sizeof ys/sizeof(int*));

  print_as_int_list(head0);
  print_as_int_list(head1);

  int val = sum_int_list_forward(head0, head1);
  printf("result: %d\n", val);

  free_list(head0);
  free_list(head1);
}
