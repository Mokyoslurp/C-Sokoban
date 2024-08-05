#include "solver.h"
#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include "gui.h"

// Solving functions

stats solve_map_list(char path[])
{

	// Initializing a map, stats, queue and list objects
	map initial_map = load_map(path);
	int path_length = 0;
	while (path[path_length] != '\0')
	{
		path_length++;
	}

	stats map_stats = {malloc(sizeof(char) * path_length), false, malloc(sizeof(movement_plan)), 0, 0.};
	memmove(map_stats.path, path, path_length);

	queue search_queue = nil_queue();
	queue dequeued_queue = nil_queue();
	linked_list_map explored_list = nil();

	queue_cell current_cell;
	map current_map;

	// Starting to solve
	clock_t start = clock();

	enqueue(search_queue, create_queue_cell(NULL, initial_map, '\0'));
	explored_list = cons(initial_map, explored_list);

	while (!is_empty_queue(search_queue))
	{
		current_cell = dequeue(search_queue);
		current_map = queue_cell_map(current_cell);
		(map_stats.explored_nodes)++;

		enqueue(dequeued_queue, current_cell);

		// This function is used to check if a box lies in a wall corner. if it the case the map is not solvable anymore
		if (!are_box_in_corner(current_map))
		{
			if (is_win(current_map))
			{
				*(map_stats.plan) = build_plan(current_cell);
				map_stats.is_win_plan = true;

				deallocate_solver_list(search_queue, dequeued_queue, explored_list);
				map_stats.solve_time = (clock() - (double)start) / CLOCKS_PER_SEC;
				return map_stats;
			}

			map new_map;
			char dir[4] = {UP, DOWN, LEFT, RIGHT};
			for (int i = 0; i < 4; i++)
			{
				new_map = move(current_map, dir[i]);

				if (is_map_in_list(new_map, explored_list))
				{
					free(new_map.str);
				}
				else
				{
					explored_list = cons(new_map, explored_list);
					enqueue(search_queue, create_queue_cell(current_cell, new_map, dir[i]));
				}
			}
		}
	}
	deallocate_solver_list(search_queue, dequeued_queue, explored_list);
	map_stats.solve_time = (clock() - (double)start) / CLOCKS_PER_SEC;
	return map_stats;
}

stats solve_map_bst(char path[])
{

	// Initializing a map, stats, queue and BST objects
	map initial_map = load_map(path);
	int path_length = 0;
	while (path[path_length] != '\0')
	{
		path_length++;
	}

	stats map_stats = {malloc(sizeof(char) * path_length), false, malloc(sizeof(movement_plan)), 0, 0.};
	memmove(map_stats.path, path, path_length);

	queue search_queue = nil_queue();
	queue dequeued_queue = nil_queue();
	bst_map explored_tree = nil_bst();

	queue_cell current_cell;
	map current_map;

	// Starting to solve
	clock_t start = clock();

	enqueue(search_queue, create_queue_cell(NULL, initial_map, '\0'));
	explored_tree = insert(explored_tree, initial_map);

	while (!is_empty_queue(search_queue))
	{
		current_cell = dequeue(search_queue);
		current_map = queue_cell_map(current_cell);
		(map_stats.explored_nodes)++;

		enqueue(dequeued_queue, current_cell);

		// This function is used to check if a box lies in a wall corner. if it the case the map is not solvable anymore
		if (!are_box_in_corner(current_map))
		{
			if (is_win(current_map))
			{
				*(map_stats.plan) = build_plan(current_cell);
				map_stats.is_win_plan = true;

				deallocate_solver_bst(search_queue, dequeued_queue, explored_tree);
				map_stats.solve_time = (clock() - (double)start) / CLOCKS_PER_SEC;
				return map_stats;
			}

			map new_map;
			char dir[4] = {UP, DOWN, LEFT, RIGHT};
			for (int i = 0; i < 4; i++)
			{
				new_map = move(current_map, dir[i]);

				if (is_map_in_tree(new_map, explored_tree))
				{
					free(new_map.str);
				}
				else
				{
					explored_tree = insert(explored_tree, new_map);
					enqueue(search_queue, create_queue_cell(current_cell, new_map, dir[i]));
				}
			}
		}
	}
	deallocate_solver_bst(search_queue, dequeued_queue, explored_tree);
	map_stats.solve_time = (clock() - (double)start) / CLOCKS_PER_SEC;
	return map_stats;
}

// Other functions

