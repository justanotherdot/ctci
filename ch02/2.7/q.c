#include <stdio.h>
#include "../common/linked_list.h"

Node*
intersection_ref(Node* s, Node* t)
{
  // The idea:
  // Something is an intersection if it's some ith level tail of another list.
  // So if two nodes are the same node in memory that means they must have the
  // same `next` pointers and if they have the same next pointers those
  // pointers must point to the same thing, and so on.
  //
  // This seems unnecessarily tedious, so ideally we would actually implement a
  // quick and dirty hash table and iterate across the list making hashes and
  // storing them away. The first collection we find when iterating the second
  // list will be our intersecting nodes. This:
  //   - Maintains the ordering of the nodes (we want to walk from left-to-right
  //   - Keeps the complexity down by using a bit of storage

  size_t slen = list_len(s);
  size_t tlen = list_len(t);
  Node* scurr = s;
  for (size_t i = 0; i < slen; ++i)
  {
    Node* tcurr = t;
    for (size_t j = 0; j < tlen; ++j)
    {
      if (scurr == tcurr)
      {
        return tcurr;
      }
      tcurr = tcurr->next;
    }
    scurr = scurr->next;
  }
  return NULL;
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
  Node* head1 = head0;
  while (*(int*)head1->payload != 4)
  {
    head1 = head1->next;
  }
  printf("head1: %p\n", head1);

  print_as_int_list(head0);
  print_as_int_list(head1);

  Node* head2 = intersection_ref(head0, head1);
  printf("head2: %p\n", head2);

  free_list(head0);
}
