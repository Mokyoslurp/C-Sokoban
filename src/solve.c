/**
 * @file solve.c
 *
 * @brief Solve a Sokoban game given as an argument of the command line. "list" and "gui" can be added on the command line if you want to use linked list for solving too, and if you want to show the solution with a GUI
 *
 * @author M.Giordani
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"
#include "solver.h"

// To tell SDL a main is already defined
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "gui.h"

int main(int argc, char *argv[])
{
	// Loading of the chosen level
	if (argc < 2)
	{
		fprintf(stderr, "You must provide a file name (with path)!\n");
		exit(EXIT_FAILURE);
	}
	char *path = argv[1];

	bool with_list = false;
	bool with_GUI = false;

	if (argc >= 3)
	{
		if (strncmp(argv[2], "list", 4))
		{
			with_list = true;
		}
		if (strncmp(argv[2], "gui", 3))
		{
			with_GUI = true;
		}
	}
	if (argc >= 4)
	{
		if (strncmp(argv[3], "list", 4))
		{
			with_list = true;
		}
		if (strncmp(argv[3], "gui", 3))
		{
			with_GUI = true;
		}
	}

	// Asking the user if he wants to use list or GUI if not specified on the command line
	if (!with_list)
	{
		printf("Do you want to solve the map using linked list in addition to BST (no by default) ? (y/n)\n");
		char yes_no;
		if (scanf("%c", &yes_no) != 0 && yes_no == 'y')
		{
			with_list = true;
		}
		// scanf required to clear the buffer
		scanf("%c", &yes_no);
	}
	if (!with_GUI)
	{
		printf("Do you want to interactively solve the map after solving (no by default) ? (y/n)\n");
		char yes_no;
		if (scanf("%c", &yes_no) != 0 && yes_no == 'y')
		{
			with_GUI = true;
		}
	}

	// solving the level (using bst)
	print_solve(path, with_list, with_GUI);

	return 0;
}
