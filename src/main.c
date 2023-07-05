#include <stdio.h>
#include <SDL2/SDL.h>
#include <signal.h>
#include "tools.h"
#include "application.h"
#include "sorting.h"

bool exit_program = false;
ApplicationWindow app;

void close_programm(void)
{
    DestroyApp(&app);
}

int main(int argc, char *argv[])
{
    atexit(&close_programm);
    SetAppValues(&app, 1200, 600);
    SortingParams sp;
    SDL_zero(sp);
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
            sp.bar_number = get_int("Enter the number of bars (max = 600): ");
        } while (sp.bar_number <= 0 || sp.bar_number > 600);
        sp.start_index = 0;
        sp.end_index = sp.bar_number - 1;
        do
        {
            sp.duration = get_int("Enter the delay duration (max = 100): ");
        } while (sp.duration < 0 || sp.duration > 100);
        if (loop(&app, choice, sp, sort) == -1)
        {
            exit(-1);
        }
    }
    exit(0);
}
