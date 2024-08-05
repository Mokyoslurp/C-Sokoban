/**
 * @file queue_map.h
 *
 * @brief Queue containing maps
 *
 * @author M.Giordani
 */

#ifndef QUEUE_MAP_H
#define QUEUE_MAP_H

#include <stdbool.h>
#include "sokoban.h"

/**
 * @brief An alias for the structure representing a queue cell
 *
 */
typedef struct queue_cell_struct queue_cell_struct;

/**
 * @brief An alias for a pointer to the structure representing queue cell
 *
 */
typedef queue_cell_struct *queue_cell;

/**
 * @brief An alias for a pointer to the structure representing a queue
 *
 */
typedef struct queue_struct *queue;

/**
 * @brief A structure containing pointers to first and last cell of a queue, representing a queue
 *
 */
struct queue_struct
{
	queue_cell first;
	queue_cell last;
};

/**
 * @brief A structure representing a queue cell with a pointer to a map
 *
 */
struct queue_cell_struct
{
	/** A pointer to a map*/
	map *p_map;
	/** A pointer to the next cell in the queue*/
	queue_cell next;
	/** A pointer to the cell used to create the current cell*/
	queue_cell mother;
	/** A char representing the movement used to move the character and create current cell from the mother cell*/
	char movement;
	/** The depth of a map in the tree representing the possible movements from initial map*/
	int depth;
};

/**
 * @brief Create a nil queue
 *
 * @return A pointer to a queue
 */
queue nil_queue();

/**
 * @brief Return a boolean indicating if a queue cell is empty
 *
 * @param cell The considered cell
 */
bool is_empty_queue_cell(queue_cell cell);

/**
 * @brief Return a boolean indicating if a queue is empty
 *
 * @param my_queue The considered queue
 */
bool is_empty_queue(queue my_queue);

/**
 * @brief Enqueue a cell in a queue
 *
 * @param my_queue The queue considered
 * @param cell The cell to be enqueued
 */
void enqueue(queue my_queue, queue_cell cell);

/**
 * @brief Dequeue the first cell of a queue
 *
 * @param my_queue The queue to be dequeued
 * @return The first cell of the queue, or an empty cell with an empty map if queue is empty
 */
queue_cell dequeue(queue my_queue);

/**
 * @brief Create a queue cell object from a mother cell
 *
 * @param former_cell The mother cell
 * @param new_map The map created from the mother cell using the dir movement
 * @param dir The movement used to create new_map
 * @return The new queue cell
 */
queue_cell create_queue_cell(queue_cell former_cell, map new_map, char dir);

/**
 * @brief Deallocate a queue cell
 *
 * @param cell The cell to deallocate
 */
void deallocate_queue_cell(queue_cell cell);

/**
 * @brief Deallocate a queue
 *
 * @param my_queue The queue to deallocate
 */
void deallocate_queue(queue my_queue);

/**
 * @brief The map contained in a queue cell
 *
 */
map queue_cell_map(queue_cell cell);

/**
 * @brief A pointer to the queue cell following the current cell
 *
 */
queue_cell next_cell(queue_cell cell);

/**
 * @brief A pointer to the mother queue cell of the current cell
 *
 */
queue_cell mother_cell(queue_cell cell);

/**
 * @brief The last movement made to reach the map contained in the cell
 *
 */
char movement(queue_cell cell);

/**
 * @brief The depth of the cell in the tree of possible movements
 *
 */
int depth(queue_cell cell);

/**
 * @brief the first queue cell of a queue
 *
 */
queue_cell first(queue my_queue);

/**
 * @brief The last queue cell of a queue
 *
 */
queue_cell last(queue my_queue);

#endif
