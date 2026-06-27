#include <lpc214x.h>
#include "dht11.h"
#include "delay.h"

// Initialize DHT11
void DHT11_Init(void)
{
    IODIR0 |= (1 << DHT_PIN);
}

// Send start signal
static void DHT11_Start(void)
{
    IODIR0 |= (1 << DHT_PIN);

    // Pull LOW
    IOCLR0 = (1 << DHT_PIN);

    delay_ms(20);

    // Pull HIGH
    IOSET0 = (1 << DHT_PIN);

    delay_us(30);

    // Input mode
    IODIR0 &= ~(1 << DHT_PIN);
}
// Check response
static int DHT11_Response(void)
{
    int timeout = 0;

    // Wait for LOW
    while(IOPIN0 & (1 << DHT_PIN))
    {
        if(timeout++ > 10000)
            return 0;
    }

    // Wait for HIGH
    while(!(IOPIN0 & (1 << DHT_PIN)));

    // Wait for LOW
    while(IOPIN0 & (1 << DHT_PIN));

    return 1;
}

// Read one byte
static u8 DHT11_ReadByte(void)
{
    u8 i;
    u8 data = 0;

    for(i = 0; i < 8; i++)
    {
// Wait for HIGH
        while(!(IOPIN0 & (1 << DHT_PIN)));

        delay_us(40);

        // Check bit
        if(IOPIN0 & (1 << DHT_PIN))
        {
            data |= (1 << (7 - i));
        }

        // Wait for LOW
        while(IOPIN0 & (1 << DHT_PIN));
    }

    return data;
}

// Read temp & humidity
int DHT11_Read(u8 *temp, u8 *hum)
{
    u8 h_int, h_dec;
    u8 t_int, t_dec;
    u8 checksum;

    DHT11_Start();

    if(!DHT11_Response())
        return 0;
// Read data
    h_int = DHT11_ReadByte();
    h_dec = DHT11_ReadByte();

    t_int = DHT11_ReadByte();
    t_dec = DHT11_ReadByte();

    checksum = DHT11_ReadByte();

    // Verify checksum
    if((h_int + h_dec + t_int + t_dec) != checksum)
        return 0;

    *temp = t_int;
    *hum  = h_int;

    return 1;
}
