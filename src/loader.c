#include "sokoban.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

map find_player(map my_map)
{

    int i = -1;
    char actual_char;
    // finds the player char id in the map string and then calculate the player coordinates
    do
    {
        i = i + 1;
        actual_char = *(my_map.str + i);
    } while (actual_char != BOY && actual_char != BOY_ON);

    my_map.player_x = i / my_map.width;
    my_map.player_y = i % my_map.width;

    return my_map;
}

map load_map(char path[])
{

    map my_map;

    // Opening of the file
    FILE *p_file = NULL;
    p_file = fopen(path, "r");
    if (p_file == NULL)
    {
        fprintf(stderr, "Cannot read file %s!\n", path);
        exit(EXIT_FAILURE);
    }

    // Read dimensions on first line
    int fscanf_result = 0;
    fscanf_result = fscanf(p_file, "%d %d\n", &(my_map.width), &(my_map.height));

    if (fscanf_result != 2)
    {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    // Read the rest of the file
    my_map.str = malloc(sizeof(char) * my_map.height * (my_map.width + 1));

    char line_buffer[my_map.width + 2];

    for (int i = 0; i < my_map.height; i++)
    {
        fgets(line_buffer, my_map.width + 2, p_file);
        // memmove use to transfer the string line_buffer to the pointer my_map.str at the right adress
        memmove(my_map.str + i * my_map.width, line_buffer, my_map.width);
    }

    fclose(p_file);
    p_file = NULL;
    // Update my_map with the player coordinates
    my_map = find_player(my_map);

    return my_map;
}
