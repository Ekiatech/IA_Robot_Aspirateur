#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int assign_one_neighbor(int condition, int x, int y, struct Map * map, struct Node * node, int neighbors_counter) {
    int neighbor_coordinates[2] = {0, 0};
    if (condition) {
        neighbor_coordinates[0] = y;
        neighbor_coordinates[1] = x;
        node->neighbors[neighbors_counter] = create_empty_node(map, neighbor_coordinates);
        neighbors_counter++;
    }
    return neighbors_counter;
}

int assign_neighbors(struct Node * node, struct Map * map) {
    int not_first_line      = (node->room->position[0] > 0);
    int not_last_line       = (node->room->position[0] < (map->side_size - 1));
    int not_first_column    = (node->room->position[1] > 0);
    int not_last_column     = (node->room->position[1] < (map->side_size - 1));

    int x_node = node->room->position[1];
    int y_node = node->room->position[0];

    int neighbors_counter = 0;

    neighbors_counter = assign_one_neighbor(not_first_line,    x_node,     y_node - 1, map, node, neighbors_counter);
    neighbors_counter = assign_one_neighbor(not_last_column,   x_node + 1, y_node,     map, node, neighbors_counter);
    neighbors_counter = assign_one_neighbor(not_last_line,     x_node,     y_node + 1, map, node, neighbors_counter);
    neighbors_counter = assign_one_neighbor(not_first_column,  x_node - 1, y_node,     map, node, neighbors_counter);

    return neighbors_counter;
}

struct Node * create_empty_node(struct Map * map, int coordinates[2]) {
    struct Node * node = (struct Node *) malloc(sizeof(struct Node));
    node->status = NOT_VISITED;
    node->room = &map->rooms[coordinates[0]][coordinates[1]];
    node->neighbors = (struct Node **) malloc(sizeof(struct Node * ) * 4);
    for (int i = 0; i < 4; ++i) {
        node->neighbors[i] = NULL;
    }
    node->previous = NULL;
    node->next = NULL;
    return node;
}

struct Queue * create_empty_queue(struct Map * map) {
    struct Queue * queue = malloc(sizeof(struct Queue));
    queue->max_size = map->side_size * map->side_size ; // + 2 for NULL first and last
    queue->current_size = 0;
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void init_queue(struct Queue * q, struct Map * map) {
    int current_coordinates[2] = {0, 0};
    for (int i = 0; i < map->side_size; i++) {
        for (int j = 0; j < map->side_size; j++) {
            q->current_size++;
            current_coordinates[0] = i;
            current_coordinates[1] = j;
            struct Node * current_node = create_empty_node(map, current_coordinates);
            current_node->next = q->rear;
            if ((i == 0) && (j == 0))
                q->front = current_node;
            if (q->rear != NULL)
                q->rear->previous = current_node;
            q->rear = current_node;
        }
    }
}

int queue_is_full(struct Queue * q) {
    return q->current_size == q->max_size;
}

int queue_is_empty(struct Queue * q) {
    return q->current_size == 0;
}

void push_queue(struct Queue * q, struct Node * node) {
    if (!queue_is_full(q)) {
        node->status = IN_QUEUE;
        if (queue_is_empty(q)) {
            node->next = NULL;
            node->previous = NULL;
            q->front = node;
        }
        else {
            q->rear->previous = node;
            node->next = q->rear;
        }
        q->rear = node;
        q->current_size++;
    }
}

struct Node * pop_queue(struct Queue * q, struct Map * map) {
    struct Node * node = NULL;
    if (!queue_is_empty(q)) {
        node = q->front;
        q->current_size--;
        node->status = OUT_QUEUE;
        q->front = q->front->previous;
        int nb_neighbors = assign_neighbors(node, map);
        for (int i = 0; i < nb_neighbors; i++) {
            push_queue(q, node->neighbors[i]);
        }
        q->front->next = NULL;
    }
    return node;
}

void free_node(struct Node * node) {
    free(node->neighbors);
    node->next = NULL;
    node->previous = NULL;
    free(node);
}

void free_queue(struct Queue * q) {
    struct Node * node = q->front;
    struct Node * node_free = q->front;
    while (node != NULL) {
        node_free = node;
        node = node->previous;
        free_node(node_free);
    }
    free(q);
}
