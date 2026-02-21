#include "independent_key.h"

unsigned char independent_key_scan(void)
{
    // Implement key scanning logic here
    unsigned char key_value = 0;
    if (P3_1 == 0)
    {
        delay_for_ms(20);
        while (P3_1 == 0);
        delay_for_ms(20);
        key_value = 1; // Key 1 pressed
    }

    if (P3_0 == 0)
    {
        delay_for_ms(20);
        while (P3_0 == 0);
        delay_for_ms(20);
        key_value = 2; // Key 2 pressed
    }

    if (P3_2 == 0)
    {
        delay_for_ms(20);
        while (P3_2 == 0);
        delay_for_ms(20);
        key_value = 3; // Key 3 pressed
    }

    if (P3_3 == 0)
    {
        delay_for_ms(20);
        while (P3_3 == 0);
        delay_for_ms(20);
        key_value = 4; // Key 4 pressed
    }

    return key_value; // Return the key value pressed
}