

#define RS_PIN 1
#define RW_PIN 2
#define EN_PIN 3

#define DB0 0
#define DB1 1
#define DB2 2
#define DB3 3
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7

#define CONTROL_PORT A
#define DATA_PORT    B


#define INIT_ADDR 0x38
#define LCD_DISP_ON_CURSOR_OFF_ADDR 0x0C
#define LCD_CLEAR 0x01
#define LCD_FIRST_LINE_ADDR  0x80
#define LCD_SECOND_LINE_ADDR 0xC0


#define LCD_FIRST_LINE 0
#define LCD_SECOND_LINE 1

#define RS_COMMAND 0x00
#define RS_DATA    0xFF
#define WRITE_TO_LCD  0x00
#define READ_FROM_LCD 0xFF

void LCD_portControl(void);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_dispChar(char c);
void LCD_dispString(char *strPtr);
void LCD_dispNumber(int num);
void LCD_dispFloatNumber(float num);
void setCursorPos(int line, int charPos);
void delay(int delayPeriod);
void sendCmd(int cmdID);
void sendData(int dataID);