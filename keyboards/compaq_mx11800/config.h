/*
Copyright 2021 keebnewb

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x049F
#define PRODUCT_ID   0x000E
#define DEVICE_VER   0x0001
#define MANUFACTURER Compaq Computer Corporation
#define PRODUCT      COMPAQ MC-11800

// Add teensy core
#define CORE_TEENSY

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, A5, A6, A7 }
#define MATRIX_COL_PINS { F6, F7, E0, E1, C0, C1, C2, C3, C4, C5, C6, C7, F5, F4, F3, F2 }
// LED PINS are B7, D6, D7
#define UNUSED_PINS { B6, B5, B4, B4, B2, B1, B0, D0, D1, D3, D4, E7, E6, E5, E4, F1, F0 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

//#define LED_NUM_LOCK_PIN B0
//#define LED_CAPS_LOCK_PIN B1
//#define LED_SCROLL_LOCK_PIN B2
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// This is the default EEPROM max address to use for dynamic keymaps.
// The default is the Teensy 2.0++ EEPROM max address.
// Explicitly override it if the keyboard uses a microcontroller with
// more or less EEPROM.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4095

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 13

// Leds at start bootmagic
#define BOOTMAGIC_LEDSEQ_COUNT 3
#define BOOTMAGIC_LEDSEQ_STEP 200

// Layer led blink time
#define LAYER_BLINK_TIME 200

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// Applies a transformation to the movement before sending to the host (see link)
#define PS2_MOUSE_USE_2_1_SCALING

// Define a lower presition for move
#define PS2_MOUSE_X_MULTIPLIER 3
#define PS2_MOUSE_Y_MULTIPLIER 3
#define PS2_MOUSE_V_MULTIPLIER 1

// Define a higher presition on scroll
#define PS2_MOUSE_SCROLL_DIVISOR_H 3
#define PS2_MOUSE_SCROLL_DIVISOR_V 3

// Swap left/rigth mouse buttons
#define REMAP_MOUSE_BTN_LEFT (PS2_MOUSE_BTN_RIGHT)
#define REMAP_MOUSE_BTN_RIGHT (PS2_MOUSE_BTN_LEFT)

// Define Scroll button (this is the button after remap)
#define PS2_MOUSE_SCROLL_BTN_MASK (1 << PS2_MOUSE_BTN_RIGHT)

/* PS2/Mouse configuration */
#ifdef PS2_USE_USART
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif
