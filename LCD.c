

#include <stdio.h>
#include "LCD.h"

static int initState = 0;

void LCD_portControl(void)
{
  GPIO_Dir(CONTROL_PORT, RS_PIN, OUTPUT, PULLUP_OFF);
  GPIO_Dir(CONTROL_PORT, RW_PIN, OUTPUT, PULLUP_OFF);
  GPIO_Dir(CONTROL_PORT, EN_PIN, OUTPUT, PULLUP_OFF);

  GPIO_Dir(DATA_PORT, DB0, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB1, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB2, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB3, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB4, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB5, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB6, OUTPUT, PULLUP_OFF);
  GPIO_Dir(DATA_PORT, DB7, OUTPUT, PULLUP_OFF);
}

void LCD_init(void)
{
  LCD_portControl();
  delay(15000);
  sendCmd(INIT_ADDR);
  delay(100);
  sendCmd(LCD_DISP_ON_CURSOR_OFF_ADDR);
  sendCmd(LCD_CLEAR);
  initState = 1;
}

void LCD_clearScreen(void)
{
  if(initState == 1)
    sendCmd(LCD_CLEAR);
}

void LCD_dispChar(char c)
{
  if(initState == 1)
  {
    sendData(c);
  }
}

void LCD_dispString(char *strPtr)
{
  if(initState == 1)
  {
    while(*strPtr != '\0')
	{
	  LCD_dispChar(*strPtr);
	  *strPtr++;
	}
  }
}

void LCD_dispNumber(int num)
{
  char str[17];
  sprintf(str, "%d", num);
  LCD_dispString(str);
}

void LCD_dispFloatNumber(float num)
{
  long int tenProduct = 10;
  LCD_dispNumber((int) num);

  num -= (int) num;

  while((int) num != num && tenProduct < 100000)
  {
	num *= 10;
	if((int) num == num)
	  break;
    tenProduct *= 10;
  }


  LCD_dispChar('.');
  LCD_dispNumber((int) num % tenProduct);
}

void setCursorPos(int line, int charPos)
{
  if(initState == 1)
  {
    if(line == LCD_FIRST_LINE)
	{
      sendCmd(LCD_FIRST_LINE_ADDR + charPos);
	}
	else if(line == LCD_SECOND_LINE)
	{
      sendCmd(LCD_SECOND_LINE_ADDR + charPos);
	}
  }
}

void delay(int delayPeriod)
{
  volatile long int i;
  for(i = 0; i < delayPeriod * 4; i++);
}


void sendCmd(int cmdID)
{
  GPIO_Write(CONTROL_PORT, RS_PIN, RS_COMMAND);
  GPIO_Write(CONTROL_PORT, RW_PIN, WRITE_TO_LCD);

  GPIO_Port_Write(DATA_PORT, cmdID, FULL_PORT);
  GPIO_Write(CONTROL_PORT, EN_PIN, HIGH);
  delay(1);
  GPIO_Write(CONTROL_PORT, EN_PIN, LOW);
  delay(200);
}

void sendData(int dataID)
{
  GPIO_Write(CONTROL_PORT, RS_PIN, RS_DATA);
  GPIO_Write(CONTROL_PORT, RW_PIN, WRITE_TO_LCD);

  GPIO_Port_Write(DATA_PORT, dataID, FULL_PORT);
  GPIO_Write(CONTROL_PORT, EN_PIN, HIGH);
  delay(1);
  GPIO_Write(CONTROL_PORT, EN_PIN, LOW);
  delay(110);
}
