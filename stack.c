/*********************************INCLUDES*********************************/

#include <stdio.h>
#include <stdlib.h>

/*********************************DEFINES*********************************/

#define STACKENTRY int

/*********************************TYPES*********************************/

typedef struct stackNode
{
  struct stackNode *next;
  STACKENTRY entry;
}node;

typedef struct Stack
{
  node *top;
  int size;
}stack;



/*********************************FUNCTIONS DECLARATION*********************************/

/* createStack() */
void createStack(stack *ps)
{
  ps->top = NULL;
  ps->size = 0;
}

void clearStack(stack *ps)
{
  node *pn = ps->top;
  while(!ps->top)
  {
    ps->top = pn->next;
	free(pn);
	pn = ps->top;
  }
  ps->size = 0;
}

/* push() */
void push(STACKENTRY e, stack *ps)
{
  node *pn = (node *) malloc(sizeof(node));
  pn->entry = e;
  pn->next = ps->top;
  ps->top = pn;
  ps->size ++;
}

/* pop() */
void pop(STACKENTRY *pe, stack *ps)
{
  node *pn = ps->top;
  *pe = ps->top->entry;
  ps->top = ps->top->next;
  free(pn);
  ps->size --;
}

/* stackTop() */
void stackTop(STACKENTRY *pe, stack *ps)
{
  *pe = ps->top->entry;
}

/* stackEmpty() */
int stackEmpty(stack *ps)
{
  if(ps->top == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


void StackTraverse(stack *ps, void (*pf) (STACKENTRY))
{
  node *pn;
  for(pn = ps->top; pn; pn = pn->next)
  {
    (*pf) (pn->entry);
  }
}

void PrintStack(STACKENTRY e)
{
  switch(e)
  {
    case '+':
      printf("%c\n", e);
      break;
    case '-':
      printf("%c\n", e);
      break;
    case '*':
      printf("%c\n", e);
      break;
    case '/':
      printf("%c\n", e);
      break;
    //case '^':
      //printf("%c\n", e);
      //break;
    case 'n':
      printf("%c\n", e);
      break;
    default:
      printf("%d\n", e);
      break;
  }
}


