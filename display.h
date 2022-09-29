#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "map.h"
#include "robot.h"
#include "queue.h"

void display_top_map(int map_side_size);

void display_bottom_map(int map_side_size);

void display_map_or_queue(struct Map * map, int ** status, int map_side_size);

void display_map(struct Map *map);

void display_robot_attributes();

void display_queue(struct Queue * q);

#endif // DISPLAY_H_