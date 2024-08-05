/**
 * @file test-replay.c
 *
 * @brief Test executable to verify the replay function is working
 *
 * @author M.Giordani
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"

/**
 * @brief function to verify if the map after the replay function is equal to the loaded map corresponding
 *
 */
bool are_maps_equal(char path_1[], char path_2[], int l_plan, char plan[])
{

	map init_map = load_map(path_1);

	map moved_map = replay(init_map, l_plan, plan);

	map loaded_map = load_map(path_2);

	bool are_equal = are_maps_strings_equal(moved_map, loaded_map);

	free(moved_map.str);
	free(loaded_map.str);

	init_map.str = NULL;
	loaded_map.str = NULL;
	moved_map.str = NULL;

	return are_equal;
}

int main()
{
	printf("Replay tests launched ...\n");

	// soko_dumb tests
	assert(are_maps_equal("./data/soko_dumb.in", "./data/soko_dumb_1.in", 3, "SSSEENN"));
	assert(are_maps_equal("./data/soko_dumb.in", "./data/soko_dumb_2.in", 5, "SSSEENN"));
	assert(are_maps_equal("./data/soko_dumb.in", "./data/soko_dumb_win.in", 7, "SSSEENN"));
	assert(are_maps_equal("./data/soko_dumb.in", "./data/soko_dumb_3.in", 7, "ESEESSWNN"));
	assert(are_maps_equal("./data/soko_dumb.in", "./data/soko_dumb_win.in", 9, "ESEESSWNN"));

	// Reading big plan
	FILE *p_file = NULL;
	p_file = fopen("./data/soko1-plan.txt", "r");
	char big_plan[200];
	fgets(big_plan, 200, p_file);
	fclose(p_file);

	// soko1 tests
	assert(are_maps_equal("./data/soko1.in", "./data/soko1_1.in", 100, big_plan));
	assert(are_maps_equal("./data/soko1.in", "./data/soko1_2.in", 150, big_plan));
	assert(are_maps_equal("./data/soko1.in", "./data/soko1_win.in", 184, big_plan));

	printf("All replay tests succeeded !\n\n");

	return 0;
}
