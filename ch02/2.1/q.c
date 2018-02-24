#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../common/linked_list.h"

// O(n^2)
void
nub(Node* head)
{
  // Nub (meaning "essence")

  size_t len = list_len(head);
  if (len < 2)
  {
   return;
  }

  Node* curr = head;
  while (curr != NULL)
  {
    int* cval = curr->payload;

    Node* runner = curr->next;
    while (runner != NULL)
    {
      int* rval = runner->payload;
      if (*cval == *rval)
      {
        delete_node(&head, runner);
        break;
      }
      runner = runner->next;
    }

    curr = curr->next;
  }
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

  Node* head = from_arr((void*)&xs, sizeof xs/sizeof(int*));

  nub(head);

  print_as_int_list(head);

  free_list(head);
}
