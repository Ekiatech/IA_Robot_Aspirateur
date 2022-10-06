#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "queue_informed_algo.h"

struct node* create_node(struct Map* map, int x, int y, struct node* node){
    struct node* n = malloc(sizeof(struct node));
    n->room = &map->rooms[x][y];
    n->add_by_this_node = node;
    n->next = NULL;
    n->previous = NULL;
    return n;
}

struct queue* create_empty_queue_informed(){
    struct queue* q = malloc(sizeof(struct queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0;
    return q;
}

void push(struct queue* q, struct node* n){
    if (q->first == NULL){
        q->first = n;
        q->last = n;
    }
    else {
        struct node* temp = q->first;
        while (temp->next != NULL){
            temp = temp->next;
        }
        n->previous = temp;
        temp->next = n;
    }
    q->last = n;
    q->size++;
}

struct node pop(struct queue *q){
    struct node* temp = q->first;
    while (temp->next != NULL){
        temp = temp->next;
    }
    struct node return_node = *temp;
    (temp->previous)->next = NULL;
    q->last = temp->previous;
    free(temp);
    q->size--;
    return return_node;
}

struct node* remove_from_queue(struct queue* q, struct node* n){
    if (q->first == n && q->last == n){
        q->first = NULL;
        q->last = NULL;
        q->size--;
        return n;
    }
    else if (q->first == n){
        q->first = n->next;
        (q->first)->previous = NULL;
        n->next = NULL;
        q->size--;
        return n;
    }
    else if (q->last == n){
        q->last = n->previous;
        (q->last)->next = NULL;
        n->previous = NULL;
        q->size--;
        return n;
    }
    struct node* temp = q->first;
    while (temp != n && temp != NULL){
        temp = temp->next;
    }
    if (temp != NULL){
        (temp->previous)->next = temp->next;
        (temp->next)->previous = (temp->previous);
        temp->next = NULL;
        temp->previous = NULL;
        q->size--;
        return temp;
    }
    return NULL;
}

void free_queue_informed(struct queue* q){
    struct node* temp = q->first;
    if (temp != NULL){
        while (temp->next != NULL){
            temp->previous = NULL;
            struct node* temp2 = temp->next;
            free(temp);
            temp = temp2;
        }
        free(temp);
    }
    free(q);
}

void show_queue(struct queue* q){
    printf("\n===== SHOW QUEUE =====\n");
    printf("SIZE : %d\n", q->size);
    struct node* temp = q->first;
    if (temp != NULL){
        while (temp != NULL){
            printf("%p %p -> (%d %d)| ADD BY : %p : %p -> %d %d\n", temp, temp->room, temp->room->position[0], temp->room->position[1], 
            temp->add_by_this_node, temp->add_by_this_node->room, temp->add_by_this_node->room->position[0], temp->add_by_this_node->room->position[1]);
            temp = temp->next;
        }
    }
    printf("===== END QUEUE =====\n");
}