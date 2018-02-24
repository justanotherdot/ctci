#include <stdio.h>
#include "../common/linked_list.h"

#define TRUE 1
#define FALSE 0

char
is_palindrome(Node* head)
{
  Node* curr = head;
  char valid_palindrome = TRUE;
  size_t len = list_len(head);
  for (size_t i = 0; i < len; ++i)
  {
    // O(n^2) variant that isn't a double-ended linked-list.
    Node* tail = head;
    for (size_t j = 0; j < len-i-1; ++j)
    {
      tail = tail->next;
    }
    if (*(char*)curr->payload != *(char*)tail->payload)
    {
      valid_palindrome = FALSE;
    }
    curr = curr->next;
  }
  return valid_palindrome;
}

int
main(void)
{
  char a = 't';
  char b = 'a';
  char c = 'c';
  char d = 'o';
  char e = 'c';
  char f = 'a';
  char g = 't';
  char* xs[] = {
    &a,
    &b,
    &c,
    &d,
    &e,
    &f,
    &g,
  };

  Node* head = from_arr((void*)&xs, sizeof xs/sizeof(int*));

  char is_palindrome_str = is_palindrome(head);

  print_as_char_list(head);
  char* s = unsafe_cast_to_str(head);
  printf("%s, '%s' is %s a palindrome\n", is_palindrome_str ? "yes" : "no", s, is_palindrome_str ? "" : "not");

  free_list(head);
}
