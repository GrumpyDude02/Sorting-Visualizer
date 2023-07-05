#include "my_func.h"

int get_int(char *text)
{
    int temp;
    char buffer[20];
    do
    {
        fprintf(stdout, "%s", text);
        fgets(buffer, 19, stdin);
    } while (sscanf(buffer, "%d", &temp) != 1);
    return temp;
}

int get_choice(void)
{
    int choice;
    fprintf(stdout, "(0).Quit\n");
    fprintf(stdout, "(1).Bubble Sort\n");
    fprintf(stdout, "(2).Quick Sort\n");
    fprintf(stdout, "(3).Selection Sort\n");
    fprintf(stdout, "(4).Merge Sort\n");
    fprintf(stdout, "(5).Insertion Sort\n");
    fprintf(stdout, "(6).Cocktail Sort\n");
    fprintf(stdout, "(7).Gnome Sort\n");
    fprintf(stdout, "(8).Odd-Even Sort\n");
    fprintf(stdout, "(9).Shell Sort\n");
    fprintf(stdout, "(10).Bogo Sort\n");
    do
    {
        choice = get_int("Select the desired sorting algorithm : ");

    } while (choice < 0 || choice > 10);
    return choice;
}

int render_window(WindowProp dimensions, int choice, SortingParams sp, SortingAlgorithm *sort_alg)
{

    Bar *bars = (Bar *)malloc(sizeof(Bar) * sp.bar_number);

    if (!bars)
        return -1;

    SDL_Window *window = SDL_CreateWindow("Sorting Visulizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimensions.WIDTH, dimensions.HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window)
    {
        printf("failed to initilize window\n");
        return -1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        printf("Renderer Error\n");
        return -1;
    }

    SDL_Event ev;
    bool quit = false, done_sorting = false;

    srand(time(NULL));
    for (int i = 0; i < sp.bar_number; i++)
    {
        int val = rand() % sp.bar_number;
        bars[i].activity = inactive;
        bars[i].value = val;
    }
    while (!quit)
    {
        SDL_PollEvent(&ev);
        if (ev.type == SDL_QUIT)
        {
            quit = true;
        }
        if (!done_sorting)
        {
            sort_alg[choice - 1].sort(bars, renderer, dimensions, sp, &quit);
            done_sorting = true;
        }
        else
        {
            draw_bars(bars, renderer, dimensions, sp);
        }
    }
    free(bars);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    system("cls");
    return 0;
}