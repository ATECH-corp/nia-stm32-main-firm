/*
 * leds.h
 *
 *  Created on: Jan 4, 2022
 *      Author: YJ
 */

#ifndef SRC_DRIVER_LEDS_H_
#define SRC_DRIVER_LEDS_H_

#include <stdint.h>

extern void leds_off();
extern void leds_on();
extern void leds_toggle();

extern void led_on(uint8_t n);
extern void led_off(uint8_t n);
extern void led_toggle(uint8_t n);

extern void leds_loop();

#endif /* SRC_DRIVER_LEDS_H_ */
