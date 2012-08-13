# Implementation of Conway's Game of Life in GLUT/OpenGL ###

## Rules
* an organism with 0, 1, 4, 5, 6, 7 or 8 neighbors dies
* an organism with 2 or 3 neighbors survives
* organisms are born in empty cells with 3 neighbors

# Configuration File ####

Some game variables can be changed using a configuration file like the one provided (game.config). The configuration file is passed as an argument to the executable:

* ./game game.config

The example configuration contains all the possible variables and a small explanation for each one.

## Compilation

The makefile allows for an easy compilation on Linux and Mac OS X operative systems. The fastest way to compile and run the code is just by typing 'make' in the terminal. To compile only type 'make compile'.
