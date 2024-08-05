/**
 * @file loader.h
 *
 * @brief Functions used to load a map from a .in file into a dynamically allocated structure representing the map
 *
 * @author M.Giordani
 *
 */

#ifndef LOADER_H
#define LOADER_H

#include "sokoban.h"

/**
 * @brief Searche the player on the map and add its position to the map structure
 *
 * @return The map updated with player coordinates
 */
map find_player(map my_map);

/**
 * @brief Load a map from a path of a file to a dynamically allocated structure representing the map
 *
 * @return The loaded map
 */
map load_map(char path[]);

#endif
