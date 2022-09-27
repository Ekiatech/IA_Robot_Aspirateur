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


