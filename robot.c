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

void move(struct Map * map, Action move) {
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
        default:
            break;
    }
}

void robot_action(struct Map * map, Action action) {
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
            move(map, action);
            break;
        default:
            break;
    }
}

void test(struct Map * map){
    for (int i = 0; i < map->side_size; i++){
        for (int j = 0; j < map->side_size; j++){
            printf("(%d, %d) : %d\n", i, j, map->rooms[i][j].objects[0]);
        }
    }
    printf("==============================================\n");
}

int distance_robot_room(struct Map* map, int x, int y){
    int x_robot = map->robot->position[0];
    int y_robot = map->robot->position[0];
    int x_dist = (x > x_robot) ? x - x_robot : x_robot - x;
    int y_dist = (y > y_robot) ? y - y_robot : y_robot - y;
    return x_dist + y_dist;
}

void heuristic(struct Map* map){
    for (int i = 0; i < map->side_size; i++){
        for (int j = 0; j < map->side_size; j++){
            int object1 = map->rooms[i][j].objects[0];
            object1 = (object1 == DUST) ? object1 * 10 : object1 * 5; 
            int object2 = map->rooms[i][j].objects[1];
            object2 = (object2 == DUST) ? object2 * 10 : object2 * 5; 
            int dist = distance_robot_room(map, i, j);
            int heuristicTemp = object1 + object2 - dist;
            heuristicTemp = (heuristicTemp < 0) ? 0 : heuristicTemp;
            map->rooms[i][j].heuristic = heuristicTemp;
            
            printf("(%d, %d) : %d\n", i, j, map->rooms[i][j].heuristic);
        }
    }
}



void greedy_best_first_search_depth(struct Map* map, int depth){
    struct queue * q_path = create_empty_queue();
    struct queue * q_waiting = create_empty_queue();

    int i = map->robot->position[0];
    int j = map->robot->position[1];
    struct node * n = create_node(map, i, j);

    push(q_path, n);
}