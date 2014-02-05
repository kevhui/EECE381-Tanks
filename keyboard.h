/*
 * keyboard.h
 *
 *  Created on: 2014-02-02
 *      Author: Kevin
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "system.h"
#include "player.h"
#include <alt_legacy_irq.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "nios2_ctrl_reg_macros.h"

void initKeyboard();

#endif /* KEYBOARD_H_ */
