#include <stdio.h>
#include <stdlib.h>

#include "linked_list_map.h"
#include "sokoban.h"

linked_list_map nil()
{
    cell_map *cell = NULL;
    return cell;
}

linked_list_map cons(map elt, linked_list_map list)
{

    cell_map *cell = malloc(sizeof(cell_map));
    cell->value = elt;
    cell->next = NULL;

    if (is_empty(list))
    {
        list = cell;
        return list;
    }

    cell_map *last_cell = list;
    while (last_cell->next != NULL)
    {
        last_cell = last_cell->next;
    }
    last_cell->next = cell;
    return list;
}

int size(linked_list_map list)
{

    cell_map *cell = list;
    int n = 0;

    while (!is_empty(cell))
    {
        cell = cell->next;
        n = n + 1;
    }
    return n;
}

bool is_empty(linked_list_map list)
{
    return (list == NULL);
}

map get_element(linked_list_map list, int nat)
{

    if (nat >= size(list) || nat < 0)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nat; i++)
    {
        list = list->next;
    }
    return list->value;
}

linked_list_map insert_element(linked_list_map list, int nat, map elt)
{

    if (nat > size(list) || nat < 0)
    {
        exit(EXIT_FAILURE);
    }

    cell_map *cell = list;
    cell_map *new_cell = malloc(sizeof(cell_map));
    new_cell->value = elt;

    if (nat == 0)
    {
        new_cell->next = cell;
        list = new_cell;
    }
    else
    {
        for (int i = 0; i < nat - 1; i++)
        {
            cell = cell->next;
        }
        new_cell->next = cell->next;
        cell->next = new_cell;
    }
    return list;
}

linked_list_map remove_element(linked_list_map list, int nat)
{

    if (nat >= size(list) || nat < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (nat == 0)
    {
        list = list->next;
    }
    else
    {
        cell_map *cell = list;
        for (int i = 0; i < nat - 1; i++)
        {
            cell = cell->next;
        }
        cell_map *old_cell = cell->next;
        cell->next = old_cell->next;

        // Free the deleted cell
        free((old_cell->value).str);
        free(old_cell);
        old_cell = NULL;
    }
    return list;
}

void deallocate_list(linked_list_map list)
{

    if (!is_empty(list))
    {
        cell_map *old_cell = list;
        cell_map *cell = old_cell->next;
        free((old_cell->value).str);
        free(old_cell);
        deallocate_list(cell);
    }
}

void print_list(linked_list_map list)
{

    while (!is_empty(list))
    {
        print_map(list->value);
        list = list->next;
    }
    printf("\n");
}

bool is_map_in_list(map my_map, linked_list_map list)
{

    while (!is_empty(list))
    {
        if (are_players_pos_equal(my_map, list->value) && are_maps_strings_equal(my_map, list->value))
        {
            return true;
        }
        list = list->next;
    }
    return false;
}