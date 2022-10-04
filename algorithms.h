#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include "map.h"
#include "queue.h"

#define MAX_DISTANCE 8
#define NB_LEARNING_LOOPS 20

/************ FCTs ************/

/*** BFS ***/

int select_action_move(int line_robot, int column_robot, int line_next, int column_next);

int select_action_collect(int objects[2]);

void follow_path(struct Map * map, int objects[2], int ** selected_path, int length_path, int nb_action_btw_update_map);

int ** retrieve_path(struct Node * n);

void bfs(struct Map * map, int nb_action_btw_update_map);

int best_nb_actions_bfs(struct Map * map);

#endif // ALGORITHMS_H_