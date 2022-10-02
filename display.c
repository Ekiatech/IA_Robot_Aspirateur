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

void display_robot_attributes(struct Map * map) {
    printf("Robot :\n");
    printf("\t- position : %d:%d\n", map->robot->position[0], map->robot->position[1]);
    printf("\t- energy : %d\n", map->robot->energy);
    printf("\t- points : %d\n", map->robot->points);
}

void display_map_and_queue(struct Map * map, struct Queue * q) {
    int map_side_size = map->side_size;
    int ** status_mat = (int **) malloc(map_side_size * sizeof(int *));

    for (int i = 0; i < map_side_size; i++) {
        status_mat[i] = (int *) malloc(map_side_size * sizeof(int));
        for (int j = 0; j < map_side_size; j++) {
            status_mat[i][j] = q->visited_indexes[i * map_side_size + j];
        }
    }

    int room_has_object = 0;
    display_top_map(map_side_size);
    for (int i = 0; i < map_side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map_side_size; j++) {
                room_has_object = 0;
                if (j == 0) {
                    printf("|");
                }
                if (status_mat[i][j] == 0)
                    printf("   ");
                if (status_mat[i][j] == 1)
                    printf("   \033[0;35m");
                if (status_mat[i][j] == 2)
                    printf("   \033[0;31m");
                if ((map->robot->position[0] == i) && (map->robot->position[1] == j) && (l == 0)) {
                    printf("R\033[0;37m");
                    room_has_object = 1;
                }
                if (((map->rooms[i][j].objects[0] == 1) || (map->rooms[i][j].objects[1] == 1)) && (l == 1)) {
                    printf("D\033[0;37m");
                    room_has_object = 1;
                }
                if (((map->rooms[i ][j].objects[0] == 2) || (map->rooms[i][j].objects[1] == 2)) && (l == 2)) {
                    printf("J\033[0;37m");
                    room_has_object = 1;
                }
                if ((room_has_object == 0) && (l == 1))
                    printf("*");
                printf("\033[0;37m");
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
    printf("\n\n");
    display_robot_attributes(map);
    printf("\n");
    display_color_code();

    for (int i = 0; i < map_side_size; i++) {
        free(status_mat[i]);
    }
    free(status_mat);
}

void display_color_code() {
    printf("\n");
    printf("Color code :\n");
    printf("\t- White : \tnode not visited yet\n");
    printf("\t- \033[0;35mPurple\033[0;37m : \tnode in queue\n");
    printf("\t- \033[0;31mRed\033[0;37m : \tnode not in queue anymore\n");
    printf("\n\n\n");
}


void display_map(struct Map * map) {
    int map_side_size = map->side_size;

    display_top_map(map_side_size);
    for (int i = 0; i < map_side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map_side_size; j++) {
                if (j == 0) {
                    printf("|");
                }
                if ((map->robot->position[0] == i) && (map->robot->position[1] == j) && (l == 0))
                    printf("   R");
                if (((map->rooms[i][j].objects[0] == 1) || (map->rooms[i][j].objects[1] == 1)) && (l == 1))
                    printf("   D");
                if (((map->rooms[i ][j].objects[0] == 2) || (map->rooms[i][j].objects[1] == 2)) && (l == 2))
                    printf("   J");
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
    printf("\n\n");
    display_robot_attributes(map);
    printf("\n");
}

void display_path_goal_objects(struct Node * n, int ** selected_path, int objects[2], int goal[2]) {
    int first_object = objects[0], second_object = objects[1];
    printf("Path = ");
    for (int j = 0; j < n->length_path + 1; j++) {
        printf("%d:%d ", selected_path[j][0], selected_path[j][1]);
    }
    printf("\n");
    printf("Goal = %d:%d - ", goal[0], goal[1]);
    printf("Objects : %d, %d\n", first_object, second_object);
}