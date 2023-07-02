#ifndef MY_STRUCTS
#define MY_STRUCTS

typedef enum
{
    inactive,
    compare1,
    compare2,
    pivot_element,
} color_index;

typedef struct ScreenDimensions
{
    int WIDTH;
    int HEIGHT;
    float cell_w;
    float cell_h;
    SDL_Event ev;
} WindowProp;

#endif