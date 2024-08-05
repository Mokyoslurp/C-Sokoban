/**
 * @file linked_list_map.h
 *
 * @brief Linked list containing maps
 *
 * @author M.Giordani
 */

#ifndef LINKED_LIST_MAP_H
#define LINKED_LIST_MAP_H

#include <stdbool.h>
#include "sokoban.h"

/**
 * @brief An alias to the structure representing the cells of
 *        a list.
 */
typedef struct cell_map cell_map;

/**
 * @brief A linked list is represented by a pointer to the first cell
 *        of the list
 */
typedef cell_map *linked_list_map;

/**
 * @brief The structure representing the cells of a list
 */
struct cell_map
{
    /** The map value in the cell*/
    map value;
    /** A pointer to the next cell in the list*/
    cell_map *next;
};

/**
 * @brief Create a nil linked list.
 *
 * @return an empty linked list
 */
linked_list_map nil();

/**
 * @brief Add a map to the tail of the list
 *
 * @param elt The map to add
 * @param list The list in which the map has to be added
 * @return The list with the map added
 */
linked_list_map cons(map elt, linked_list_map list);

/**
 * @brief Compute the size of a linked list
 *
 * @param list The list considered
 * @return int : The size of the list
 */
int size(linked_list_map list);

/**
 * @brief Return a boolean indicating if the list is empty
 *
 * @param list The list considered
 */
bool is_empty(linked_list_map list);

/**
 * @brief Get the map at a certain position of a linked list
 *
 * @pre 'nat' is smaller than the size of the list, and greater than 0
 *
 * @param list The list considered
 * @param nat int : The position of the map to retrieve
 * @return The retrieved map
 */
map get_element(linked_list_map list, int nat);

/**
 * @brief Insert a map in a linked list at a given position
 *
 * @pre 'nat' is smaller than the size of the list, and greater than 0
 *
 * @param list The list considered
 * @param nat int : the position where the map has to be inserted
 * @param elt The map to insert
 * @return The list with the map inserted
 */
linked_list_map insert_element(linked_list_map list, int nat, map elt);

/**
 * @brief Remove a map from a list at a given position
 *
 * @pre 'nat' is smaller than the size of the list, and greater than 0
 *
 * @param list The list considered
 * @param nat int : the position where the map has to be deleted
 * @return the list without the deleted map
 */
linked_list_map remove_element(linked_list_map list, int nat);

/**
 * @brief Deallocate a linked list and its cells
 *
 * @param list The list to deallocate
 */
void deallocate_list(linked_list_map list);

/**
 * @brief Print the elements of a linked list
 *
 * @param list The list to print
 */
void print_list(linked_list_map list);

/**
 * @brief Return a boolean indicating if a map is an element of a list
 *
 * @param my_map The map considered
 * @param list The list considered
 */
bool is_map_in_list(map my_map, linked_list_map list);

#endif
