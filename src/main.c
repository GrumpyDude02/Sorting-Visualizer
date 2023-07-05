#include <stdio.h>
#include <SDL2/SDL.h>
#include <signal.h>
#include "tools.h"
#include "application.h"
#include "sorting.h"

bool exit_program = false;
ApplicationWindow app;

void catch_sig(int sig)
{
    exit_program = true;
    fprintf(stdout, "\nCtrl-C pressed\n");
    DestroyApp(&app);
    exit(0);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, &catch_sig);
    SortingParams sp;
    SDL_zero(sp);
    SetAppValues(&app, 1200, 600);
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
            sp.bar_number = get_int("enter the number of bars (max = 600): ");
        } while (sp.bar_number <= 0 || sp.bar_number > 600);
        sp.start_index = 0;
        sp.end_index = sp.bar_number - 1;
        do
        {
            sp.duration = get_int("enter the delay duration (max = 100): ");
        } while (sp.duration < 0 || sp.duration > 100);
        if (loop(&app, choice, sp, sort) == -1)
        {
            return -1;
        }
    }
    DestroyApp(&app);
    return 0;
}
