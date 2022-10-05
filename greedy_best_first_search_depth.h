#ifndef GREEDY_BEST_FIRST_SEARCH_H_
#define GREEDY_BEST_FIRST_SEARCH_H_

#include "robot.h"
#include "display.h"

#define MAX_ACTIONS 10
#define NB_LEARNING_LOOPS 20

struct node** greedy_best_first_search_depth(struct Map* map, int depth);

int follow_path_greedy(struct Map* map, struct node* q_path[], int depth, int limit);

int best_gbfs_nb_actions(struct Map* map, int depth);

#endif