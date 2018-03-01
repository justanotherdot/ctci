#include <stdio.h>
#include "../common/linked_list.h"


void
link(Node** n, Node** p, Node** h, void* payload)
{
  *n = new_node(payload);

  if (p != NULL && *p != NULL)
  {
    (*p)->next = *n;
  }

  if (h != NULL && *h == NULL)
  {
    *h = *n;
  }
  *p = *n;
}

char
cmp_lt(int a, int b)
{
  return a < b;
}

char
cmp_eq(int a, int b)
{
  return a == b;
}

char
cmp_gt(int a, int b)
{
  return a > b;
}

void
link_with_int_cmp(Node** n, Node** p, Node** h, void* payload, int k, char (*cmp)(int, int))
{
  if ((*cmp)(*(int*)payload, k))
  {
    link(n, p, h, payload);
  }
}

void
partition_with_compare(Node* head, Node** n, Node** p, Node** h, int k, char (*cmp)(int, int))
{
  Node* curr = head;
  while (curr != NULL)
  {
    link_with_int_cmp(n, p, h, curr->payload, k, cmp);
    curr = curr->next;
  }
}

Node*
partition_int_list(Node* head, int k)
{
  // O(4n) time
  // O(n) space

  size_t len = list_len(head);
  if (len == 0)
  {
    // n.b. To avoid double-free errors.
    return clone_list(head);
  }

  Node* p = NULL;
  Node* n = NULL;
  Node* h = NULL;

  partition_with_compare(head, &n, &p, &h, k, cmp_lt);
  partition_with_compare(head, &n, &p, &h, k, cmp_eq);
  partition_with_compare(head, &n, &p, &h, k, cmp_gt);

  return h;
}

int
main(void)
{
  int x0 = 4;
  int x1 = 1;
  int x2 = 6;
  int x3 = 3;
  int x4 = 9;
  int x5 = 2;
  int x6 = 3;
  int x7 = 5;
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

  Node* head1 = partition_int_list(head0, 3);

  print_as_int_list(head0);
  print_as_int_list(head1);

  free_list(head0);
  free_list(head1);
}
