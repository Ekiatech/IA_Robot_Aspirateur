#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct node {
    struct node* previous;
    struct node* next;
    int val;
    struct Room* r;
};

struct queue{
    struct node* first;
};

struct node* create_node(struct Map* map, int x, int y);

struct queue* create_empty_queue_informed();

void push(struct queue* q, struct node* n);

struct node pop(struct queue *q);

void free_queue_informed(struct queue* q);

void show_queue(struct queue* q);

void get_neighbors(struct Map* map, struct Room* room);