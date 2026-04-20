#include "game.h"
#include <stdlib.h>

led_color_t get_random_color(void)
{
    uint8_t r = rand() % 4;

    switch (r)
    {
        case 0: return RED;
        case 1: return GREEN;
        case 2: return BLUE;
        default: return YELLOW;
    }
}
