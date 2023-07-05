#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "application.h"

static int InitWindow(ApplicationWindow *app, SortingParams sp)
{
    app->cell_w = app->WIDTH / sp.bar_number;
    app->cell_h = app->HEIGHT / sp.bar_number;

    if (!app->beeper)
    {
        DestroyApp(app);
        fprintf(stdout, "Failed to create beeper.\n%s.\n", SDL_GetError());
        return -1;
    }

    app->window = SDL_CreateWindow("Sorting Visulizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, app->WIDTH, app->HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!app->window)
    {
        DestroyApp(app);
        fprintf(stdout, "Failed to create window.\n%s.\n", SDL_GetError());
        return -1;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (!app->renderer)
    {
        DestroyApp(app);
        fprintf(stdout, "Failed to create renderer.\n%s.\n", SDL_GetError());
        return -1;
    }

    app->bars = (Bar *)malloc(sizeof(Bar) * sp.bar_number);

    if (!app->bars)
    {
        DestroyApp(app);
        printf("Failed to allocate memory.\n");
    }

    srand(time(NULL));
    for (int i = 0; i < sp.bar_number; i++)
    {
        int val = rand() % sp.bar_number;
        app->bars[i].activity = inactive;
        app->bars[i].value = val;
    }

    app->quit = false;
    return 0;
}

static float map(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    return ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin) + outputMin;
}

void SetAppValues(ApplicationWindow *app, int width, int height)
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    app->quit = false;
    app->beeper = NULL;
    app->window = NULL;
    app->renderer = NULL;
    app->cell_h = app->cell_w = 0;
    app->WIDTH = width;
    app->HEIGHT = height;
    app->beeper = InitializeBepper(BUFFER_SIZE, AMPLITUDE, SAMPLE_RATE, 1, 440.0f);
    return;
}

void draw_bars(Bar *arr, ApplicationWindow *app, SortingParams sp)
{
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);
    for (int i = sp.start_index; i < sp.bar_number; i++)
    {
        if (arr[i].activity == red)
        {
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
            arr[i].activity = inactive;
            float f = map(arr[i].value, 0, sp.bar_number * 2, 50.f, 1200.f);
            AddTone(app->beeper, f);
            BeepSound(app->beeper, 0, 0);
        }
        else if (arr[i].activity == green)
        {
            SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255);
            arr[i].activity = inactive;
        }
        else if (arr[i].activity == purple)
        {
            SDL_SetRenderDrawColor(app->renderer, 255, 0, 255, 255);
            arr[i].activity = inactive;
            float f = map(arr[i].value, 0, sp.bar_number * 2, 50.f, 1200.f);
            AddTone(app->beeper, f);
            BeepSound(app->beeper, 0, 0);
        }
        else
        {
            SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
        }
        SDL_FRect r = {(float)i * app->cell_w - 1.0, (float)app->HEIGHT - (float)arr[i].value * app->cell_h, app->cell_w, (float)arr[i].value * app->cell_h};
        SDL_RenderFillRectF(app->renderer, &r);
    }
    SDL_RenderPresent(app->renderer);
    SDL_Delay(sp.duration);
    SDL_PauseAudioDevice(app->beeper->device, 1);
}

int loop(ApplicationWindow *app, int choice, SortingParams sp, SortingAlgorithm *sort_alg)
{
    if (InitWindow(app, sp) == -1)
    {
        return -1;
    }

    bool sorting_done = false;

    while (!app->quit)
    {
        SDL_PollEvent(&app->ev);
        if (app->ev.type == SDL_QUIT)
        {
            app->quit = true;
        }
        if (!sorting_done)
        {
            sort_alg[choice - 1].sort(app->bars, app, sp);
            sorting_done = true;
        }
        else
        {
            draw_bars(app->bars, app, sp);
        }
    }
    Deallocate(app);
    system("cls");
    return 0;
}

void Deallocate(ApplicationWindow *app)
{
    if (app->window)
    {
        SDL_DestroyWindow(app->window);
        app->window = NULL;
    }
    if (app->renderer)
    {
        SDL_DestroyRenderer(app->renderer);
        app->renderer = NULL;
    }
    if (app->bars)
    {
        free(app->bars);
        app->bars = NULL;
    }
    return;
}

void DestroyApp(ApplicationWindow *app)
{
    Deallocate(app);
    DestroyBeeper(app->beeper);
    app->beeper = NULL;
    if (SDL_WasInit(0))
    {
        fprintf(stdout, "Quitting SDL\n");
        SDL_Quit();
    }
    return;
}