#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "sokoban.h"
#include "bst_map.h"

// All of the functions implemented here are made for AVL trees

// Auxiliary functions
void print_level(bst_map tree, int level)
{
    for (int i = 0; i < level - 1; i++)
    {
        printf("   ");
    }

    if (is_empty_bst(tree))
    {
        printf("%snil\n", level == 0 ? "" : " +-");
        return;
    }

    printf("%s\n", level == 0 ? "" : " +-");
    print_map(tree->value);
    print_level(tree->left, level + 1);
    print_level(tree->right, level + 1);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Main functions
void print_bst(bst_map tree)
{
    print_level(tree, 0);
}

bst_map nil_bst()
{
    bst_map tree = NULL;
    return tree;
}

bool is_empty_bst(bst_map tree)
{
    return (tree == NULL);
}

map value(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        return tree->value;
    }
    exit(EXIT_FAILURE);
}

char *str_value(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        return (tree->value).str;
    }
    exit(EXIT_FAILURE);
}

int str_length(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        return (tree->value).height * (tree->value).width;
    }
    exit(EXIT_FAILURE);
}

int size_bst(bst_map tree)
{
    if (is_empty_bst(tree))
    {
        return 0;
    }
    return size_bst(tree->left) + size_bst(tree->right) + 1;
}

int height(bst_map tree)
{
    if (is_empty_bst(tree))
    {
        return -1;
    }
    return tree->height;
}

bst_map left_child(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        return tree->left;
    }
    exit(EXIT_FAILURE);
}

bst_map right_child(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        return tree->right;
    }
    exit(EXIT_FAILURE);
}

bst_map retrieve(bst_map tree, map val)
{
    while (!is_empty_bst(tree))
    {
        if (strncmp(str_value(tree), val.str, str_length(tree)) == 0)
        {
            return tree;
        }
        else if (strncmp(str_value(tree), val.str, str_length(tree)) < 0)
        {
            tree = right_child(tree);
        }
        else
        {
            tree = left_child(tree);
        }
    }
    return nil_bst();
}

bst_map insert(bst_map tree, map val)
{
    if (is_empty_bst(tree))
    {
        tree = malloc(sizeof(bst_node_map));
        tree->value = val;
        tree->left = NULL;
        tree->right = NULL;
        tree->height = 0;

        return tree;
    }
    if (strncmp(str_value(tree), val.str, str_length(tree)) > 0)
    {
        tree->left = insert(tree->left, val);
    }
    else if (strncmp(str_value(tree), val.str, str_length(tree)) < 0)
    {
        tree->right = insert(tree->right, val);
    }

    update_height(tree);
    tree = balance_node(tree);
    return tree;
}

bst_map delete(bst_map tree, map val)
{
    if (is_empty_bst(tree))
    {
        return tree;
    }

    if (strncmp(str_value(tree), val.str, str_length(tree)) > 0)
    {
        tree->left = delete (tree->left, val);
    }
    else if (strncmp(str_value(tree), val.str, str_length(tree)) < 0)
    {
        tree->right = delete (tree->right, val);
    }
    else
    {
        // When the node to delete is found, the childs are checked to see if one is empty
        if (is_empty_bst(tree->left))
        {
            bst_map new_tree = tree;
            tree = new_tree->right;
            free((new_tree->value).str);
            free(new_tree);
        }
        else if (is_empty_bst(tree->right))
        {
            bst_map new_tree = tree;
            tree = new_tree->left;
            free((new_tree->value).str);
            free(new_tree);
        }
        else
        {
            // If both children aren't empty, finds the node with the minimum value to take the place of the deleted node
            bst_map new_tree = tree;
            while (!is_empty_bst(new_tree) && !is_empty_bst(new_tree->left))
            {
                new_tree = new_tree->left;
            }

            tree->value = new_tree->value;

            tree->right = delete (tree->right, new_tree->value);
        }
    }
    update_height(tree);
    tree = balance_node(tree);
    return tree;
}

void in_order_dfs_infix(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        in_order_dfs_infix(left_child(tree));
        print_map(tree->value);
        in_order_dfs_infix(right_child(tree));
    }
}

void deallocate_bst(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        deallocate_bst(left_child(tree));
        deallocate_bst(right_child(tree));
        free((tree->value).str);
        free(tree);
    }
}

int balance_factor(bst_map tree)
{
    if (is_empty_bst(tree))
    {
        return 0;
    }
    return height(right_child(tree)) - height(left_child(tree));
}

bst_map balance_node(bst_map tree)
{
    int bf = balance_factor(tree);
    if (bf <= -2)
    {
        int bfl = balance_factor(left_child(tree));
        if (bfl >= 1)
        {
            tree = left_right_rotate(tree);
        }
        else
        {
            tree = right_rotate(tree);
        }
    }
    else if (bf >= 2)
    {
        int bfr = balance_factor(right_child(tree));
        if (bfr <= -1)
        {
            tree = right_left_rotate(tree);
        }
        else
        {
            tree = left_rotate(tree);
        }
    }
    return tree;
}

bst_map balance_tree(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        tree = balance_node(tree);
        tree->left = balance_tree(left_child(tree));
        tree->right = balance_tree(right_child(tree));
    }
    return tree;
}

bst_map left_rotate(bst_map tree)
{
    bst_map new_tree = tree->right;

    // Rotating
    tree->right = new_tree->left;
    new_tree->left = tree;

    // Update heights
    update_height(tree);
    update_height(new_tree);

    return new_tree;
}

bst_map right_rotate(bst_map tree)
{
    bst_map new_tree = tree->left;

    // Rotating
    tree->left = new_tree->right;
    new_tree->right = tree;

    // Update heights
    update_height(tree);
    update_height(new_tree);

    return new_tree;
}

bst_map left_right_rotate(bst_map tree)
{
    tree->left = left_rotate(tree->left);
    return right_rotate(tree);
}

bst_map right_left_rotate(bst_map tree)
{
    tree->right = right_rotate(tree->right);
    return left_rotate(tree);
}

void update_height(bst_map tree)
{
    if (!is_empty_bst(tree))
    {
        tree->height = max(height(tree->left), height(tree->right)) + 1;
    }
}

bool is_map_in_tree(map value, bst_map tree)
{
    return (retrieve(tree, value) != nil_bst());
}