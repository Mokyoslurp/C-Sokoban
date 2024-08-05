/**
 * @file test-bst-map.c
 * @author M.Giordani
 * @brief Test for the BST (here AVL trees) functionalities
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "loader.h"
#include "sokoban.h"
#include "bst_map.h"

int main()
{
	printf("BST map tests launched ...\n");

	bst_map tree = nil_bst();
	printf("tree created\n");

	int s = size_bst(tree);
	int h = height(tree);
	printf("is my tree empty : %s\n", is_empty_bst(tree) ? "yes" : "no");
	printf("size of my tree : %d\n", s);
	printf("height of my tree : %d\n", h);

	map my_map = load_map("./data/soko99.in");
	tree = insert(tree, my_map);
	my_map = move(my_map, LEFT);
	tree = insert(tree, my_map);
	my_map = move(my_map, LEFT);
	tree = insert(tree, my_map);
	my_map = move(my_map, UP);
	tree = insert(tree, my_map);
	my_map = move(my_map, UP);
	tree = insert(tree, my_map);
	my_map = move(my_map, RIGHT);
	tree = insert(tree, my_map);
	printf("tree constructed\n");

	printf("is my tree empty : %s\n", is_empty_bst(tree) ? "yes" : "no");
	s = size_bst(tree);
	h = height(tree);
	printf("size of my tree : %d\n", s);
	printf("height of my tree : %d\n", h);

	printf("Removing an element ...\n");
	tree = delete (tree, my_map);

	printf("Here is the complete bst : \n");
	print_bst(tree);

	map new_map = load_map("./data/soko_dumb.in");
	tree = insert(tree, new_map);
	printf("new map inserted\n");

	printf("maps in order : \n");
	in_order_dfs_infix(tree);

	deallocate_bst(tree);

	printf("All BST map tests succeeded !\n\n");

	return 0;
}