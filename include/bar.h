#include <SDL2/SDL.h>
#include <stdbool.h>
#include "beeper.h"
#include "my_structs.h"

#ifndef BAR_H
#define BAR_H

typedef struct
{
    int value;
    color_index activity;
} Bar;

typedef struct
{
    int start_index;
    int middle;
    int end_index;
    int bar_number;
    int duration;
    Beeper *beeper;
} SortingParams;

void swap(Bar *b1, Bar *b2);
void draw_bars(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp);
//-----------------------------sorting algorithms-------------------------
//---qudratic algorithms-----
void bubble_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);
void selection_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);
void insertion_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);
void cocktail_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);
void gnome_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);
void odd_even_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);

//--logarithmic algorithms---
void quick_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);
void merge_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit);

// bogo sort for fun
void bogo_sort();
#endif