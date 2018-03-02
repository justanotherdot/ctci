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

  // TODO this means all payloads are shared.
  // It would be ideal to make copies of the data.
  n->payload = payload;
  n->next = NULL;

  return n;
}

void
delete_node(Node** head, Node* node)
{
  // Linus Torvalds 'double ptr trick'
  // Fabulous at parties.
  Node** curr = head;
  Node* runner = *head;
  while (runner != NULL)
  {
    if (runner == node)
    {
      *curr = runner->next;
      return;
    }

    curr = &runner->next;
    runner = runner->next;
  }
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

void
print_as_char_list(Node* head)
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
    char* p = (char*)curr->payload;
    printf("'%c'", *p);
    if (curr->next != NULL)
    {
      printf(", ");
    }
    curr = curr->next;
  }
  printf("]\n");
}

char*
unsafe_cast_to_str(Node* head)
{
  // XXX
  // Assumes that head is a collection of ascii chars!
  size_t len = list_len(head);
  char* s = malloc(sizeof(char)*len+1);
  s[len-1] = '\0';

  if (len <= 1)
  {
    return s;
  }

  Node* curr = head;
  for (size_t i = 0; i < len; ++i)
  {
    char p = *(char*)curr->payload;
    s[i] = p;
    curr = curr->next;
  }

  return s;
}


void
free_list(Node* head)
{
  Node* curr = head;
  while (curr != NULL)
  {
    Node* to_free = curr;
    curr = curr->next;
    free(to_free);
  }
}

Node*
clone_list(Node* head)
{
  Node* curr = head;
  Node* n = NULL;
  Node* h = NULL;
  Node* prev = NULL;

  while (curr != NULL)
  {
    n = new_node(curr->payload);
    if (prev != NULL)
    {
      prev->next = n;
    }
    if (h == NULL)
    {
      h = n;
    }
    prev = n;
    curr = curr->next;
  }

  return h;
}

void
reverse(Node** head)
{
  if (head == NULL)
  {
    return;
  }

  size_t len = list_len(*head);
  // FIXME memory leak.
  Node** ptrs = malloc(sizeof(Node*)*len+1);
  ptrs[len] = NULL; // Avoid special case in linking step.
  Node* curr = *head;

  for (size_t i = 0; i < len; ++i)
  {
    ptrs[(len-1)-i] = curr;
    curr = curr->next;
  }

  // Link inplace.
  for (size_t i = 0; i < len; ++i)
  {
    ptrs[i]->next = ptrs[i+1];
  }

  *head = ptrs[0];
  free(ptrs);
}
