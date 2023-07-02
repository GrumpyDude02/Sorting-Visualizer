#include <time.h>
#include <stdio.h>
#include "bar.h"
#ifndef MYFUNC_H
#define MYFUNC_H

typedef struct
{
    void (*sort)(Bar *, SDL_Renderer *, WindowProp, SortingParams, bool *);
} SortingAlgorithm;

int get_int(char *text);

int get_choice(void);

int render_window(WindowProp dimensions, int choice, SortingParams sp, SortingAlgorithm *sort);
#endif