
#include <stdint.h>
#include "GPIO.h"

typedef volatile uint8_t *const GPIO_type;
#define PORTS_NUMBER 4u
#define PINS_NUMBER  8u

#define PORTA_ADDR 0x3B
#define PORTB_ADDR 0x38
#define PORTC_ADDR 0x35
#define PORTD_ADDR 0x32

static const uint8_t PORTS_ADDR[PORTS_NUMBER] = {PORTA_ADDR, PORTB_ADDR, PORTC_ADDR, PORTD_ADDR};

#define GPIO_WRITE(PORT_NUMBER)  *((GPIO_type)(PORTS_ADDR[PORT_NUMBER] - 0x00))
#define GPIO_READ(PORT_NUMBER)   *((GPIO_type)(PORTS_ADDR[PORT_NUMBER] - 0x02))
#define GPIO_DDR(PORT_NUMBER)    *((GPIO_type)(PORTS_ADDR[PORT_NUMBER] - 0x01))


void GPIO_Dir(uint8_t port, uint8_t pin, uint8_t dir, uint8_t pullup)
{
  if(port < PORTS_NUMBER && pin < PINS_NUMBER)
  {
    if(dir == INPUT)
    {
      GPIO_DDR(port) &= ~((1 << pin) & 0xFF);

      if(pullup == PULLUP_ON)
      {
        GPIO_WRITE(port) |= ((1 << pin) & 0xFF);
        SPECFUN_REG &= ~(1 << 2);
      }
      else if(pullup == PULLUP_OFF)
      {
        GPIO_WRITE(port) &= ~((1 << pin) & 0xFF);
      }
    }

    else if(dir == OUTPUT)
    {
      GPIO_DDR(port) |= ((1 << pin) & 0xFF);
    }
  }
}

void GPIO_Write(uint8_t port, uint8_t pin, uint8_t data)
{
  if(port < PORTS_NUMBER && pin < PINS_NUMBER)
  {
    if(data == LOW)
    {
      GPIO_WRITE(port) &= ~((1 << pin) & 0xFF);
    }
    else if(data == HIGH)
    {
      GPIO_WRITE(port) |= ((1 << pin) & 0xFF);
    }
  }
}

void GPIO_Read(uint8_t port, uint8_t pin, uint8_t *data_ptr)
{
  static uint8_t value;
  if(port < PORTS_NUMBER && pin < PINS_NUMBER)
  {
    value = (GPIO_READ(port) & (1 << pin));
    if(value == 0)
    {
      *data_ptr = 0x00;
    }
    else if((value & 0xFF) == (1 << pin))
    {
      *data_ptr = 0xFF;
    }
  }

  // IF the user wants to read all port
  if(pin == 8)
  {
    *data_ptr = GPIO_READ(port);
  }
}

void GPIO_Port_Write(uint8_t port, uint8_t data, uint8_t pos)
{
  if(port < PORTS_NUMBER)
  {
    if(pos == FULL_PORT)
    {
      GPIO_WRITE(port) = data;
    }
    else if(pos == HIGH_NIBBLE)
    {
      GPIO_WRITE(port) &= 0x0F;
      GPIO_WRITE(port) |= (data & 0xF0);
    }
    else if(pos == LOW_NIBBLE)
    {
      GPIO_WRITE(port) &= 0xF0;
      GPIO_WRITE(port) |= (data & 0x0F);
    }
  }
}
