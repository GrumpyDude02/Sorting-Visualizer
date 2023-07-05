#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <windows.h>
#include <signal.h>
#include "my_func.h"
#include "bar.h"
#include "beeper.h"

bool end_program = false;

void handle_exit(int signal)
{
    end_program = true;
}

int main(int argc, char *argv[])
{
    signal(SIGTERM, handle_exit);
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    WindowProp dimensions = {1280, 600, 0.0, 0.0};
    SortingParams sp;
    SDL_zero(sp);
    sp.beeper = InitializeBepper(BUFFER_SIZE, AMPLITUDE, SAMPLE_RATE, CHANNELS, 440.0f);
    if (sp.beeper == NULL)
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
    while ((choice = get_choice()) != 0 && !end_program)
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
            fprintf(stdout, "ctrl-c\n");
            DetroyBeeper(sp.beeper);
            SDL_Quit();
            return -1;
        }
    }
    fprintf(stdout, "hh\n");
    DetroyBeeper(sp.beeper);
    SDL_Quit();
    return 0;
}
