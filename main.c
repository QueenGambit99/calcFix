#include "GPIO.c"
#include "keypad.c"
#include "LCD.c"
#include "stack.c"
#include "stackfloat.c"
#include "postfix.c"

int checkOperator(char result);

int main(void)
{
  LCD_init();
  keypad_init();
  char result;
  char prevPress;
  char equationToCalc[17];
  int equationIndex = 0;
  stack postFixCalc;
  createStack(&postFixCalc);
  float resultNumber;
  int checkEqualPress = 0;
  int indexOfEqn = 0;
  int errorCheck = 0;
  while(1)
  {
	result = prevPress = keypad_getKey();
    while(result != 'F' && result == prevPress)
	{
	  if(result == '=')
	  {
		equationToCalc[equationIndex] = '\0';
		setCursorPos(LCD_SECOND_LINE, 0);
		while(equationToCalc[indexOfEqn] != '\0')
		{
		  if(indexOfEqn == 0)
		  {
			if(equationToCalc[0] == '/' || equationToCalc[0] == '*')
			{
				LCD_dispString("Error");
				errorCheck = 1;
				break;
			}

		  }
		  else
		  {
			if(equationToCalc[indexOfEqn] == '0' && equationToCalc[indexOfEqn - 1] == '/')
			{
				LCD_dispString("Math Error");
				errorCheck = 1;
				break;
			}

		  }
		  indexOfEqn++;
		}
	    postFixCalc = postFix(equationToCalc);
	    resultNumber = evaluatePostFix(postFixCalc);
		if(errorCheck == 0)
			LCD_dispFloatNumber(resultNumber);
		checkEqualPress = 1;
		break;
	  }

	  if(result == '?')
	  {
		LCD_clearScreen();
		clearStack(&postFixCalc);
		equationIndex = 0;
		break;
	  }

	  if(checkEqualPress == 1 && checkOperator(result))
	  {
		char prevAns[8];
		sprintf(prevAns, "%d", (int) resultNumber);
		clearStack(&postFixCalc);
		LCD_clearScreen();
		LCD_dispNumber(resultNumber);
		equationIndex = 0;
		while(prevAns[equationIndex] != '\0')
		{
		  equationToCalc[equationIndex] = prevAns[equationIndex];
		  equationIndex++;
		}
	  }

	  else if(checkEqualPress == 1 && !checkOperator(result))
	  {
		LCD_clearScreen();
		clearStack(&postFixCalc);
		equationIndex = 0;
		checkEqualPress = 0;
	  }

	  LCD_dispChar(result);
	  equationToCalc[equationIndex] = result;
	  equationIndex++;
	  prevPress = keypad_getKey();
	  checkEqualPress = 0;
	}

  }
}


int checkOperator(char result)
{
  switch(result)
  {
	case '-':
	case '+':
	case '*':
	case '/':
	  return 1;
	default:
	  return 0;
  }
}