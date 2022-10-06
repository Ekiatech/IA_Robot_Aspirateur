#ifndef GREEDY_BEST_FIRST_SEARCH_H_
#define GREEDY_BEST_FIRST_SEARCH_H_

#include "robot.h"
#include "display.h"
#include <unistd.h>

#define MAX_ACTIONS_BEFORE_RECALCULATE 10
#define NB_LEARNING_LOOPS_ALGO 20

void heuristic(struct Map* map);

struct node* get_best_node(struct queue* q);

int is_neighbor_from(struct node* node_from, struct node* node);

int not_depth_reached(struct queue* q_path, int depth, struct node* initial_node);

void push_the_good_path(struct queue* q_path, struct node* initial_node, struct node* the_good_path[], int number_in_good_path);

int room_not_in_queue(struct queue* queue, struct Room* room, struct node* best_node);

void push_nodes_in_waiting_queue(struct Map* map, struct queue* q_waiting, struct node* best_node, struct queue* q_path);

void free_node_tab(struct node** path, int depth);

Action which_side_to_move(int i, int j, struct Room* to);

Action choose_action(struct Map* map, int i, int j);

int nb_max_actions_from_learning();

int follow_path_greedy(struct Map* map, struct node* path[], int depth, int limit, int learning);

struct node** greedy_best_first_search_depth(struct Map* map, int depth);

int best_gbfs_nb_actions(struct Map* map, int depth);

#endif