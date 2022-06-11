

typedef struct stackNodeFloat
{
  struct stackNodeFloat *next;
  float entry;
}nodeFloat;

typedef struct StackFloat
{
  nodeFloat *top;
  int size;
}stackFloat;

/* createStack() */
void createStackFloat(stackFloat *ps)
{
  ps->top = NULL;
  ps->size = 0;
}

void pushFloat(float e, stackFloat *ps)
{
  nodeFloat *pn = (nodeFloat *) malloc(sizeof(nodeFloat));
  pn->entry = e;
  pn->next = ps->top;
  ps->top = pn;
  ps->size ++;
}

/* pop() */
void popFloat(float *pe, stackFloat *ps)
{
  nodeFloat *pn = ps->top;
  *pe = ps->top->entry;
  ps->top = ps->top->next;
  free(pn);
  ps->size --;
}

/* stackEmpty() */
int stackEmptyFloat(stackFloat *ps)
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