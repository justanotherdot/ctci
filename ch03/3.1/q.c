#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MAX_CAP 1024
#define NUM_STACKS 3

struct stack_t
{
  int* base;
  int boffset;
  int size;
  int MAX_STACK_SIZE;
};
typedef struct stack_t Stack;

enum stack_result_type_t
{
  PopSuccess,
  PopFailure,
  PushSuccess,
  PushFailure,
};
typedef enum stack_result_type_t StackResultTy;

// Could have probably done this with just a Maybe type.
struct stack_result_t
{
  StackResultTy tag;
  int val;
};
typedef struct stack_result_t StackResult;

// Would be nicer if these took pure values and returned the stack in the
// StackResult
StackResult
push(Stack* s, int val)
{
  StackResult sr;

  if (s->size <= s->MAX_STACK_SIZE)
  {
    sr.tag = PushFailure;
  }


  *(s->base+s->boffset+s->size) = val;
  ++s->size;

  sr.tag = PushSuccess;

  return sr;
}

StackResult
pop(Stack* s)
{
  StackResult sr;
  if (s->size < 1)
  {
    sr.tag = PopFailure;
    return sr;
  }

  --s->size;
  sr.tag = PopSuccess;
  sr.val = *(s->base+s->boffset+s->size);

  return sr;
}

int
main(void)
{
  const int MAX_STACK_SIZE = (int)ceil(MAX_CAP/NUM_STACKS);

  Stack ss[NUM_STACKS];
  int base[MAX_CAP];
  for (int i = 0; i < NUM_STACKS; ++i)
  {
    ss[i].boffset = i*MAX_STACK_SIZE;
    ss[i].base = base+ss[i].boffset;
    ss[i].size = 0;
    ss[i].MAX_STACK_SIZE = MAX_STACK_SIZE;
  }

  StackResult sr0 = push(&ss[0], 12);
  if (sr0.tag == PushSuccess)
  {
    StackResult sr = pop(&ss[0]);
    if (sr.tag == PopSuccess)
    {
      int k = sr.val;
      printf("%d\n", k);
    }
  }

}
