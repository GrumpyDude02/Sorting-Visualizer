# Sorting Visulizer

A simple sorting visualizer with sound developed as a final project for the cs50x course. It provides the possibility to visualize various sorting algorithms in action making it easy to understand how each algorithm works.

## Available Sorting Algorithms:

- Bubble Sort
- Quick Sort
- Insertion Sort
- Merge Sort
- Selection Sort
- Cocktail Sort
- Gnome Sort
- Shell Sort
- Bogo Sort (for fun)

## Features:

- Visualization of popular sorting algorithms.
- Synchronised sound with sorting.
- Ability to change the delay between each iteration (the delay is the duration of the sound).
- Ability to change the number of bars drawn at the screen (limit 600).
- Modular code making it easy to add sorting algorithms in the future.
- Written in C programming language.

## Demo:

- Exemple 1: Merge Sort - 150 bars - 20ms delay.

![](/gifs/merge_sort_demo.gif)

- Exemple 2: Cocktail Sort - 80 bars - 4ms delay.

![](/gifs/cocktail_sort_demo.gif)

- Exemple 3: Inerstion Sort - 100 bars - 5ms delay.

![](/gifs/insertion_sort_demo.gif)

## Usage

- Upon running the program, a terminal window will open showing a list of available sorting algorithms.
- The desired sorting algorithm can be selected by pressing on the corresponding number key.
- After selecting the sorting algorithm the user is prompted to enter the number of bars with a maximum of 600.
- A third prompt will appear asking for the delay duration in miliseconds.
- An SDL window will open, displaying a visualization of the sorting process. The window will show a series of white bars representing the elements to be sorted. Initially, these bars will be randomly arranged. As the sorting algorithm progresses, the bars will change their positions in accordance with the sorting logic.
- The SDL window can be closed at any time, but the terminal window will still be open, allowing you to chose an algorithm or close the program.
- The program can be closed by pressing on the number key 0 when prompted to chose an algorithm.

## Made Using:

- SDL2 devel 2.28.0 mingw (https://github.com/libsdl-org/SDL/releases/tag/release-2.28.0).
- Compiler: gcc version 12.2.0 (x86_64-posix-seh-rev2, Built by MinGW-W64 project).

## How to Build:

- Clone the repository to your local machine using the following command:

```
git clone https://github.com/GrumpyDude02/Sorting-Visualizer.git
```

- Download SDL 2 version compatible with your C compiler (https://github.com/libsdl-org/SDL/releases/tag/release-2.28.0). Make sure to use the files corresponding to your computer's architecture.
- When bulding link the the sdl2 library using

```
-lSDL2 -lSDL2main -lmingw32(if using mingw)
```

- The executable file and the SDL2.dll file should be in the same directory.
