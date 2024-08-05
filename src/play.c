/**
 * @file play.c
 *
 * @brief Plays a Sokoban game from a path to a map given in argument
 *
 * @author M.Giordani
 *
 */

// The cache is the amount of movements that the player is allowed to get back to in the past
#define CACHE 15

#include "sokoban.h"
#include "loader.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// To tell SDL a main is already defined
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "gui.h"

int main(int argc, char *argv[])
{

    // Loading of the chosen level
    if (argc != 2)
    {
        fprintf(stderr, "You must provide a file name (with path)!\n");
        exit(EXIT_FAILURE);
    }
    char *path = argv[1];
    map initial_map = load_map(path);

    // The following lines are made to store the movements made during the game to go backwards in it
    map my_map = copy_map(initial_map);
    char *plan_cache = malloc(sizeof(char) * (CACHE + 1));
    int mov_number = -1;

    // definition of a char matrix to fit the GUI_show function parameter
    char level[my_map.height][my_map.width];
    for (int lin = 0; lin < my_map.height; lin++)
    {
        for (int col = 0; col < my_map.width; col++)
        {
            level[lin][col] = access_elem(my_map, lin, col);
        }
    }

    bool stop = false;
    printf("Let's play !\nUse arrow keys to move");
    printf("Use Escape key or Q key to quit the game\nUse tab to go backwards\n");

    // initialize GUI window
    GUI_init("Sokoban", my_map.width, my_map.height);

    // display level
    GUI_show(my_map.width, my_map.height, level);

    while (true)
    {

        switch (GUI_get_key())
        {
        case SDLK_UP:
            my_map = replay(my_map, 1, "N");
            mov_number++;
            strcpy(plan_cache + mov_number, "N");
            break;
        case SDLK_DOWN:
            my_map = replay(my_map, 1, "S");
            mov_number++;
            strcpy(plan_cache + mov_number, "S");
            break;
        case SDLK_LEFT:
            my_map = replay(my_map, 1, "W");
            mov_number++;
            strcpy(plan_cache + mov_number, "W");
            break;
        case SDLK_RIGHT:
            my_map = replay(my_map, 1, "E");
            mov_number++;
            strcpy(plan_cache + mov_number, "E");
            break;
        case SDLK_q:
            stop = true;
            break;
        case SDLK_ESCAPE:
            stop = true;
            break;
        // key to go backward, replays the initial map using the cache
        case SDLK_TAB:
            if (mov_number > -1)
            {
                deallocate_map(my_map);
                my_map = copy_map(initial_map);
                my_map = replay(my_map, mov_number, plan_cache);
                mov_number--;
            }
            break;
        }
        // if cache is full, the memory is move to forbid the player to go further backwards
        if (mov_number == CACHE)
        {
            initial_map = replay(initial_map, 1, plan_cache);
            memmove(plan_cache, plan_cache + 1, CACHE);
            mov_number--;
        }

        // Updating the matrix with the map after movement
        for (int lin = 0; lin < my_map.height; lin++)
        {
            for (int col = 0; col < my_map.width; col++)
            {
                level[lin][col] = access_elem(my_map, lin, col);
            }
        }
        GUI_show(my_map.width, my_map.height, level);

        if (stop)
        {
            deallocate_map(my_map);
            deallocate_map(initial_map);
            free(plan_cache);
            printf("You are quitting us already ?\n");
            break;
        }

        if (is_win(my_map))
        {
            deallocate_map(my_map);
            deallocate_map(initial_map);
            free(plan_cache);
            printf("Congratulations you win !\n");
            break;
        }
    }

    GUI_close();

    return EXIT_SUCCESS;
}
