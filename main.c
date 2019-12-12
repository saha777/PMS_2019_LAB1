#include "delay.h"
#include "keyboard.h"
#include "tm1637.h"
#include "number_converter.h"

#include "stdlib.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "Encoder.h"

void display_value(int,char);
int keyboard_value(char key);

#define KEYBOARD_ENABLED 0
#define ENCODER_ENABLED 1

#define MOVE_LEFT 0
#define UNVALUABLE -1

//keyboard
//C3 GPIOB9
//C2 GPIOB10
//C1 GPIOB11
//R4 GPIOB12
//R3 GPIOB13
//R2 GPIOB14
//R1 GPIOB15

//display
//CLK GPIOB6
//DIO GPIOB7
//UCC 5V
//GND G

//encoder
//CLK GPIOA1
//DT GPIOA0
//SV GPIOA2
//+ 3.3
//GND G

int state = 0;
int enableEncoder = 0;
unsigned int keypad_columns[3] = 
{
	GPIO_Pin_9,
	GPIO_Pin_10,
	GPIO_Pin_11
};
unsigned int keypad_rows[4] = 
{
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15
};

int main()
{
	init_encoder();
	TM1637_init();	
  TM1637_brightness(BRIGHT_TYPICAL);
	keypad_init(keypad_columns, keypad_rows);
  delay_ms(10);
	while (1)
	{
		char key=keypadGetKey();

		switch(key) {
			case '*':
				enableEncoder = 0;
				TM1637_display_all(state);
				break;
			case '#':
				enableEncoder = 1;
				state = 0;
				break;
			default:
				display_value(enableEncoder, key);
				
		}
		delay_ms(1);
	}
}
void display_value(int encoderEnable, char key) {
	int displayNumber = 0;
	switch(enableEncoder) {
		case KEYBOARD_ENABLED:
			displayNumber = keyboard_value(key);
			break;
		case ENCODER_ENABLED:
			displayNumber = getEncoderValue();
			break;		
	}
	
	TM1637_display_all(displayNumber);
}

int keyboard_value(char key) {
	int convert = convert_char(key);
	switch(convert) {
		case UNVALUABLE:
			break;
		case MOVE_LEFT:
			state = (state * 10) % 10000;
			break;
		default:
			state = state - (state % 10) + convert;
	}	
	return state;
}

