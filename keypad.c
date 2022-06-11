

#include "keypad.h"

void keypad_init()
{
  uint8_t i;
  for(i = ROW0; i <= ROW3; i++)
    GPIO_Dir(PORTID, i, OUTPUT, PULLUP_OFF);
  for(i = COL0; i <= COL3; i++)
    GPIO_Dir(PORTID, i, INPUT, PULLUP_ON);
}

uint8_t data;

char keypad_getKey()
{
  uint8_t i, j;
  char input = 'F';

  for(i = ROW0; i <= ROW3; i++)
  {
    GPIO_Write(PORTID, ROW0, HIGH);
    GPIO_Write(PORTID, ROW1, HIGH);
    GPIO_Write(PORTID, ROW2, HIGH);
    GPIO_Write(PORTID, ROW3, HIGH);

    GPIO_Write(PORTID, i, LOW);

    for(j = COL0; j <= COL3; j++)
    {
      GPIO_Read(PORTID, j, &data);
      if(data == LOW)
      {
        while(data == LOW) GPIO_Read(PORTID, j, &data);
        switch(i)
        {
          case(ROW0):
          {
            if(j == COL0)       input = '7';
            else if (j == COL1) input = '8';
            else if (j == COL2) input = '9';
            else                input = '/';
            break;
          }
          case(ROW1):
          {
            if(j == COL0)       input = '4';
            else if (j == COL1) input = '5';
            else if (j == COL2) input = '6';
            else                input = '*';
            break;
          }
          case(ROW2):
          {
            if(j == COL0)       input = '1';
            else if (j == COL1) input = '2';
            else if (j == COL2) input = '3';
            else                input = '-';
            break;
          }
          case(ROW3):
          {
            if(j == COL0)       input = '?';
            else if (j == COL1) input = '0';
            else if (j == COL2) input = '=';
            else                input = '+';
            break;
          }
          default:
          {
            input = 'F';
            break;
          }
        }
      }
    }
  }
  return input;
}