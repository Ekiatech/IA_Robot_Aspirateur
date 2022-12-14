#ifndef ROBOT_H_
#define ROBOT_H_

#include "map.h"
#include "queue_informed_algo.h"

/************ ENUMs ************/

typedef enum {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    CLEAN = 4,
    PICK_UP = 5,
    STOP = 6
} Action;

/************ STRUCTs ************/

struct Robot {
    int position[2];
    int energy;
    int points;
};

/************ FCTs ************/

struct Robot * create_robot(int coordinates[2], int initial_energy);

void clean(struct Map * map);

void pick_up(struct Map * map);

void move(struct Map * map, Action move);

void robot_action(struct Map * map, Action action);

int distance_robot_room(struct Map* map, int x, int y);

#endif // ROBOT_H_
