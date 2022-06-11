
/*********************************INCLUDES*********************************/

#include <stdio.h>
#include <math.h>



/*********************************FUNCTIONS PROTOTYPE*********************************/

stack postFix(char infix[]);
int precedent(char op1, char c);
int power(int count);
float evaluatePostFix(stack s);
float operation(char op, float op1, float op2);
int negSign(char opbef);

/*********************************postFix()*********************************/

stack postFix(char infix[])
{

  /* initialization of local variables */
  int    infixIndex;
  int    numIndex;
  int    op;
  int    numValue;
  int    count;
  char   infixChar;
  char   lastChar;

  /* declaration of local variables */
  infixIndex    = 0;
  numValue      = 0;
  count         = 0;
  lastChar      = -1;

  /* create a stack for postfix */
  stack tempPostFix;
  createStack(&tempPostFix);

  /* create a stack for storing operators */
  stack operators;
  createStack(&operators);

  /* do that while the equation does not finish */
  do
  {
    infixChar = infix[infixIndex];

    /* when the element of the array is an operand */
    if(infixChar >= '0' && infixChar <= '9')
    {
      push((int)(infixChar - '0'), &tempPostFix);
      count++;
    }

    /* when the element of the array is an operator */
    else
    {

      /* put n in the stack in case '-' is negative sign */
      if(infixChar == '-' && (lastChar == -1 || negSign(lastChar)))
      {
        push('n', &operators);
      }

      else
      {

      /* convert previous single digits in the stack into the number */
      for(numIndex = 0; numIndex < count; numIndex ++)
      {
        pop(&op, &tempPostFix);
        numValue = numValue + op * power(numIndex);
      }

      /* reset the count for the next loop */
      count = 0;

      /* put the number from previous loop in the postfix stack */
      push(numValue, &tempPostFix);


      /* reset the numValue for next digits */
      numValue = 0;

      /* put the operators in precedent order */
      if(infixChar != '\0' && !stackEmpty(&operators))
      {
        stackTop(&op, &operators);

        while(!stackEmpty(&operators) && precedent(op, infixChar))
        {
          pop(&op, &operators);
          push(op, &tempPostFix);
          if(!stackEmpty(&operators))
          {
            stackTop(&op, &operators);
          }
        }
      }

      /* push the operator into postfix stack */
      if(infixChar != '\0')
      {
        push(infixChar, &operators);
      }
    }
   }

	lastChar = infixChar;

    /* increase the loop index */
    infixIndex ++;
  }
  while(infixChar != '\0');

  /* push the remaining operators from operators stack into postfix stack */
  while(!stackEmpty(&operators))
  {
    pop(&op, &operators);
    push((int) op, &tempPostFix);
  }

  /* return the stack */
  return tempPostFix;
}

/*********************************precedent()*********************************/

int precedent(char op1, char c)
{
  if(op1 == 'n')
    return 1;

  if ((op1 == '*') || (op1 == '/'))
    return (c != 'n');

  if ((op1 == '+') || (op1 == '-'))
     return ((c != 'n') && (c != '*') && (c != '/'));

  return 0;
}

/*********************************power()*********************************/

int power(int count)
{
  int num = 1;

  if (count == 0)
    return 1;
  else if (count == 1)
    return 10;
  else
  {
    for(int i = 1; i <= count; i ++)
    {
      num = num * 10;
    }
    return num;
  }
}


/*********************************evaluatePostFix()*********************************/

float evaluatePostFix(stack s)
{


  /* intilization for local variables */
  int op;
  float op1;
  float op2;
  float result;


  /* create a stack for rearranging the postfix */
  stack postFixStack;
  createStack(&postFixStack);

  /* create a stack for the calculation */
  stackFloat calcFix;
  createStackFloat(&calcFix);


  /* rearranging the postfix stack */
  while(!stackEmpty(&s))
  {
    pop(&op, &s);
    push(op, &postFixStack);

  }



  /* calcualate the postfix */
  while(!stackEmpty(&postFixStack))
  {

    pop(&op, &postFixStack);


    if(op != '-' && op != '+' && op != '*' && op != '/' && op != '^' && op != 'n')
    {
      pushFloat((float) op, &calcFix);

    }

    else
    {
      if(op == 'n')
      {
        popFloat(&op1, &calcFix);
        result = operation(op, op1, 0);
      }
      else
      {
        popFloat(&op2, &calcFix);
        popFloat(&op1, &calcFix);
        result = operation(op, op1, op2);
      }
      pushFloat(result, &calcFix);
    }
  }

  popFloat(&result, &calcFix);

 return result;
}

/*********************************operation()*********************************/

float operation(char op, float op1, float op2)
{
  switch(op)
  {
    case 'n':
      return (-op1);
	case '+':
      return(op1 + op2);
	case '-':
      return(op1 - op2);
   	case '*':
      return(op1 * op2);
	case '/':
      return(op1 / op2);
  }
}


int negSign(char opbef)
{
switch(opbef)
  {
	case '+':
      return 1;
	case '-':
      return 1;
   	case '*':
      return 1;
	case '/':
      return 1;
    default:
      return 0;
  }
}