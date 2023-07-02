#include <stdio.h>
#include "my_func.h"
#include "bar.h"

int main(int argc, char *argv[])
{
    WindowProp dimensions = {1280, 600, 0.0, 0.0};
    SortingParams sp;
    SortingAlgorithm sort[] = {
        {bubble_sort},
        {quick_sort},
        {selection_sort},
        {merge_sort},
        {insertion_sort},
        {cocktail_sort}};
    int choice;
    while ((choice = get_choice()) != 0)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        do
        {
            sp.bar_number = get_int("Enter the number of bars (max = 600) : ");
        } while (sp.bar_number < 0 || sp.bar_number > 600);

        dimensions.cell_h = dimensions.HEIGHT / (float)sp.bar_number;
        dimensions.cell_w = dimensions.WIDTH / (float)sp.bar_number;
        sp.start_index = 0;
        sp.end_index = sp.bar_number - 1;

        if (render_window(dimensions, choice, sp, sort) == -1)
        {
            SDL_Quit();
        }
        SDL_Quit();
    }
    return 0;
}