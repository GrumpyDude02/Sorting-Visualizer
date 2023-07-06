# Sorting Visulizer

A simple sorting visualizer with sound developed as a final project for the cs50x course. It provides the possibility to visualize various sorting algorithms in action making it easy to understand how each algorithm works.

## Available sorting a algorithms:

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

- Exemple 1 : Bubble Sort

## Usage

- Upon running the program, a terminal window will open showing a list of available sorting algorithms.
- The desired sorting algorithm can be selected by pressing on the corresponding number key.
- After selecting the sorting algorithm the user is prompted to enter the number of bars with a maximum of 600.
- A third prompt will appear asking for the delay duration in miliseconds.
- An SDL window will where the bars are drawn and changing position on each iteration of the selected algorithm.
- The window can be closed at any time, but the terminal window will still be open asking the user to chose an algorithm.
- The program can closed by pressing on the number key 0 when prompted to chose an algorithm.

## Made Using:

- SDL2 devel 2.28.0 mingw.
- Compiler: gcc version 12.2.0 (x86_64-posix-seh-rev2, Built by MinGW-W64 project).
