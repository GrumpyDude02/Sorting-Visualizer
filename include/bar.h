#include <SDL2/SDL.h>
#include <stdbool.h>
#include "beeper.h"

#ifndef BAR_H
#define BAR_H

typedef enum
{
    inactive,
    red,
    green,
    purple,
    blue

} color_index;

typedef struct
{
    int value;
    color_index activity;

} Bar;

#endif