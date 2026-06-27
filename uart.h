#ifndef UART_H
#define UART_H

#include "types.h"
#include "rtc.h"

// Baud rate
#define BAUD 9600

// Baud calculations
#define DLL_VALUE ((PCLK / (16 * BAUD)) & 0xFF)
#define DLM_VALUE ((PCLK / (16 * BAUD)) >> 8)

// UART functions
void UART0_Init(void);
void UART0_TxChar(char ch);
void UART0_TxString(char *str);

// UART ISR
void uart0_isr(void) __irq;

// Received character
extern volatile char rx_data;

#endif
