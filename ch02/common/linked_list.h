#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>

struct node_t {
  void* payload;
  struct node_t* next;
};
typedef struct node_t Node;

size_t
list_len(Node* head);

Node*
from_arr(void** parr, size_t len);

Node*
push_back(Node* head, Node* new_tail);

Node*
new_node(void* payload);

void
delete_node(Node** head, Node* node);

void
print_as_int_list(Node* head);

void
print_as_char_list(Node* head);

char*
unsafe_cast_to_str(Node* head);

void
free_list(Node* head);

#endif
