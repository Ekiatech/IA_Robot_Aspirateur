#ifndef ROBOT_H_
#define ROBOT_H_

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

#endif // ROBOT_H_
