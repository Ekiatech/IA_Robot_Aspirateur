#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "queue_informed_algo.h"

struct node* create_node(struct Map* map, int x, int y){
    struct node* n = malloc(sizeof(struct node));
    n->r = &map->rooms[x][y];
    return n;
}

struct queue* create_empty_queue_informed(){
    struct queue* q = malloc(sizeof(struct queue));
    q->first = NULL;
    return q;
}

void push(struct queue* q, struct node* n){
    if (q->first == NULL){
        q->first = n;
    }
    else {
        struct node* temp = q->first;
        while (temp->next != NULL){
            temp = temp->next;
        }
        n->previous = temp;
        temp->next = n;
    }
}

struct node pop(struct queue *q){
    struct node* temp = q->first;
    while (temp->next != NULL){
        temp = temp->next;
    }
    struct node return_node = *temp;
    (temp->previous)->next = NULL;
    free(temp);
    struct node* t = q->first;

    return return_node;
}

void free_queue_informed(struct queue* q){
    struct node* temp = q->first;
    if (temp != NULL){
        while (temp->next != NULL){
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
    struct node* temp = q->first;
    if (temp != NULL){
        while (temp != NULL){
            printf("%d\n", temp->val);
            temp = temp->next;
        }
    }
    printf("===== END QUEUE =====\n");
}

void get_neighbors(struct Map* map, struct Room* room){
    int n = map->side_size;
    int i = room->position[0];
    int j = room->position[1];
    
    int nbr_neighbors = 0;
    if (j == 0){
        room->neighbors[nbr_neighbors] = map->rooms[i][j+1];
        nbr_neighbors++;
    }
    else if (j == n - 1){
        room->neighbors[nbr_neighbors] = map->rooms[i][j-1];
        nbr_neighbors++;
    }
    else{
        room->neighbors[nbr_neighbors] = map->rooms[i][j-1];
        nbr_neighbors++;
        room->neighbors[nbr_neighbors] = map->rooms[i][j+1];
        nbr_neighbors++;
    }

    if (i == 0){
        room->neighbors[nbr_neighbors] = map->rooms[i+1][j];
        nbr_neighbors++;
    }
    else if (i == n - 1){
        room->neighbors[nbr_neighbors] = map->rooms[i-1][j];
        nbr_neighbors++;
    }
    else{
        room->neighbors[nbr_neighbors] = map->rooms[i-1][j];
        nbr_neighbors++;
        room->neighbors[nbr_neighbors] = map->rooms[i+1][j];
        nbr_neighbors++;
    }

}

/*int main(int argc, char* argv[]){
    struct queue* q = create_empty_queue_informed();
    struct node* n1 = malloc(sizeof(struct node));
    n1->previous = NULL;
    n1->next = NULL;
    n1->val = 1;

    push(q, n1);
    show_queue(q);

    struct node* n2 = malloc(sizeof(struct node));
    n2->previous = NULL;
    n2->next = NULL;
    n2->val = 2;

    push(q, n2);
    show_queue(q);

    struct node* n3 = malloc(sizeof(struct node));
    n3->previous = NULL;
    n3->next = NULL;
    n3->val = 3;

    push(q, n3);
    show_queue(q);

    struct node nq = pop(q);
    printf("\nValue return : %d\n", nq.val);
    show_queue(q);

    pop(q);
    show_queue(q);
    
    printf("DONE\n");

    free_queue_informed(q);
}*/