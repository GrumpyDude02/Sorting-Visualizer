#include "bar.h"
#include "application.h"

#ifndef SORTING_H
#define SORTING_H

void swap(Bar *b1, Bar *b2);
//-----------------------------sorting algorithms-------------------------
//---qudratic algorithms-----
void bubble_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void selection_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void insertion_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void cocktail_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void gnome_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void odd_even_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void shell_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void bogo_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);

//--logarithmic algorithms---
void quick_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);
void merge_sort(Bar *arr, ApplicationWindow *app, SortingParams sp);

#endif