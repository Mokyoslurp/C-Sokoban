/**
 * @file sokoban.h
 *
 * @brief Essential functionalities of the game
 *
 * @author M.Giordani
 *
 */

#ifndef SOKOBAN_H
#define SOKOBAN_H

// definition of cells icons
#define BOY '@'
#define BOY_ON '+'
#define BOX '$'
#define BOX_ON '*'
#define PARK '.'
#define EMPTY ' '
#define WALL '#'

// definition of directions
#define UP 'N'
#define DOWN 'S'
#define RIGHT 'E'
#define LEFT 'W'

#include <stdbool.h>

/**
 * @brief An alias for the map structure
 *
 */
typedef struct map map;

/**
 * @brief Structure representing a map
 *
 */
struct map
{
	/** The height the map*/
	int height;
	/** The width of the map*/
	int width;
	/** The x coordinate of the player on the map (from left to right)*/
	int player_x;
	/** The y coordinate of the player on the map (from up to down)*/
	int player_y;
	/** The string representing tha map*/
	char *str;
};

/**
 * @brief Print a map from a dynamically allocated structure representing the map
 *
 */
void print_map(map my_map);

/**
 * @brief Copie a map located by a pointer to an other memory emplacement dynamically allocated
 *
 */
map copy_map(map my_map);

/**
 * @brief Modify the p_map pointer given and the player_pos pointer with the right movement according to the game rules and the direction given
 *
 * @param my_map The map from which the movement has to be made
 * @param direction The movement chosen
 */
map move(map my_map, char direction);

/**
 * @brief Replay a game based on an initial map
 *
 * @param my_map The initial map
 * @param l_plan The length of the plan to be tested
 * @param plan The plan to be tested
 *
 * @return The latest map obtained with the plan, using only l_plan moves
 */
map replay(map my_map, int l_plan, char plan[]);

/**
 * @brief Return the adress of the map element at the coordinates (i, j)
 *
 */
char *id_elem(map my_map, int i, int j);

/**
 * @brief Return the element of the map at the coordinates (i, j)
 *
 */
char access_elem(map my_map, int i, int j);

/**
 * @brief Modifie the element of the map at the coordinates (i, j) and return the modified map
 *
 * @param symbol The symbol to put at coordiantes (i, j)
 */
map modify_elem(map my_map, int i, int j, char symbol);

/**
 * @brief Return true if the map is a winning map, false if not
 *
 */
bool is_win(map my_map);

/**
 * @brief Function to verify if the strings representing 2 maps are equal
 *
 */
bool are_maps_strings_equal(map map_1, map map_2);

/**
 * @brief Function to verify if the coordinates of the player on 2 maps are the same
 *
 */
bool are_players_pos_equal(map map_1, map map_2);

/**
 * @brief Deallocate a map
 *
 * @param my_map The map to deallocate
 */
void deallocate_map(map my_map);

#endif
