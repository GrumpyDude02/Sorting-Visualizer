#include "bar.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(Bar *b1, Bar *b2)
{
    Bar temp = *b1;
    *b1 = *b2;
    *b2 = temp;
}

static float map(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    return ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin) + outputMin;
}

bool check_exit(SDL_Event *ev, bool *quit)
{
    SDL_PollEvent(ev);
    if (ev->type == SDL_QUIT)
    {
        *quit = true;
        return true;
    }
    return false;
}

void draw_bars(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp)
{
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    for (int i = sp.start_index; i < sp.bar_number; i++)
    {
        if (arr[i].activity == red)
        {
            SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
            arr[i].activity = inactive;
            float f = map(arr[i].value, 0, sp.bar_number * 2, 50.f, 1200.f);
            AddTone(sp.beeper, f);
            BeepSound(sp.beeper, 0, 0);
        }
        else if (arr[i].activity == green)
        {
            SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
            arr[i].activity = inactive;
        }
        else if (arr[i].activity == purple)
        {
            SDL_SetRenderDrawColor(rend, 255, 0, 255, 255);
            arr[i].activity = inactive;
            float f = map(arr[i].value, 0, sp.bar_number * 2, 50.f, 1200.f);
            AddTone(sp.beeper, f);
            BeepSound(sp.beeper, 0, 0);
        }
        else
        {
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        }
        SDL_FRect r = {(float)i * dim.cell_w - 1.0, (float)dim.HEIGHT - (float)arr[i].value * dim.cell_h, dim.cell_w, (float)arr[i].value * dim.cell_h};
        SDL_RenderFillRectF(rend, &r);
    }
    SDL_RenderPresent(rend);
    SDL_Delay(sp.duration);
    SDL_PauseAudioDevice(sp.beeper->device, 1);
}

//-----------------------------sorting algorithms-------------------------
void bubble_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    for (int i = 0; i < sp.bar_number; i++)
    {
        for (int j = 0; j < sp.bar_number - i - 1; j++)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[j].activity = green;
            arr[j + 1].activity = red;
            if (arr[j].value > arr[j + 1].value)
            {
                swap(&arr[j], &arr[j + 1]);
            }
            draw_bars(arr, rend, dim, sp);
        }
    }
}

void cocktail_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    bool swap_flag = true;
    int i = 0;
    while (swap_flag)
    {
        swap_flag = false;
        for (int j = i; j < sp.bar_number - i - 1; j++)
        {

            if (check_exit(&dim.ev, quit))
                return;
            arr[j].activity = green;
            arr[j + 1].activity = red;
            if (arr[j].value > arr[j + 1].value)
            {
                swap(&arr[j], &arr[j + 1]);
                swap_flag = true;
            }
            draw_bars(arr, rend, dim, sp);
        }
        ++i;
        // if (!swap_flag)
        //     return;
        for (int j = sp.bar_number - 1 - i; j >= i; j--)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[j].activity = red;
            arr[j - 1].activity = red;
            if (arr[j].value < arr[j - 1].value)
            {
                swap(&arr[j], &arr[j - 1]);
                swap_flag = true;
            }
            draw_bars(arr, rend, dim, sp);
        }
    }
}

void selection_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    for (int i = 0; i < sp.bar_number; i++)
    {
        Bar *min = &arr[i];
        for (int j = i; j < sp.bar_number; j++)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[j].activity = red;
            if (min->value >= arr[j].value)
            {
                min = &arr[j];
            }
            min->activity = green;
            draw_bars(arr, rend, dim, sp);
        }
        Bar temp = *min;
        *min = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    for (int i = 1; i < sp.bar_number; i++)
    {
        Bar key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].value > key.value)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[j].activity = red;
            arr[j + 1] = arr[j];
            arr[i].activity = green;
            j--;
            draw_bars(arr, rend, dim, sp);
        }
        arr[j + 1] = key;
    }
}

void gnome_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    int i = 0;
    while (i < sp.bar_number)
    {
        if (check_exit(&dim.ev, quit))
            return;
        arr[i].activity = red;
        if (i == 0 || arr[i - 1].value <= arr[i].value)
            ++i;
        else
        {
            swap(&arr[i], &arr[i - 1]);
            --i;
        }
        draw_bars(arr, rend, dim, sp);
    }
}

void odd_even_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    bool swap_flag = true;
    while (swap_flag)
    {
        swap_flag = false;
        for (int i = 1; i < sp.bar_number - 1; i += 2)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[i].activity = red;
            arr[i + 1].activity = red;
            if (arr[i].value > arr[i + 1].value)
            {
                swap(&arr[i], &arr[i + 1]);
                swap_flag = true;
            }
            draw_bars(arr, rend, dim, sp);
        }
        for (int i = 0; i < sp.bar_number - 1; i += 2)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[i].activity = red;
            if (arr[i].value > arr[i + 1].value)
            {
                swap(&arr[i], &arr[i + 1]);
                swap_flag = true;
            }
            draw_bars(arr, rend, dim, sp);
        }
    }
}

