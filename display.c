#include <stdio.h>

#include "display.h"

void display_map(struct Map *map) {
    printf("\n-----------------------------------------\n");
    for (int i = 0; i < map->side_size; i++) {
        for (int l = 0; l < 3; l++)
        {
            for (int j = 0; j < map->side_size; j++) {
                if ((map->robot->position[0] == i) && (map->robot->position[1] == j) && (l == 0))
                    printf("   R");
                if (((map->rooms[i][j].objects[0] == 1) || (map->rooms[i][j].objects[1] == 1)) && (l == 1))
                    printf("   D");
                if (((map->rooms[i ][j].objects[0] == 2) || (map->rooms[i][j].objects[1] == 2)) && (l == 2))
                    printf("   J");
                printf("\t|");
            }
            printf("\n");
        }
        printf("-----------------------------------------\n");
    }
    printf("\n");
    display_actions_help();
    printf("\n");
}

void display_actions_help() {
    printf("- u : move up\n");
    printf("- r : move right\n");
    printf("- d : move down\n");
    printf("- l : move left\n");
    printf("- c : clean\n");
    printf("- p : pick up jewel\n");
    printf("- s : stop\n");
}
