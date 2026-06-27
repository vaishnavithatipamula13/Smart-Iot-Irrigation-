#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "rtc.h"

// Menu function
void Menu_Setup(void)
{
    char key;

    while(1)
    {
        Cmd_LCD(GOTO_LINE1_POS0);

        Str_LCD("1.TIME 2.DATE");

        Cmd_LCD(GOTO_LINE2_POS0);

        Str_LCD("3.EXIT");

        if(colscan() == 0)
        {
            key = keyscan();

            if(key == '1')
            {
                RTC_UpdateTime();

                Cmd_LCD(CLEAR_LCD);
 }

            else if(key == '2')
            {
                RTC_UpdateDate();

                RTC_UpdateDay();

                Cmd_LCD(CLEAR_LCD);
            }

            else if(key == '3')
            {
                break;
            }
        }
    }
}
