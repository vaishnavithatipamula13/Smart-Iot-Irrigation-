#ifndef LCD_DEFINES_H
#define LCD_DEFINES_H

// LCD DATA PINS
#define LCD_DATA 8

// CONTROL PINS
#define RS 16
#define RW 17
#define EN 18

// LCD COMMANDS
#define CLEAR_LCD 0x01

#define RET_CUR_HOME 0x02

#define DISP_ON 0x0C

#define DISP_OFF 0x08

#define MODE_8BIT_2LINE 0x38

#define GOTO_LINE1_POS0 0x80

#define GOTO_LINE2_POS0 0xC0

#endif
