#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "robot.h"
#include "map.h"

int main(int argc, char **argv) {
    int map_side_size = 5;
    int robot_points = 0;
    int robot_energy = 100;
    int robot_coordinates[2] = {0, 0};

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);

    // map->rooms[0][4].objects[1] = 1;
    // map->rooms[1][0].objects[0] = 1;
    // map->rooms[1][2].objects[1] = 2;
    // map->rooms[2][4].objects[0] = 2;
    // map->rooms[3][1].objects[0] = 1;
    // map->rooms[3][1].objects[1] = 2;
    // map->rooms[4][4].objects[0] = 2;
    // map->rooms[4][4].objects[1] = 1;
    // map->rooms[0][0].objects[0] = 2;
    // map->rooms[0][0].objects[1] = 1;
    display_map(map);

    Action current_action;
    char action_letter[2];

    do {
        gen_random_object(map);
        scanf("%s", &action_letter);
        switch (action_letter[0]) {
            case 'u':
            case 'U':
                current_action = 0;
                break;
            case 'r':
            case 'R':
                current_action = 1;
                break;
            case 'd':
            case 'D':
                current_action = 2;
                break;
            case 'l':
            case 'L':
                current_action = 3;
                break;
            case 'c':
            case 'C':
                current_action = 4;
                break;
            case 'p':
            case 'P':
                current_action = 5;
                break;
            case 's':
            case 'S':
                current_action = 6;
                break;
            default:
                printf("This key doesn't correspond to a valid action.\n");
        }
        action(map, current_action);
        display_map(map);
    }
    while (current_action != 6);
    
    
    free_map(map);

    return 0;
}