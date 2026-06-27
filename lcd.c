#include <lpc214x.h>

#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"

// Write data to LCD
void Write_LCD(char data)
{
    IOCLR0 = 0xFF << LCD_DATA;

    IOSET0 = (data << LCD_DATA);

    IOSET0 = (1 << EN);

    delay_ms(2);

    IOCLR0 = (1 << EN);
}

// Send command
void Cmd_LCD(char cmd)
{
    IOCLR0 = (1 << RS);

    IOCLR0 = (1 << RW);

    Write_LCD(cmd);
}
// Send character
void Char_LCD(char ch)
{
    IOSET0 = (1 << RS);

    IOCLR0 = (1 << RW);

    Write_LCD(ch);
}

// Initialize LCD
void Init_LCD(void)
{
    IODIR0 |= (0xFF << LCD_DATA);

    IODIR0 |= (1 << RS);

    IODIR0 |= (1 << RW);

    IODIR0 |= (1 << EN);

    Cmd_LCD(MODE_8BIT_2LINE);

    Cmd_LCD(DISP_ON);

    Cmd_LCD(CLEAR_LCD);
}
// Display string
void Str_LCD(char *p)
{
    while(*p)
    {
        Char_LCD(*p++);
    }
}

// Display unsigned integer
void Uint_LCD(unsigned int n)
{
    char arr[10];

    int i = 0;

    if(n == 0)
    {
        Char_LCD('0');

        return;
    }

    while(n > 0)
    {
        arr[i++] = (n % 10) + 48;

        n /= 10;
    }
 for(i = i - 1; i >= 0; i--)
    {
        Char_LCD(arr[i]);
    }
}

// LCD cursor position
void LCD_GotoXY(unsigned int row,unsigned int col)
{
    if(row == 0)
    {
        Cmd_LCD(GOTO_LINE1_POS0 + col);
    }

    else if(row == 1)
    {
        Cmd_LCD(GOTO_LINE2_POS0 + col);
    }
}

