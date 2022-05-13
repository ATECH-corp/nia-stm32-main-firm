/*
 * buttons.h
 *
 *  Created on: Jan 4, 2022
 *      Author: YJ
 */

#ifndef SRC_DRIVER_BUTTONS_H_
#define SRC_DRIVER_BUTTONS_H_

#include "stdint.h"

extern void buttons_loop();
extern uint32_t button_push_time();
extern void button_reset();
extern uint8_t button_locked();

#endif /* SRC_DRIVER_BUTTONS_H_ */
