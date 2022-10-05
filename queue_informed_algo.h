#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct node {
    struct node* previous;
    struct node* next;
    struct Room* room;
    struct node* add_by_this_node;
};

struct queue {
    struct node* first;
    struct node* last;
    int size;
};

struct node* create_node(struct Map* map, int x, int y, struct node* node);

struct queue* create_empty_queue_informed();

void push(struct queue* q, struct node* n);

struct node pop(struct queue *q);

void free_queue_informed(struct queue* q);

void show_queue(struct queue* q);

struct node* remove_from_queue(struct queue* q, struct node* n);