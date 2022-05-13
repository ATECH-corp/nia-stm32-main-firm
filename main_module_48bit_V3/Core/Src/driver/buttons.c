#include "stm32h7xx_hal.h"
#include "buttons.h"

static uint32_t button_pushed;
static uint8_t button_is_locked;

void buttons_loop(){

	static uint8_t init = 0;

	if(init == 0){
		init = 1;
		button_pushed = 0;
	}

	uint16_t buttons = (uint16_t)(GPIOD->IDR & 0xFF00) | (uint16_t)(GPIOE->IDR >> 8);

	if(buttons & 0x0080) button_pushed += 1;
	else button_pushed = 0;

	button_is_locked = (buttons & 0x8000) ? 1 : 0;
}

uint32_t button_push_time(){
	return button_pushed;
}

void button_reset(){
	button_pushed = 0;
}

uint8_t button_locked(){
	return button_is_locked;
}
