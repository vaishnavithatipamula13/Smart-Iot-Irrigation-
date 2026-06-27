#include <lpc214x.h>
#include "interrupt.h"
#include "config.h"

// Variable from main.c
extern int menu_flag;

// Interrupt initialization
void Interrupt_Init(void)
{
    // Configure P0.3 as EINT1
    PINSEL0 &= ~(3<<6);
    PINSEL0 |=  (3<<6);

    // Clear interrupt flag
    EXTINT = (1<<1);

    // Edge trigger
    EXTMODE |= (1<<1);

    // Falling edge
    EXTPOLAR &= ~(1<<1);

    // IRQ mode
    VICIntSelect &= ~(1<<EINT1_VIC_CHNO);

    // VIC slot setup
    VICVectCntl0 = (1<<5) | EINT1_VIC_CHNO;
VICVectAddr0 = (unsigned int)eint1_isr;

    // Enable interrupt
    VICIntEnable |= (1<<EINT1_VIC_CHNO);
}

// ISR
void eint1_isr(void) __irq
{
    menu_flag = 1;

    EXTINT = (1<<1);

    VICVectAddr = 0;
}
