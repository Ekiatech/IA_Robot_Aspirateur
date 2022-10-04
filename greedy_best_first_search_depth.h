#ifndef GREEDY_BEST_FIRST_SEARCH_H_
#define GREEDY_BEST_FIRST_SEARCH_H_

#include "robot.h"
#include "display.h"

struct node** greedy_best_first_search_depth(struct Map* map, int depth);

void follow_path_greedy(struct Map* map, struct Robot* robot, struct node* q_path[], int depth);

#endif