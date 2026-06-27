#include <lpc214x.h>

#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"

// RTC global variables
s32 hour, min, sec;

s32 date, month, year;

s32 day;

// RTC initialization
void RTC_Init(void)
{
    CCR = RTC_RESET;

    PREINT = PREINT_VAL;

    PREFRAC = PREFRAC_VAL;

    RTC_SetInitial();

    CCR = RTC_ENABLE;
}

// Set initial RTC values
void RTC_SetInitial(void)
{
    HOUR = 10;
    MIN  = 30;
    SEC  = 0;

    DOM   = 1;
    MONTH = 1;
    YEAR  = 2025;

    DOW = MON;
}

// Read time
void GetRTCTimeInfo(s32 *h,s32 *m,s32 *s)
{
    *h = HOUR;
    *m = MIN;
    *s = SEC;
}

// Read date
void GetRTCDateInfo(s32 *d,s32 *m,s32 *y)
{
    *d = DOM;
    *m = MONTH;
    *y = YEAR;
}

// Read day
void GetRTCDay(s32 *d)
{
    *d = DOW;
}

// Display time
void DisplayRTCTime(u32 h,u32 m,u32 s)
{
    Cmd_LCD(GOTO_LINE1_POS0);

    Uint_LCD(h);

    Char_LCD(':');

    Uint_LCD(m);

    Char_LCD(':');

    Uint_LCD(s);
}

// Display date
void DisplayRTCDate(u32 d,u32 m,u32 y)
{
    Cmd_LCD(GOTO_LINE2_POS0);

    Uint_LCD(d);

    Char_LCD('/');

    Uint_LCD(m);

    Char_LCD('/');

    Uint_LCD(y);
}

// Display weekday
void DisplayRTCDay(u32 d)
{
    Cmd_LCD(GOTO_LINE1_POS0 + 12);

    switch(d)
    {
        case SUN: Str_LCD("SUN"); break;
        case MON: Str_LCD("MON"); break;
        case TUE: Str_LCD("TUE"); break;
        case WED: Str_LCD("WED"); break;
        case THU: Str_LCD("THU"); break;
        case FRI: Str_LCD("FRI"); break;
        case SAT: Str_LCD("SAT"); break;
    }
}

// Set time
void SetRTCTimeInfo(u32 h,u32 m,u32 s)
{
    HOUR = h;
    MIN  = m;
    SEC  = s;
}

// Set date
void SetRTCDateInfo(u32 d,u32 m,u32 y)
{
    DOM   = d;
    MONTH = m;
YEAR  = y;
}

// Set weekday
void SetRTCDay(u32 d)
{
    DOW = d;
}

// Update time through keypad
void RTC_UpdateTime(void)
{
    Cmd_LCD(CLEAR_LCD);

    Str_LCD("HHMMSS:");

    Cmd_LCD(GOTO_LINE2_POS0);

    hour = ReadNum();

    min = ReadNum();

    sec = ReadNum();

    SetRTCTimeInfo(hour,min,sec);
}

// Update date
void RTC_UpdateDate(void)
{
    Cmd_LCD(CLEAR_LCD);

    Str_LCD("DDMMYYYY:");

    Cmd_LCD(GOTO_LINE2_POS0);

    date = ReadNum();

    month = ReadNum();

    year = ReadNum();

    SetRTCDateInfo(date,month,year);
}
// Update weekday
void RTC_UpdateDay(void)
{
    Cmd_LCD(CLEAR_LCD);

    Str_LCD("DAY(0-6):");

    Cmd_LCD(GOTO_LINE2_POS0);

    day = ReadNum();

    SetRTCDay(day);
}

// Wrapper function
void RTC_DisplayAll(void)
{
    GetRTCTimeInfo(&hour,&min,&sec);

    GetRTCDateInfo(&date,&month,&year);

    GetRTCDay(&day);

    DisplayRTCTime(hour,min,sec);

    DisplayRTCDay(day);

    DisplayRTCDate(date,month,year);
}

