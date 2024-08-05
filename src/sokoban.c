#include "sokoban.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_map(map my_map)
{
	printf("map dimensions: %d x %d\n", my_map.width, my_map.height);
	for (int i = 0; i < my_map.height; i++)
	{
		printf("line %d: ", i);
		for (int j = 0; j < my_map.width; j++)
		{
			printf("%c", *(my_map.str + (i * my_map.width) + j));
		}
		printf("\n");
	}
}

map copy_map(map my_map)
{
	map new_map = my_map;
	new_map.str = malloc((sizeof(char) * my_map.height * my_map.width) + 1);
	memcpy(new_map.str, my_map.str, (sizeof(char) * my_map.height * my_map.width) + 1);
	return new_map;
}

map move(map my_map, char direction)
{
	map new_map = copy_map(my_map);

	// depending on the direction, different coordinates are considered around the player
	int i = 0;
	int j = 0;

	if (direction == UP)
	{
		i = -1;
	}
	else if (direction == DOWN)
	{
		i = +1;
	}
	else if (direction == RIGHT)
	{
		j = +1;
	}
	else if (direction == LEFT)
	{
		j = -1;
	}

	// actual position of the player represented by the id of the character representing the player in the map string
	char *actual_pos = id_elem(new_map, my_map.player_x, my_map.player_y);
	// freed_space is the character that the case will have after the player leave it
	char freed_space = (*actual_pos == BOY_ON) ? PARK : EMPTY;
	// next_pos is the position that is next to the player in the specified direction
	char *next_pos = id_elem(new_map, my_map.player_x + i, my_map.player_y + j);

	// if there is no obstacle, the player moves forward
	if (*next_pos == EMPTY || *next_pos == PARK)
	{
		// map after movement modification
		new_map.player_y = my_map.player_y + j;
		new_map.player_x = my_map.player_x + i;
		*actual_pos = freed_space;

		if (*next_pos == EMPTY)
		{
			*next_pos = BOY;
		}
		else
		{
			*next_pos = BOY_ON;
		}
		return new_map;
	}
	// if there is a wall, nothing happen
	else if (*next_pos == WALL)
	{
		return new_map;
	}
	// if there is a box, the cell after the box is checked to verified it it is free
	else
	{
		char *next_next_pos = id_elem(new_map, my_map.player_x + 2 * i, my_map.player_y + 2 * j);
		if (*next_next_pos == WALL || *next_next_pos == BOX || *next_next_pos == BOX_ON)
		{
			return new_map;
		}
		else
		{
			// map after movement modification
			new_map.player_y = my_map.player_y + j;
			new_map.player_x = my_map.player_x + i;
			*actual_pos = freed_space;
			if (*next_next_pos == PARK)
			{
				*next_next_pos = BOX_ON;
				if (*next_pos == BOX)
				{
					*next_pos = BOY;
				}
				else
				{
					*next_pos = BOY_ON;
				}
			}
			else
			{
				*next_next_pos = BOX;
				if (*next_pos == BOX)
				{
					*next_pos = BOY;
				}
				else
				{
					*next_pos = BOY_ON;
				}
			}
			return new_map;
		}
	}
}

map replay(map my_map, int l_plan, char plan[])
{

	map old_map;

	for (int k = 0; k < l_plan; k++)
	{
		old_map = my_map;
		my_map = move(old_map, plan[k]);
		if (old_map.str != my_map.str)
		{
			free(old_map.str);
		}
	}
	return my_map;
}

char *id_elem(map my_map, int i, int j)
{
	return my_map.str + i * my_map.width + j;
}

char access_elem(map my_map, int i, int j)
{
	return *id_elem(my_map, i, j);
}

map modify_elem(map my_map, int i, int j, char symbol)
{
	*id_elem(my_map, i, j) = symbol;
	return my_map;
}

bool is_win(map my_map)
{

	char actual_char;
	// finds the box (not on a storage) char in the map to tell the player if the game is over
	for (int i = my_map.width; i < (my_map.height - 1) * my_map.width; i++)
	{
		actual_char = *(my_map.str + i);
		if (actual_char == BOX)
		{
			return false;
		}
	}
	return true;
}

bool are_maps_strings_equal(map map_1, map map_2)
{
	// the verification is made everywhere except in the first and last line
	int nb_char = (map_1.height - 1) * map_1.width;
	for (int i = map_1.width; i < nb_char; i++)
	{
		if (*(map_1.str + i) != *(map_2.str + i))
		{
			return false;
		}
	}
	return true;
}

bool are_players_pos_equal(map map_1, map map_2)
{
	return (map_1.player_x == map_2.player_x && map_1.player_y == map_2.player_y);
}

void deallocate_map(map my_map)
{
	free(my_map.str);
}