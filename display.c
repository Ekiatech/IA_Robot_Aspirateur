#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "display.h"

void display_top_map(int map_side_size) {
    printf("\n");
    for (int i = 0; i < map_side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map_side_size; j++) {
                if ((i == 0) && (l == 0)) {
                    printf("    %d", j);
                }
                printf("\t");
            }
        }
    }
    printf("\n");
    for (int i = 0; i < map_side_size; i++) {
        printf("--------");
    }
    printf("\n");
}

void display_bottom_map(int map_side_size) {
    for (int i = 0; i < map_side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map_side_size; j++) {
                if ((i == 0) && (l == 0)) {
                    printf("    %d", j);
                }
                printf("\t");
            }
        }
    }
}

void display_map_or_queue(struct Map * map, int ** status, int map_side_size) {
    display_top_map(map_side_size);
    for (int i = 0; i < map_side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map_side_size; j++) {
                if (j == 0) {
                    printf("|");
                }
                if (status != NULL) {
                    if (l == 1)
                        printf("   %d", status[i][j]);
                }
                else if (map != NULL) {
                    if ((map->robot->position[0] == i) && (map->robot->position[1] == j) && (l == 0))
                        printf("   R");
                    if (((map->rooms[i][j].objects[0] == 1) || (map->rooms[i][j].objects[1] == 1)) && (l == 1))
                        printf("   D");
                    if (((map->rooms[i ][j].objects[0] == 2) || (map->rooms[i][j].objects[1] == 2)) && (l == 2))
                        printf("   J");
                }
                printf("\t|");
            }
            if (l == 1) {
                printf("   %d", i);
            }
            printf("\n");
        }
        for (int i = 0; i < map_side_size; i++) {
            printf("--------");
        }
        printf("\n");
    }
    display_bottom_map(map_side_size);
    if (map != NULL) {
        printf("\n\n");
        display_robot_attributes(map);
    }
    printf("\n");
}

void display_map(struct Map * map) {
    int map_side_size = map->side_size;
    display_map_or_queue(map, NULL, map_side_size);
}

void display_robot_attributes(struct Map * map) {
    printf("Robot :\n");
    printf("\t- position : %d:%d\n", map->robot->position[0], map->robot->position[1]);
    printf("\t- energy : %d\n", map->robot->energy);
    printf("\t- points : %d\n", map->robot->points);
}


// // Display status of nodes in queue from Front to Rear
// void display_queue(struct Queue * q) {
//     int side_size = sqrt(q->max_size);
//     struct Node * current_node = q->front;
//     int column_counter = 0;
//     int is_last_line, is_top, is_bottom;

//     printf("\nQueue :\n");
//     printf("max size = %d\n", q->max_size);
//     printf("current size = %d\n", q->current_size);
//     printf("STATUS :\n");
//     display_top_map(side_size);

//     while (current_node != NULL) {
//         is_last_line = (column_counter == q->max_size - 1);
//         is_top = ((column_counter % side_size == 0) && !is_last_line);
//         is_bottom = ((column_counter + 1) % side_size == 0);

//         if (column_counter == 0)
//             printf("|");

//         if (is_top) {
//             for (int i = 0; i < side_size; i++) {
//                 printf("   \t|");
//             }
//             printf("\n|");
//         }

//         printf("   %d\t|", current_node->status);
        

//         if (is_bottom) {
//             printf("   %d\n|", column_counter / side_size);
//             if (!is_last_line) {
//                 for (int i = 0; i < side_size; i++) {
//                     printf("   \t|");
//                 }
//                 printf("\n|");
//                 for (int i = 0; i < side_size; i++) {
//                     printf("--------");
//                 }
//                 printf("\n|");
//             }
//         }
        
//         current_node = current_node->previous;
//         column_counter++;
//     }
    
//     for (int i = 0; i < side_size; i++) {
//         printf("   \t|");
//     }
//     printf("\n");
//     for (int i = 0; i < side_size; i++) {
//         printf("--------");
//     }
//     printf("\n");
//     display_bottom_map(side_size);
//     printf("\n");
// }

// Display status of nodes in queue from Front to Rear
void display_queue(struct Queue * q) {
    int side_size = sqrt(q->max_size);
    struct Node * current_node = q->front;
    int column_counter = 0;
    int ** status_mat = (int **) malloc(side_size * sizeof(int *));

    for (int i = 0; i < side_size; i++) {
        status_mat[i] = (int *) malloc(side_size * sizeof(int));
        for (int j = 0; j < side_size; j++) {
            status_mat[i][j] = 0;
        }
    }

    printf("\nQueue :\n");
    printf("max size = %d\n", q->max_size);
    printf("current size = %d\n", q->current_size);
    printf("Status :\n");

    while (current_node != NULL) {
        // printf("%d:%d = %d\n", current_node->room->position[0], current_node->room->position[1], current_node->status);
        // printf("current_node->room->position[0] = %d, current_node->room->position[1] = %d\n", current_node->room->position[0], current_node->room->position[1]);
        // printf("status_mat[current_node->room->position[0]][current_node->room->position[1]] = %d\n", status_mat[current_node->room->position[0]][current_node->room->position[1]]);
        // printf("current_node->status = %d\n", current_node->status);
        status_mat[current_node->room->position[0]][current_node->room->position[1]] = current_node->status;
        current_node = current_node->previous;
        column_counter++;
    }

    display_map_or_queue(NULL, status_mat, side_size);

    for (int i = 0; i < side_size; i++) {
        free(status_mat[i]);
    }
    free(status_mat);

    printf("\n");
}
