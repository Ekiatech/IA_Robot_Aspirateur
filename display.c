#include <stdio.h>

#include "display.h"

void display_map(struct Map *map) {
    printf("\n");
    for (int i = 0; i < map->side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map->side_size; j++) {
                if ((i == 0) && (l == 0)) {
                    printf("    %d", j);
                }
                printf("\t");
            }
        }
    }
    printf("\n");
    for (int i = 0; i < map->side_size; i++) {
        printf("--------");
    }
    printf("\n");

    for (int i = 0; i < map->side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map->side_size; j++) {
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
        for (int i = 0; i < map->side_size; i++) {
            printf("--------");
        }
        printf("\n");
    }

    for (int i = 0; i < map->side_size; i++) {
        for (int l = 0; l < 3; l++) {
            for (int j = 0; j < map->side_size; j++) {
                if ((i == 0) && (l == 0)) {
                    printf("    %d", j);
                }
                printf("\t");
            }
        }
    }

    printf("\n\n");
    display_robot_attributes(map);
    printf("\n");
}

void display_robot_attributes(struct Map *map) {
    printf("Robot :\n");
    printf("\t- position : %d:%d\n", map->robot->position[0], map->robot->position[1]);
    printf("\t- energy : %d\n", map->robot->energy);
    printf("\t- points : %d\n", map->robot->points);
}
