#ifndef RTC_H
#define RTC_H

#include "types.h"

// Oscillator frequency
#define FOSC 12000000

// CPU clock
#define CCLK (5 * FOSC)

// Peripheral clock
#define PCLK (CCLK / 4)

// RTC prescaler
#define PREINT_VAL (s32)((PCLK / 32768) - 1)

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))

// RTC control bits
#define RTC_ENABLE (1<<0)

#define RTC_RESET  (1<<1)

// Weekdays
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

// Global RTC variables
extern s32 hour, min, sec;

extern s32 date, month, year;

extern s32 day;

// RTC functions
void RTC_Init(void);

void GetRTCTimeInfo(s32*,s32*,s32*);
void GetRTCDateInfo(s32*,s32*,s32*);
void GetRTCDay(s32*);

void DisplayRTCTime(u32,u32,u32);
void DisplayRTCDate(u32,u32,u32);
void DisplayRTCDay(u32);

void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);
void SetRTCDay(u32);

void RTC_SetInitial(void);

void RTC_UpdateTime(void);void RTC_UpdateDate(void);
void RTC_UpdateDay(void);

// Wrapper function
void RTC_DisplayAll(void);

#endif

