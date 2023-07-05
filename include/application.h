#include <stdio.h>
#include <time.h>
#include "beeper.h"
#include "bar.h"

#ifndef MY_STRUCTS
#define MY_STRUCTS

typedef struct
{
    int WIDTH;
    int HEIGHT;
    float cell_w;
    float cell_h;
    bool quit;
    SDL_Event ev;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Beeper *beeper;
    Bar *bars;

} ApplicationWindow;

typedef struct
{
    int start_index;
    int middle;
    int end_index;
    int bar_number;
    int duration;

} SortingParams;

typedef struct
{
    void (*sort)(Bar *, ApplicationWindow *, SortingParams);
} SortingAlgorithm;

void SetAppValues(ApplicationWindow *app, int WIDTH, int HEIGHT);
void draw_bars(Bar *arr, ApplicationWindow *app, SortingParams sp);
int loop(ApplicationWindow *app, int choice, SortingParams sp, SortingAlgorithm *sort_alg);
void Deallocate(ApplicationWindow *app);
void DestroyApp(ApplicationWindow *app);

#endif