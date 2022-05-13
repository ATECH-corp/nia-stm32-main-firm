#include "stm32h7xx_hal.h"

static uint32_t led_on_arr[8] = {
			0x00000080, 0x00000040, 0x00000020, 0x00000010,
			0x00000008, 0x00000004, 0x00000002, 0x00000001,
};

static uint32_t led_off_arr[8] = {
			0x00800000, 0x00400000, 0x00200000, 0x00100000,
			0x00080000, 0x00040000, 0x00020000, 0x00010000,
};

static uint8_t led_state[8]; // 0 : off, 1 : on, 2 : toggle
static uint8_t led_state_req[8];
static uint8_t led_request;

void write_leds(uint8_t val[8]){
	uint32_t bsrr = 0;

	for(int i = 0; i < 8; i++){
		if(val[i] == 1) bsrr |= led_on_arr[i];
		else bsrr |= led_off_arr[i];
	}

	GPIOG->BSRR = bsrr;
}

void leds_off(){
	led_state_req[0] = 0;
	led_state_req[1] = 0;
	led_state_req[2] = 0;
	led_state_req[3] = 0;
	led_state_req[4] = 0;
	led_state_req[5] = 0;
	led_state_req[6] = 0;
	led_state_req[7] = 0;
	led_request = 1;
}

void leds_on(){
	led_state_req[0] = 1;
	led_state_req[1] = 1;
	led_state_req[2] = 1;
	led_state_req[3] = 1;
	led_state_req[4] = 1;
	led_state_req[5] = 1;
	led_state_req[6] = 1;
	led_state_req[7] = 1;
	led_request = 1;
}

void leds_toggle(){
	led_state_req[0] = 2;
	led_state_req[1] = 2;
	led_state_req[2] = 2;
	led_state_req[3] = 2;
	led_state_req[4] = 2;
	led_state_req[5] = 2;
	led_state_req[6] = 2;
	led_state_req[7] = 2;
	led_request = 1;
}

void led_on(uint8_t n){
	if(n > 7) return;
	led_state_req[n] = 1;
	led_request = 1;
}

void led_off(uint8_t n){
	if(n > 7) return;
	led_state_req[n] = 0;
	led_request = 1;
}

void led_toggle(uint8_t n){
	if(n > 7) return;
	led_state_req[n] = 2;
	led_request = 1;
}

void leds_loop(){ // ms

	static uint8_t init = 0;
	static uint32_t loop_time = 0;

	int i;
	uint32_t bsrr;

	if(init == 0){

		for(i = 0; i < 8; i++){
			led_state[i] = 0;
			led_state_req[i] = 0;
		}

		led_request = 0;
		GPIOG->BSRR = 0x00FF0000; // All led off
		init = 1;
	}

	loop_time += 1;

	if(loop_time > 12500){
		loop_time = 0;
		bsrr = 0;

		for(i = 0; i < 8; i++){
			if(led_state[i] ==  2){
				led_state[i] = 3;
				bsrr |= led_on_arr[i];
			}else if(led_state[i] == 3){
				led_state[i] = 2;
				bsrr |= led_off_arr[i];
			}
		}

		GPIOG->BSRR = bsrr;
	}

	if(led_request == 1){
		led_request = 0;
		bsrr = 0;

		for(i = 0; i < 8; i++){
			if(led_state[i] != led_state_req[i]){
				led_state[i] = led_state_req[i];
				if(led_state[i] == 0) bsrr |= led_off_arr[i];
				else if(led_state[i] == 1) bsrr|= led_on_arr[i];
			}
		}

		GPIOG->BSRR = bsrr;
	}

}
