/**
 * @file test-move.c
 *
 * @brief Test executable to verify the move function is working
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
 * @brief function to verify if the map after the move function is equal to the loaded map corresponding
 *
 */
bool are_maps_equal(char path_1[], char path_2[], char direction)
{

	map init_map = load_map(path_1);

	map moved_map = move(init_map, direction);

	map loaded_map = load_map(path_2);

	bool are_equal = are_maps_strings_equal(moved_map, loaded_map);

	if (moved_map.str != init_map.str)
	{
		free(moved_map.str);
	}
	free(init_map.str);
	free(loaded_map.str);

	init_map.str = NULL;
	loaded_map.str = NULL;
	moved_map.str = NULL;

	return are_equal;
}

int main()
{
	printf("Move tests launched ...\n");

	// simple player movements
	assert(are_maps_equal("./data/soko_move_1.in", "./data/soko_move_1_N.in", UP));
	assert(are_maps_equal("./data/soko_move_1.in", "./data/soko_move_1_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_1.in", "./data/soko_move_1_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_1.in", "./data/soko_move_1_W.in", LEFT));

	// player movements on dest.
	assert(are_maps_equal("./data/soko_move_2.in", "./data/soko_move_2_N.in", UP));
	assert(are_maps_equal("./data/soko_move_2.in", "./data/soko_move_2_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_2.in", "./data/soko_move_2_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_2.in", "./data/soko_move_2_W.in", LEFT));

	// move box to east
	assert(are_maps_equal("./data/soko_move_3_1.in", "./data/soko_move_3_1_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_3_2.in", "./data/soko_move_3_2_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_3_3.in", "./data/soko_move_3_3_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_3_4.in", "./data/soko_move_3_4_E.in", RIGHT));

	// move box to west
	assert(are_maps_equal("./data/soko_move_4_1.in", "./data/soko_move_4_1_W.in", LEFT));
	assert(are_maps_equal("./data/soko_move_4_2.in", "./data/soko_move_4_2_W.in", LEFT));
	assert(are_maps_equal("./data/soko_move_4_3.in", "./data/soko_move_4_3_W.in", LEFT));
	assert(are_maps_equal("./data/soko_move_4_4.in", "./data/soko_move_4_4_W.in", LEFT));

	// move box to north
	assert(are_maps_equal("./data/soko_move_5_1.in", "./data/soko_move_5_1_N.in", UP));
	assert(are_maps_equal("./data/soko_move_5_2.in", "./data/soko_move_5_2_N.in", UP));
	assert(are_maps_equal("./data/soko_move_5_3.in", "./data/soko_move_5_3_N.in", UP));
	assert(are_maps_equal("./data/soko_move_5_4.in", "./data/soko_move_5_4_N.in", UP));

	// move box to south
	assert(are_maps_equal("./data/soko_move_6_1.in", "./data/soko_move_6_1_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_6_2.in", "./data/soko_move_6_2_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_6_3.in", "./data/soko_move_6_3_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_6_4.in", "./data/soko_move_6_4_S.in", DOWN));

	// does nothing
	assert(are_maps_equal("./data/soko_move_W_E.in", "./data/soko_move_W_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_W_W.in", "./data/soko_move_W_W.in", LEFT));
	assert(are_maps_equal("./data/soko_move_W_N.in", "./data/soko_move_W_N.in", UP));
	assert(are_maps_equal("./data/soko_move_W_S.in", "./data/soko_move_W_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_B_W_E.in", "./data/soko_move_B_W_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_B_W_W.in", "./data/soko_move_B_W_W.in", LEFT));
	assert(are_maps_equal("./data/soko_move_B_W_N.in", "./data/soko_move_B_W_N.in", UP));
	assert(are_maps_equal("./data/soko_move_B_W_S.in", "./data/soko_move_B_W_S.in", DOWN));
	assert(are_maps_equal("./data/soko_move_B_B_E.in", "./data/soko_move_B_B_E.in", RIGHT));
	assert(are_maps_equal("./data/soko_move_B_B_W.in", "./data/soko_move_B_B_W.in", LEFT));
	assert(are_maps_equal("./data/soko_move_B_B_N.in", "./data/soko_move_B_B_N.in", UP));
	assert(are_maps_equal("./data/soko_move_B_B_S.in", "./data/soko_move_B_B_S.in", DOWN));

	printf("All move tests succeeded !\n\n");

	return 0;
}
