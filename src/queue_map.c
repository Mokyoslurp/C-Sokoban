#include <stdio.h>
#include <stdlib.h>

#include "queue_map.h"
#include "sokoban.h"

queue nil_queue()
{
	queue my_queue = malloc(sizeof(struct queue_struct));
	my_queue->first = NULL;
	my_queue->last = NULL;
	return my_queue;
}

bool is_empty_queue_cell(queue_cell cell)
{
	return (cell == NULL);
}

bool is_empty_queue(queue my_queue)
{
	return (is_empty_queue_cell(my_queue->first) || is_empty_queue_cell(my_queue->last));
}

void enqueue(queue my_queue, queue_cell cell)
{

	if (is_empty_queue(my_queue))
	{
		my_queue->first = cell;
		my_queue->last = cell;
	}
	else
	{
		(my_queue->last)->next = cell;
		my_queue->last = cell;
	}
}

queue_cell dequeue(queue my_queue)
{
	// if queue is empty, returns an empty cell with an empty map of dimensions 0*0
	if (is_empty_queue(my_queue))
	{
		map empty_map = {0, 0, 0, 0, NULL};
		return create_queue_cell(NULL, empty_map, '\0');
	}

	queue_cell dequeued_cell = my_queue->first;
	if (dequeued_cell->next == NULL)
	{
		my_queue->first = NULL;
		my_queue->last = NULL;
	}
	else
	{
		my_queue->first = dequeued_cell->next;
	}
	dequeued_cell->next = NULL;
	return dequeued_cell;
}

queue_cell create_queue_cell(queue_cell former_cell, map new_map, char dir)
{
	// Convention taken for first cell : movement = '\0', depth = 0, mother = NULL
	queue_cell new_cell = malloc(sizeof(queue_cell_struct));

	new_cell->p_map = malloc(sizeof(map));
	*(new_cell->p_map) = new_map;

	new_cell->next = NULL;
	new_cell->mother = former_cell;
	new_cell->movement = dir;
	new_cell->depth = !is_empty_queue_cell(former_cell) ? former_cell->depth + 1 : 0;

	return new_cell;
}

void deallocate_queue_cell(queue_cell cell)
{
	free(cell->p_map);
	free(cell);
}

void deallocate_queue(queue my_queue)
{
	while (!is_empty_queue(my_queue))
	{
		deallocate_queue_cell(dequeue(my_queue));
	}
	free(my_queue);
}

map queue_cell_map(queue_cell cell)
{
	return *(cell->p_map);
}

queue_cell next_cell(queue_cell cell)
{
	return cell->next;
}

queue_cell mother_cell(queue_cell cell)
{
	return cell->mother;
}

char movement(queue_cell cell)
{
	return cell->movement;
}

int depth(queue_cell cell)
{
	return cell->depth;
}

queue_cell first(queue my_queue)
{
	return my_queue->first;
}

queue_cell last(queue my_queue)
{
	return my_queue->last;
}