#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "robot.h"
#include "map.h"

#define DEFAULT_MAP_SIDE_SIZE 5

int main(int argc, char **argv) {
    int map_side_size = DEFAULT_MAP_SIDE_SIZE;
    if (argc >= 2)
        map_side_size = atoi(argv[1]);
    int robot_points = 0;
    int robot_energy = 100;
    time_t t;
    srand((unsigned) time(&t));
    int robot_coordinates[2] = {rand() % map_side_size, rand() % map_side_size};

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);

    display_map(map);

    Action current_action;
    char action_letter;

    do {
        gen_random_object(map);
        scanf("%s", &action_letter);
        switch (action_letter) {
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