void shell_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    for (int i = sp.bar_number / 2; i > 0; i /= 2)
    {
        for (int j = i; j < sp.bar_number; j++)
        {
            Bar *ptr = &arr[j];
            Bar temp = arr[j];
            int k;
            for (k = j; k >= i && arr[k - i].value > temp.value; k -= i)
            {
                if (check_exit(&dim.ev, quit))
                    return;
                arr[k] = arr[k - i];
                arr[k].activity = red;
                ptr->activity = purple;
                draw_bars(arr, rend, dim, sp);
            }
            arr[k] = temp;
        }
    }
}

void bogo_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    bool sorted = false;
    while (!sorted)
    {
        srand(time(NULL));
        for (int i = 0; i < sp.bar_number; i++)
        {
            if (check_exit(&dim.ev, quit))
                return;
            int j = rand() / (RAND_MAX / (sp.bar_number - i) + 1);
            arr[i].activity = purple;
            arr[i].activity = purple;
            swap(&arr[i], &arr[j]);
            draw_bars(arr, rend, dim, sp);
        }
        sorted = true;
        int i = 0;
        while (i < sp.bar_number - 1 && sorted)
        {
            if (check_exit(&dim.ev, quit))
                return;
            arr[i].activity = red;
            draw_bars(arr, rend, dim, sp);
            if (arr[i].value > arr[i + 1].value)
                sorted = false;
            i++;
        }
    }
}

// QuickSort ------------------------------------------------------------------------

static void quick_sort_unpacked(Bar *arr, int starting_index, int ending_index, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    if (*quit)
        return;
    if (starting_index >= ending_index)
        return;
    Bar pivot = arr[ending_index];
    int pivot_index = starting_index;
    arr[ending_index].activity = green;
    for (int i = starting_index; i < ending_index; i++)
    {
        if (check_exit(&dim.ev, quit))
            return;
        arr[pivot_index].activity = red;
        arr[i].activity = red;
        if (arr[i].value <= pivot.value)
        {
            swap(&arr[i], &arr[pivot_index]);
            pivot_index++;
        };
        draw_bars(arr, rend, dim, sp);
    }
    swap(&arr[pivot_index], &arr[ending_index]);

    quick_sort_unpacked(arr, starting_index, pivot_index - 1, rend, dim, sp, quit);
    quick_sort_unpacked(arr, pivot_index + 1, ending_index, rend, dim, sp, quit);
}

void quick_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    quick_sort_unpacked(arr, sp.start_index, sp.end_index, rend, dim, sp, quit);
}
//-----------------------------------------------------------------------------------

// Merge Sort------------------------------------------------------------------------
static void merge(Bar *arr, SDL_Renderer *rend, int start, int mid, int end, WindowProp dim, SortingParams sp, bool *quit)
{
    if (check_exit(&dim.ev, quit))
        return;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    Bar temp[n1 + n2];

    int i = 0, j = 0, k = 0;
    while (i < n1 || j < n2)
    {
        check_exit(&dim.ev, quit);
        if (*quit)
            return;

        if (i < n1 && (j >= n2 || arr[start + i].value < arr[mid + 1 + j].value))
        {
            arr[start + i].activity = red;
            temp[k++] = arr[start + i++];
        }
        else
        {
            arr[mid + 1 + j].activity = red;
            temp[k++] = arr[mid + 1 + j++];
        }
        draw_bars(arr, rend, dim, sp);
    }

    for (int t = 0; t < k; t++)
    {
        if (check_exit(&dim.ev, quit))
            return;
        arr[start + t] = temp[t];
        draw_bars(arr, rend, dim, sp);
    }
}

static void merge_sort_unpacked(Bar *arr, SDL_Renderer *rend, int start, int end, WindowProp dim, SortingParams sp, bool *quit)
{
    if (start >= end || *quit)
    {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort_unpacked(arr, rend, start, mid, dim, sp, quit);
    merge_sort_unpacked(arr, rend, mid + 1, end, dim, sp, quit);
    merge(arr, rend, start, mid, end, dim, sp, quit);
}

void merge_sort(Bar *arr, SDL_Renderer *rend, WindowProp dim, SortingParams sp, bool *quit)
{
    merge_sort_unpacked(arr, rend, sp.start_index, sp.end_index, dim, sp, quit);
}
