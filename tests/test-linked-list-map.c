/**
 * @file test-linked-list-map.c
 * @author M.Giordani
 * @brief Test for the linked list functionalities
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"
#include "linked_list_map.h"

int main()
{
    printf("Linked list map tests launched ...\n");

    linked_list_map list = nil();
    printf("list created\n");

    int len = size(list);
    printf("is my list empty : %s\n", is_empty(list) ? "yes" : "no");
    printf("length of my list : %d\n", len);

    map my_map = load_map("./data/soko99.in");
    list = cons(my_map, list);
    my_map = move(my_map, LEFT);
    list = cons(my_map, list);
    my_map = move(my_map, LEFT);
    list = cons(my_map, list);
    printf("list constructed\n");

    printf("is my list empty : %s\n", is_empty(list) ? "yes" : "no");
    len = size(list);
    printf("length of my list : %d\n", len);

    int pos = 1;
    printf("element %d : \n", pos);
    print_map(get_element(list, pos));

    printf("Removing an element ...\n");
    list = remove_element(list, pos);

    printf("Here is the complete list : \n");
    print_list(list);

    map new_map = load_map("./data/soko_dumb.in");
    list = insert_element(list, pos, new_map);
    printf("new map inserted at position %d\n", pos);
    print_list(list);

    deallocate_list(list);

    printf("All linked list map tests succeeded !\n\n");

    return 0;
}
