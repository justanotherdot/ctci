#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "linked_list.h"

size_t
list_len(Node* head)
{
  size_t len = 0;
  Node* curr = head;
  while (curr != NULL)
  {
    ++len;
    curr = curr->next;
  }
  return len;
}

Node*
from_arr(void** parr, size_t len)
{
  Node* head = NULL;
  Node* n = NULL;
  for (size_t i = 0; i < len; ++i)
  {
    n = new_node(parr[i]);
    if (head == NULL)
    {
      head = n;
    } else
    {
      push_back(head, n);
    }
  }
  return head;
}

Node*
push_back(Node* head, Node* new_tail)
{
  Node* curr = head;
  Node* prev = head;
  while (curr != NULL)
  {
    prev = curr;
    curr = curr->next;
  }
  prev->next = new_tail;
  return head;
}

Node*
new_node(void* payload)
{
  Node* n = malloc(sizeof(Node));
  n->payload = payload;
  n->next = NULL;

  return n;
}

void
print_as_int_list(Node* head)
{
  // FIXME
  // Ideally we'd have a function that pretty prints a linked list and then
  // just print that straightforwardly. This couples itself too tightly to the
  // internals with effects. Conversely, implementing that is tricky: We need
  // to use something like sprintf for each integer we print. And our list is
  // generic, so which do we use to cast? That's actually another issue with
  // this code; it will always cast whatever values we're storing to int.
  Node* curr = head;
  printf("[");
  while (curr != NULL)
  {
    int* p = (int*)curr->payload;
    printf("%d", *p);
    if (curr->next != NULL)
    {
      printf(", ");
    }
    curr = curr->next;
  }
  printf("]\n");
}