bool are_box_in_corner(map my_map)
{
	char actual_char;
	for (int i = my_map.width; i < (my_map.height - 1) * my_map.width; i++)
	{
		actual_char = *(my_map.str + i);
		if (actual_char == BOX)
		{
			if ((*(my_map.str + i + 1) == WALL && *(my_map.str + i + my_map.width) == WALL) ||
				(*(my_map.str + i + 1) == WALL && *(my_map.str + i - my_map.width) == WALL) ||
				(*(my_map.str + i - 1) == WALL && *(my_map.str + i + my_map.width) == WALL) ||
				(*(my_map.str + i - 1) == WALL && *(my_map.str + i - my_map.width) == WALL))
			{
				return true;
			}
		}
	}
	return false;
}

movement_plan build_plan(queue_cell cell)
{
	movement_plan plan;
	plan.length = depth(cell);
	plan.str = malloc((plan.length + 1) * sizeof(char));

	for (int i = depth(cell); i >= 0; i--)
	{
		*(plan.str + i) = cell->movement;
		cell = cell->mother;
	}
	return plan;
}

void print_solve(char path[], bool with_list, bool with_GUI)
{

	// Loading the map to solve
	printf("Loading ");
	map my_map = load_map(path);
	print_path(path);
	printf("For this map :\n");
	print_map(my_map);

	// solving using lists and bst
	stats map_stats_list;
	if (with_list)
	{
		map_stats_list = solve_map_list(path);
	}
	stats map_stats_bst = solve_map_bst(path);

	if (map_stats_bst.is_win_plan)
	{
		printf("This is a win !\n");
		printf("Length of the plan to solve the map : %d\n", (map_stats_bst.plan)->length);
		printf("Here is a plan :\n");
		print_plan(*(map_stats_bst.plan));
	}
	else
	{
		printf("I'm sorry there are no winning plan for the map\n");
	}
	printf("The program got through %d nodes\n", map_stats_bst.explored_nodes);
	if (with_list)
	{
		printf("It took %lf seconds to compute using list\n", map_stats_list.solve_time);
		deallocate_stats(map_stats_list);
	}
	printf("It took %lf seconds to compute using bst\n", map_stats_bst.solve_time);

	// Initializing and launching the GUI to play the solution if asked to
	if (with_GUI)
	{
		// Preparing initial map for GUI
		char level[my_map.height][my_map.width];
		for (int lin = 0; lin < my_map.height; lin++)
		{
			for (int col = 0; col < my_map.width; col++)
			{
				level[lin][col] = access_elem(my_map, lin, col);
			}
		}

		if (map_stats_bst.is_win_plan)
		{
			printf("You can play the solution !\n Use Enter key to go a step further, and Escape key to exit the GUI\n");

			// initialize GUI window
			GUI_init("Sokoban", my_map.width, my_map.height);

			// display level
			GUI_show(my_map.width, my_map.height, level);

			bool stop = false;
			int i = 0;
			while (!stop && i <= map_stats_bst.plan->length)
			{
				switch (GUI_get_key())
				{
				case SDLK_RETURN:
					i++;
					my_map = replay(my_map, 1, (map_stats_bst.plan->str + i));
					// Updating the matrix with the map after movement
					for (int lin = 0; lin < my_map.height; lin++)
					{
						for (int col = 0; col < my_map.width; col++)
						{
							level[lin][col] = access_elem(my_map, lin, col);
						}
					}
					GUI_show(my_map.width, my_map.height, level);

					break;
				case SDLK_ESCAPE:
					stop = true;
					break;
				case SDLK_q:
					stop = true;
					break;
				}
				if (is_win(my_map))
				{
					stop = true;
				}
			}
			GUI_close();
		}
	}
	deallocate_map(my_map);
	deallocate_stats(map_stats_bst);
}

void print_plan(movement_plan plan)
{
	for (int i = 0; i <= plan.length; i++)
	{
		printf("%c", *(plan.str + i));
	}
	printf("\n");
}

void print_path(char path[])
{
	int i = 0;
	while (path[i] != '\0')
	{
		printf("%c", path[i]);
		i++;
	}
	printf("\n");
}

void deallocate_plan(movement_plan plan)
{
	free(plan.str);
}

void deallocate_stats(stats my_stats)
{
	if (my_stats.is_win_plan)
	{
		deallocate_plan(*(my_stats.plan));
	}
	free(my_stats.path);
	free(my_stats.plan);
}

void deallocate_solver_list(queue search_queue, queue dequeued_queue, linked_list_map explored_list)
{
	deallocate_queue(search_queue);
	deallocate_queue(dequeued_queue);
	deallocate_list(explored_list);
}

void deallocate_solver_bst(queue search_queue, queue dequeued_queue, bst_map explored_tree)
{
	deallocate_queue(search_queue);
	deallocate_queue(dequeued_queue);
	deallocate_bst(explored_tree);
}
