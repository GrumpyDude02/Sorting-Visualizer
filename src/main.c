#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "my_func.h"
#include "bar.h"
#include "beeper.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    WindowProp dimensions = {1280, 600, 0.0, 0.0};
    SortingParams sp;
    SDL_zero(sp);
    Beeper *beep = InitializeBepper(BUFFER_SIZE, AMPLITUDE, SAMPLE_RATE, CHANNELS, 440.0f);
    sp.beeper = beep;
    if (beep == NULL)
        return -1;
    SortingAlgorithm sort[] = {
        {bubble_sort},
        {quick_sort},
        {selection_sort},
        {merge_sort},
        {insertion_sort},
        {cocktail_sort},
        {gnome_sort},
        {odd_even_sort},
        {shell_sort},
        {bogo_sort}};
    int choice;
    while ((choice = get_choice()) != 0)
    {
        do
        {
            sp.bar_number = get_int("Enter the number of bars (max = 600) : ");
        } while (sp.bar_number < 0 || sp.bar_number > 600);

        do
        {
            sp.duration = get_int("Enter the delay duration (max = 100): ");
        } while (sp.duration < 0 || sp.duration > 100);

        dimensions.cell_h = dimensions.HEIGHT / (float)sp.bar_number;
        dimensions.cell_w = dimensions.WIDTH / (float)sp.bar_number;
        sp.start_index = 0;
        sp.end_index = sp.bar_number - 1;
        if (render_window(dimensions, choice, sp, sort) == -1)
        {
            DetroyBeeper(beep);
            SDL_Quit();
            return -1;
        }
    }
    DetroyBeeper(beep);
    SDL_Quit();
    return 0;
}
