#include <stdio.h>
#include "../common/linked_list.h"

void
delete_middle(Node* head)
{
  if (head == NULL)
    return;

  size_t len = list_len(head);
  if (len%2 == 0)
  {
    Node* curr = head;
    size_t middle = (len/2)-1;
    for (size_t i = 0; i < middle; ++i)
    {
      curr = curr->next;
    }
    delete_node(&head, curr);
  }
  else
  {
    Node* curr = head;
    size_t middle = (len/2);
    for (size_t i = 0; i < middle; ++i)
    {
      curr = curr->next;
    }
    delete_node(&head, curr);
  }
}

int
main(void)
{
  char a = 'a';
  char b = 'b';
  char c = 'c';
  char d = 'd';
  char e = 'e';
  char f = 'f';
  char* xs[] = {
    &a,
    &b,
    &c,
    &d,
    &e,
    &f,
  };

  Node* head = from_arr((void*)&xs, sizeof xs/sizeof(int*));

  delete_middle(head);

  print_as_char_list(head);

  free_list(head);
}
