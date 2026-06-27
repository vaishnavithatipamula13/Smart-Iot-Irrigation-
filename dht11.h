#ifndef DHT11_H
#define DHT11_H

#include "types.h"

// DHT11 connected to P0.10
#define DHT_PIN 10

// Functions
void DHT11_Init(void);

int DHT11_Read(u8 *temp, u8 *hum);

#endif
