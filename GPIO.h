
void GPIO_Dir(uint8_t port, uint8_t pin, uint8_t dir, uint8_t pullup);
void GPIO_Write(uint8_t port, uint8_t pin, uint8_t data);
void GPIO_Read(uint8_t port, uint8_t pin, uint8_t *data_ptr);
void GPIO_Port_Write(uint8_t port, uint8_t data, uint8_t pos);

#define A 0
#define B 1
#define C 2
#define D 3

#define PULLUP_ON  0
#define PULLUP_OFF 1

#define INPUT  0
#define OUTPUT 1

#define SPECIAL_FUN_REG 0x50
#define SPECFUN_REG          *((GPIO_type)(SPECIAL_FUN_REG))

#define LOW   0x00
#define HIGH  0xFF

#define FULL_PORT     0
#define HIGH_NIBBLE   1
#define LOW_NIBBLE    2