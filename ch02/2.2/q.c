#include <stdio.h>
#include "../common/linked_list.h"

Node*
kth_last(Node* head, size_t k)
{
  size_t len = list_len(head);

  // kth means one-indexed.
  if (k > len || k < 1)
  {
    return NULL;
  }

  size_t delta = len - k;
  Node* curr = head;
  for (size_t i = 0; i < delta; ++i)
  {
    curr = curr->next;
  }
  return curr;
}

int
main(void)
{
  int a = 1;
  int b = 2;
  int c = 3;
  int d = 4;
  int e = 5;
  int f = 6;
  int* xs[] = {
    &a,
    &b,
    &c,
    &d,
    &e,
    &f,
  };

  Node* head = from_arr((void*)&xs, sizeof xs/sizeof(int*));
  Node* kth = kth_last(head, 6);
  if (kth != NULL)
  {
    printf("%d\n", *(int*)kth->payload);
  }

  print_as_int_list(head);

  free_list(head);
}
