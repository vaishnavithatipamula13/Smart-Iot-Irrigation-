#include <lpc214x.h>

#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "delay.h"
#include "interrupt.h"
#include "menu.h"
#include "config.h"
#include "uart.h"
#include "dht11.h"

// Interrupt flag
int menu_flag = 0;

// Irrigation logic
void Irrigation_Control(u8 temp, u8 hum)
{
    int duration = 0;

    // High temp + low humidity
    if(temp > 32 && hum < 60)
    {
        duration = 5;
    }

    // Medium condition
    else if(temp > 30 && hum < 70)
    {
        duration = 3;
    }

    else
    {
        duration = 0;
    }

    // Motor ON/OFF
    if(duration > 0)
    {
        IOCLR0 = (1 << MOTOR_LED);

        delay_s(duration);
			IOSET0 = (1 << MOTOR_LED);
    }

    else
    {
        IOSET0 = (1 << MOTOR_LED);
    }
}

// Main
int main(void)
{
	 u8 temp, hum;
    // Initialization
    RTC_Init();

    Init_LCD();

    initKPM();

    Interrupt_Init();

    UART0_Init();

    DHT11_Init();

    // Motor LED pin
    IODIR0 |= (1 << MOTOR_LED);

    IOSET0 |= (1 << MOTOR_LED);

    // Sensor variables
   // u8 temp, hum;

    while(1)
    {
        // Open menu
        if(menu_flag)
        {
            menu_flag = 0;

            VICIntEnClr = (1 << EINT1_VIC_CHNO);

            Menu_Setup();

            Cmd_LCD(CLEAR_LCD);
					EXTINT = (1 << 1);

            VICIntEnable = (1 << EINT1_VIC_CHNO);
        }

        // Display RTC
        RTC_DisplayAll();

        // Read DHT11
        if(DHT11_Read(&temp, &hum))
        {
            // Humidity
            LCD_GotoXY(1,0);

            Str_LCD("H:");

            Uint_LCD(hum);

            // Temperature
            LCD_GotoXY(1,10);

            Uint_LCD(temp);

            Char_LCD('C');

            // Irrigation control
            Irrigation_Control(temp, hum);
        }

        delay_ms(1000);
    }
}
