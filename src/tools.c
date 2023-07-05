#include "tools.h"

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
