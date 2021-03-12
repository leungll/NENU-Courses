/******************************************************************************
**                                                                           **
**  Copyright (c) 2000 ARM Limited                                           **
**  All rights reserved                                                      **
**                                                                           **
******************************************************************************/


/*****************************************************************************/
/* Local routine variables and defines                                       */
/*****************************************************************************/

#define IRQVector (unsigned *) 0x18

#define BIN_COUNT     0
#define LEFT_SHIFT    1
#define ALTERNATE     2
#define RIGHT_SHIFT   3

#define SLOW     0
#define SLOW_MED 1
#define MED_FAST 2
#define FAST     3

#define SLOW_LOAD     0xffff
#define SLOW_MED_LOAD 0xaaaa
#define MED_FAST_LOAD 0x5555
#define FAST_LOAD     0x0fff

#define FLASH_DEF     0 

#define MAX_LED_VAL   8
#define MIN_LED_VAL   1
#define SHIFT_VALUE   1
#define INIT_VALUE    1
#define MAX_BIN_COUNT 15

#define SPEED_MASK    0xf3
#define SEQUENCE_MASK 0xfc
#define SEQUENCE_SHIFT   2
#define ALT_RIGHT     0x05
#define ALT_LEFT      0x0a
#define WRITE_SETUP_DELAY 1000
#define LED_START_OFFSET  4
#define SWITCH_NIBBLE_MASK 0x0f
#define IRQSourcePAR       0x400

#define VADEM_READ_OFFSET    24
#define BYTE_MASK          0xff


extern int IntCT1;
extern int IntCT2;

