#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "map.h"
#include "robot.h"
#include "queue.h"

void display_top_map(int map_side_size);

void display_bottom_map(int map_side_size);

void display_robot_attributes();

void display_map_and_queue(struct Map * map, struct Queue * queue);

void display_color_code();

void display_map(struct Map * map);

void display_path_goal_objects(struct Node * n, int ** selected_path, int objects[2], int goal[2]);

#endif // DISPLAY_H_