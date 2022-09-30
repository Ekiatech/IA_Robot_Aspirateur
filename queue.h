#ifndef QUEUE_H_
#define QUEUE_H_

#include "map.h"

/************ ENUMs ************/

typedef enum {
    NOT_VISITED = 0,
    IN_QUEUE = 1,
    OUT_QUEUE = 2
} Status;

/************ STRUCTs ************/

struct Node {
    Status status;
    struct Room * room;
    struct Node ** neighbors;
    struct Node * previous;
    struct Node * next;
};

struct Queue {
    int max_size;
    int current_size;
    struct Node * front;
    struct Node * rear;
    Status * visited_indexes;
};

/************ FCTs ************/

int assign_one_neighbor(int condition, int x, int y, struct Map * map, struct Node * node, int neighbors_counter, struct Queue * q);

int assign_neighbors(struct Node * node, struct Map * map, struct Queue * q);

struct Node * create_empty_node(struct Map * map, int coordinates[2]);

struct Queue * create_empty_queue(struct Map * map);

void init_queue(struct Queue * q, struct Map * map);

int queue_is_full(struct Queue * q);

int queue_is_empty(struct Queue * q);

void push_queue(struct Queue * q, struct Node * node);

struct Node * pop_queue(struct Queue * q, struct Map * map);

void free_node(struct Node * node);

void free_queue(struct Queue * q);

#endif // QUEUE_H_