/**
 * @file test-loader.c
 *
 * @brief Test executable to verify the map loader is working.
 *
 * @author M.Giordani
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"

int main(int argc, char *argv[])
{
	printf("Loader tests launched ...\n");

	map my_map;

	if (argc <= 1)
	{
		my_map = load_map("./data/soko100.in");
	}
	else
	{
		my_map = load_map(argv[1]);
	}

	print_map(my_map);

	free(my_map.str);

	my_map.str = NULL;

	printf("Loader test succeeded !\n\n");

	return 0;
}
