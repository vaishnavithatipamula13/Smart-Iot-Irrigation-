#include <lpc214x.h>
#include "uart.h"

// Global variable for received data
volatile char rx_data;

// UART0 Interrupt Service Routine
void uart0_isr(void) __irq
{
    unsigned int iir;

    iir = U0IIR;

    // Check RX interrupt
    if((iir & 0x0E) == 0x04)
    {
        rx_data = U0RBR;
    }

    VICVectAddr = 0;
}

// UART initialization
void UART0_Init(void)
{
    // Configure P0.0 as TXD0
    // Configure P0.1 as RXD0
    PINSEL0 &= ~((3<<0) | (3<<2));
    PINSEL0 |=  ((1<<0) | (1<<2));

    // 8-bit, 1 stop bit, DLAB enabled
    U0LCR = 0x83;

    // Baud rate setup
    U0DLL = DLL_VALUE;
    U0DLM = DLM_VALUE;

    // Disable DLAB
    U0LCR = 0x03;

    // Enable RX interrupt
    U0IER = (1<<0);

    // VIC configuration
    VICIntSelect &= ~(1<<6);

    VICVectCntl1 = (1<<5) | 6;

    VICVectAddr1 = (unsigned int)uart0_isr;
VICIntEnable |= (1<<6);
}

// Send single character
void UART0_TxChar(char ch)
{
    while(!(U0LSR & (1<<5)));

    U0THR = ch;
}

// Send string
void UART0_TxString(char *str)
{
    while(*str)
    {
        UART0_TxChar(*str++);
    }
}
