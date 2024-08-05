/**
 * @file bst_map.h
 *
 * @brief AVL trees containing maps
 *
 * @author M.Giordani
 */

#ifndef BST_MAP_H
#define BST_MAP_H

#include <stdbool.h>

#include "sokoban.h"

/**
 * @brief An alias to the structure representing the nodes of
 *        the tree.
 */
typedef struct bst_node_map bst_node_map;

/**
 * @brief A binary tree is just a pointer to the root node
 *        of the tree.
 */
typedef bst_node_map *bst_map;

/**
 * @brief The structure representing the nodes of the
 *        binary tree.
 */
struct bst_node_map
{
    /** The left subtree of the node */
    bst_map left;
    /** The map value in the node */
    map value;
    /** The right subtree of the node */
    bst_map right;
    /** The height of the node */
    int height;
};

/**
 * @brief Create a nil binary search tree.
 *
 * @return an empty binary search tree
 */
bst_map nil_bst();

/**
 * @brief Is the binary search tree empty?
 *
 * @param tree  a the tree you want to check the emptiness
 *
 * @return `true` if `tree` is empty, `false` else
 */
bool is_empty_bst(bst_map tree);

/**
 * @brief The value in the root of the binary search tree.
 *
 * @param tree  the tree
 *
 * @pre `tree` is not empty.
 *
 * @return the value in the root of the tree
 */
map value(bst_map tree);

/**
 * @brief A pointer to the string representing the map at the root of the tree
 *
 * @param tree  the tree
 */
char *str_value(bst_map tree);

/**
 * @brief The length of the string representing the map at the root of the tree
 *
 * @param tree the tree
 */
int str_length(bst_map tree);

/**
 * @brief The number of nodes in the binary search tree.
 *
 * @param tree the tree
 *
 * @return the number of nodes in the tree
 */
int size_bst(bst_map tree);

/**
 * @brief The height of the binary search tree.
 *
 * @param tree the tree
 *
 * @return the height of the tree
 */
int height(bst_map tree);

/**
 * @brief The left subtree of the tree.
 *
 * @param tree the tree
 *
 * @pre `tree` is not empty.
 *
 * @return the left subtree of `tree`
 */
bst_map left_child(bst_map tree);

/**
 * @brief The right subtree of the tree.
 *
 * @param tree the tree
 *
 * @pre `tree` is not empty.
 *
 * @return the right subtree of `tree`
 */
bst_map right_child(bst_map tree);

/**
 * @brief Retrieve a subtree in the tree given the value of
 *        its root.
 *
 * @param tree   a pointer to the tree
 * @param value  the value of the root of the subtree to search
 *
 * @return an empty tree if the value is not in
 *         the binary search tree, the subtree
 *         whose root contains the value otherwise
 */
bst_map retrieve(bst_map tree, map value);

/**
 * @brief Insert a value in the tree.
 *
 * @param tree   the tree in which the value is to be inserted
 * @param value  the value to be inserted
 *
 * @return a tree in which there is a node containing `value`.
 *         This node is correctly placed with respect to the
 *         binary search tree property. If the node was already in
 *         the tree, no new node is inserted and `tree` is returned.
 */
bst_map insert(bst_map tree, map value);

/**
 * @brief Delete a value in the tree.
 *
 * @param tree   the tree in which the value is to be deleted
 * @param value  the value to be deleted
 *
 * @return a tree such that if there was a node containing
 *       `value` in `tree`, then this node is deleted.
 *       This deletion is such that the binary
 *       search property is verified. If the node was
 *       not in the tree, `tree` is returned.
 */
bst_map delete(bst_map tree, map value);

/**
 * @brief Traverse the tree depth-first and print the value
 *        in order (infix style).
 *
 * @param tree  the tree to be traversed
 *
 * @post After the call, the values in the nodes are printed
 *       in order.
 */
void in_order_dfs_infix(bst_map tree);

/**
 * @brief Deallocate a binary search tree.
 *
 * @param tree  the tree to be deallocated
 *
 * @post After the call, all memory regions used for the nodes
 *       are deallocated
 */
void deallocate_bst(bst_map tree);

/**
 * @brief Print the tree.
 *
 * @param tree  the tree to be printed
 *
 * @post After the call, the tree is printed.
 */
void print_bst(bst_map tree);

/**
 * @brief Compute the balance factor of a tree node.
 *
 * @param tree  the tree node considered
 * @return int : the balance factor
 */
int balance_factor(bst_map tree);

/**
 * @brief A node of a BST balanced.
 *
 * @param tree  the tree node considered
 */
bst_map balance_node(bst_map tree);

/**
 * @brief A BST balanced into an AVL tree.
 *
 * @param tree  the tree considered
 */
bst_map balance_tree(bst_map tree);

/**
 * @brief A tree left-rotated.
 *
 * @param tree  the tree considered
 */
bst_map left_rotate(bst_map tree);

/**
 * @brief A tree right-rotated.
 *
 * @param tree  the tree considered
 */
bst_map right_rotate(bst_map tree);

/**
 * @brief A tree left-right-rotated.
 *
 * @param tree  the tree considered
 */
bst_map left_right_rotate(bst_map tree);

/**
 * @brief A tree right-left-rotated.
 *
 * @param tree  the tree considered
 */
bst_map right_left_rotate(bst_map tree);

/**
 * @brief Update the heights of tree nodes if not correct
 */
void update_height(bst_map tree);

/**
 * @brief Return if a map is in a tree
 *
 * @param value The map considered
 * @param tree The tree in which the map is searched
 */
bool is_map_in_tree(map value, bst_map tree);

#endif
