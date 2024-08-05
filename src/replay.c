/**
 * @file replay.c
 *
 * @brief Program that reads a sequence given in argument and plays the sequence by moving a player on a map. Print the final map.
 *
 * @author M.Giordani
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
#include "sokoban.h"

int main(int argc, char *argv[])
{

	if (argc != 4)
	{
		fprintf(stderr, "You must provide the right number of arguments!\n");
		exit(EXIT_FAILURE);
	}
	char *path = argv[1];

	int l_plan = atoi(argv[2]);

	char *plan = argv[3];

	printf("Loading a new map... :\n");
	map init_map = load_map(path);
	print_map(init_map);

	printf("\nMap after player movement :\n");
	map final_map = replay(init_map, l_plan, plan);
	print_map(final_map);

	free(final_map.str);

	return 0;
}