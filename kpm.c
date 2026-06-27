#include <lpc214x.h>

#include "kpm_defines.h"
#include "delay.h"
#include "lcd.h"

// Keypad layout
char keypad[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// Initialize keypad
void initKPM(void)
{
    // Rows output
    IODIR1 |= (1<<R0) | (1<<R1) | (1<<R2) | (1<<R3);

    // Columns input
    IODIR1 &= ~((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));
}

// Check column press
unsigned int colscan(void)
{
    return ((IOPIN1 >> 20) & 0x0F);
}

// Row check
unsigned int rowcheck(void)
{
    int row;

    for(row = 0; row < 4; row++)
    {
        IOSET1 = (0x0F << 16);

        IOCLR1 = (1 << (16 + row));

        if(colscan() != 0x0F)
        {
            return row;
        }
    }

    return 0xFF;
}

// Column check
unsigned int colcheck(void)
{
    if(!(IOPIN1 & (1<<C0))) return 0;

    if(!(IOPIN1 & (1<<C1))) return 1;
 if(!(IOPIN1 & (1<<C2))) return 2;

    if(!(IOPIN1 & (1<<C3))) return 3;

    return 0xFF;
}

// Scan keypad
unsigned int keyscan(void)
{
    unsigned int row,col;

    row = rowcheck();

    col = colcheck();

    while(colscan() != 0x0F);

    return keypad[row][col];
}

// Read number
int ReadNum(void)
{
    int num = 0;

    char key;

    while(1)
{
        while(colscan() == 0x0F);

        key = keyscan();

        if(key >= '0' && key <= '9')
        {
            Char_LCD(key);

            num = (num * 10) + (key - 48);
        }

        else if(key == '#')
        {
            break;
        }
    }

    return num;
}
