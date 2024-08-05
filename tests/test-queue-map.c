/**
 * @file test-queue-map.c
 * @author M.Giordani
 * @brief Test for the queue functionalities
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"
#include "linked_list_map.h"
#include "queue_map.h"

int main()
{
	printf("Queue map tests launched ...\n");

	linked_list_map explored_list = nil();
	queue my_queue = nil_queue();
	printf("queue and explored_list created\n");
	queue_cell empty_cell = dequeue(my_queue);
	printf("is my queue empty : %s\n", is_empty_queue(my_queue) ? "yes" : "no");

	// Loading of a map, and some movements, stored in the queue
	map my_map = find_player(load_map("./data/soko99.in"));
	explored_list = cons(my_map, explored_list);
	queue_cell cell = create_queue_cell(NULL, my_map, '\0');
	enqueue(my_queue, cell);

	my_map = move(my_map, LEFT);
	explored_list = cons(my_map, explored_list);
	cell = create_queue_cell(cell, my_map, LEFT);
	enqueue(my_queue, cell);

	// dequeueing of a queue with one element
	printf("dequeuing one element...\n");
	queue_cell dequeued_cell = dequeue(my_queue);
	print_map(queue_cell_map(dequeued_cell));
	printf("movement before this map : %c\n", movement(dequeued_cell));
	printf("depth of this cell : %d\n", depth(dequeued_cell));
	deallocate_queue_cell(dequeued_cell);
	printf("is my queue empty : %s\n", is_empty_queue(my_queue) ? "yes" : "no");

	my_map = move(my_map, LEFT);
	explored_list = cons(my_map, explored_list);
	cell = create_queue_cell(cell, my_map, LEFT);
	enqueue(my_queue, cell);

	my_map = move(my_map, UP);
	explored_list = cons(my_map, explored_list);
	cell = create_queue_cell(cell, my_map, UP);
	enqueue(my_queue, cell);

	my_map = move(my_map, UP);
	explored_list = cons(my_map, explored_list);
	cell = create_queue_cell(cell, my_map, UP);
	enqueue(my_queue, cell);
	printf("queue constructed\n");

	printf("is my queue empty : %s\n", is_empty_queue(my_queue) ? "yes" : "no");

	printf("dequeuing all queue and freeing memory...\n");

	deallocate_queue_cell(empty_cell);
	deallocate_queue(my_queue);
	deallocate_list(explored_list);

	printf("Queue list map tests succeeded !\n\n");

	return 0;
}
