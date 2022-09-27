#include <stdio.h>
#include <stdlib.h>

#include "robot.h"

struct Robot * create_robot(int coordinates[2], int initial_energy) {
    struct Robot * robot = (struct Robot *) malloc(sizeof(struct Robot));
    robot->position[0] = coordinates[0];
    robot->position[1] = coordinates[1];
    robot->energy = initial_energy;
    robot->points = 0;
    return robot;
}


void clean(struct Map * map) {
    int x_robot = map->robot->position[0], y_robot = map->robot->position[1];
    struct Room room = map->rooms[x_robot][y_robot];
    if ((room.objects[0] == 1) || (room.objects[1] == 1)) {
        map->robot->points += 2;
    }
    if ((room.objects[0] == 2) || (room.objects[1] == 2)) {
        map->robot->points -= 5;
    }
    map->rooms[x_robot][y_robot].objects[0] = 0;
    map->rooms[x_robot][y_robot].objects[1] = 0;
}

void pick_up(struct Map * map) {
    int x_robot = map->robot->position[0], y_robot = map->robot->position[1];
    struct Room room = map->rooms[x_robot][y_robot];
    if (room.objects[0] == 2) {
        map->robot->points += 3;
        map->rooms[x_robot][y_robot].objects[0] = 0;
    }
    if (room.objects[1] == 2) {
        map->robot->points += 3;
        map->rooms[x_robot][y_robot].objects[1] = 0;
    }
}

void move_up(struct Map * map, Action move) {
    int x_robot = map->robot->position[1], y_robot = map->robot->position[0];
    int new_y_position = map->robot->position[0] - 1;
    int new_x_position = map->robot->position[1] + 1;
    switch (move) {
        case UP:
            if (new_y_position >= 0) {
                map->robot->position[0] -= 1;
            }
            else {
                printf("There is no room above the robot.\n");
            }
            break;

        case RIGHT:
            if (new_x_position < map->side_size) {
                map->robot->position[1] += 1;
            }
            else {
                printf("There is no room to the right of the robot.\n");
            }
            break;

        case DOWN:
            new_y_position = map->robot->position[0] + 1;
            if (new_y_position < map->side_size) {
                map->robot->position[0] += 1;
            }
            else {
                printf("There is no room below the robot.\n");
            }
            break;

        case LEFT:
            new_x_position = map->robot->position[1] - 1;
            if (new_x_position >= 0) {
                map->robot->position[1] -= 1;
            }
            else {
                printf("There is no room to the left of the robot.\n");
            }
            break;
    }
}

void action(struct Map * map, Action action) {
    map->robot->energy -= 1;
    switch (action) {
        case CLEAN:
            clean(map);
            break;

        case PICK_UP:
            pick_up(map);
            break;

        case UP:
        case RIGHT:
        case DOWN:
        case LEFT:
            move_up(map, action);
            break;
    }
}