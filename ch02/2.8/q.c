#include <stdio.h>
#include <assert.h>
#include "../common/linked_list.h"

Node*
find_cycle(Node* xs)
{
  // This is effecitvely the solution from the book.

  Node* slow = xs;
  Node* fast = xs;

  // If fast supercedes slow, then i and i+1 but i-1, and ((i-1) - 2) = i - 1
  // are the two prior positions from the step before. Therefore, they must
  // have collided.
  while (fast != NULL && fast->next != NULL)
  {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast)
    {
      break;
    }
  }

  // The list is not really a cycle.
  if (fast == NULL || fast->next == NULL)
  {
    return NULL;
  }

  // The head and the collided node from above are both k nodes away
  // from the start of the list. I'm still not _really_ sure why this
  // is the case, but the book seems to attempt to describe it.
  slow = xs;
  while (slow != fast)
  {
    slow = slow->next;
    fast = fast->next;
  }

  return fast;
}

int
main(void)
{
  int x0 = 0;
  int x1 = 1;
  int x2 = 2;
  int x3 = 3;
  int x4 = 4;
  int x5 = 5;
  int x6 = 6;
  int x7 = 7;
  int* xs[] = {
    &x0,
    &x1,
    &x2,
    &x3,
    &x4,
    &x5,
    &x6,
    &x7,
  };

  Node* head0 = from_arr((void*)&xs, sizeof xs/sizeof(int*));
  printf("Original list: ");
  print_as_int_list(head0);

  printf("Tying the knot ...\n");
  Node* curr = head0;
  Node* knot = NULL;
  while (curr->next != NULL)
  {
    if (*(int*)curr->payload == 4)
    {
      knot = curr;
    }
    curr = curr->next;
  }
  curr->next = knot;

  printf("Finding cycle ... \n");
  Node* cycle_head = find_cycle(head0);
  if (cycle_head != NULL)
  {
    printf("Cycle found with payload %d\n", *(int*)cycle_head->payload);
    if (*(int*)cycle_head->payload != *(int*)knot->payload)
    {
      printf("%d != %d\n", *(int*)cycle_head->payload, *(int*)knot->payload);
    }
    assert(*(int*)cycle_head->payload == *(int*)knot->payload);
  }

  // TODO need a `free_list_with_cycle(list, head_of_cycle)'
  //free_list(head0);
}
