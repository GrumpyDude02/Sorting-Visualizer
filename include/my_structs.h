#ifndef MY_STRUCTS
#define MY_STRUCTS

typedef enum
{
    inactive,
    red,
    green,
    purple,
    blue,
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