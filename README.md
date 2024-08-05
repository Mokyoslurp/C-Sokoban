This project consists in the creation of a functional Sokoban game, and a solver to solve a Sokoban game.

The solver use linked list structure or AVL trees (special Binary Search Tree (BST))

A functionality has been added to the game, allowing the player to go backwards of 1 movement using Tab key

There are three executables and a few tests that can be compiled using :
`make compile-all`

Executables
===========

- `./play.exe [./data/FILENAME.in]`

    Launch a playing interface to play a Sokoban game, using arrows keys, quitting with "Q" key or Escape key. Tab key to go backwards of 1 movement
    The numbers of backwards possible is 15 by default

    Take as argument :
        a path to a Sokoban map file

- `./replay.exe [./data/FILENAME.in] [int] [string]`

    Compute the movements contained in a string with an initial Sokoban map given. 
    Print the final Sokoban map after the movements

    Take as argument :
        a path to a Sokoban map file
        the length of the movement plan desired
        a string containing "N", "S", "E", "W" in the desired configuration, representing the movements done by the player


- `./solve.exe [./data/FILENAME.in] [list] [gui]`
    Solve a Sokoban map and print stats on the way it has been solved

    Take as argument :
        a path to a Sokoban map file
        "list" if solving has to be made using linked list method in addition to BST (AVL tree here) method
        "gui" if the user wants to launch an interface that will replay the game using the plan computed by the solver
            (Use Enter key to go to the next step and Escape key or "Q" key to leave the program)


Tests
======

All the tests can be executed using :
`make launch-tests`

No test need an argument when launched
test-loader can still be launched using `[./data/FILENAME.in]`, a path to a map, to test the loader on a different map than the default one


Requirements
============

- gcc
- SDL/SDL2

Documentation
==============

Doxygen documentation is available in ./doc/html/index.html