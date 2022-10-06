#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "display.h"
#include "robot.h"
#include "map.h"
#include "queue.h"
#include "algorithms.h"
#include "greedy_best_first_search_depth.h"

#define DEFAULT_MAP_SIDE_SIZE 5
#define DEFAULT_ROBOT_ENERGY 2000
#define DEFAULT_DEPTH 8

void arguments_given(int argc, char* argv[], int* map_side_size, int* robot_energy, int* depth, int* algorithm) {
    int n = 1;
    while (argc > n){
        switch (*(argv[n] + 1))
        {
        case 'n':
            *map_side_size = atoi(argv[n+1]);
            n++;
            break;
        case 'e':
            *robot_energy = atoi(argv[n+1]);
            n++;
            break;
        case 'd':
            *depth = atoi(argv[n+1]);
            n++;
            break;
        case 'a':
            *algorithm = atoi(argv[n+1]);
            n++;
            break;
        default:
            n++;
            break;
        }
        n++;
    }
}

void action_loop_bfs(struct Map * map) {
    while (map->robot->energy > 0) {
        int best_nb_actions = best_nb_actions_bfs(map);
        printf("Best nb actions before observation = %d\n\n", best_nb_actions);
        sleep(2);

        time_t start = time(NULL);
        time_t seconds = 5;
        time_t endwait = start + seconds;
        
        while ((start < endwait) && (map->robot->energy > 0)) {
            bfs(map, best_nb_actions);
            start = time(NULL);
        }
    }
    
    printf("End.\n\n");
}

void action_loop_gbfs(struct Map * map, int depth) {
    while (map->robot->energy > 0 && (!map_cleaned(map))) {
        int best_nb_actions = best_gbfs_nb_actions(map, depth);
        printf("Best nb actions before observation = %d\n\n", best_nb_actions);
        sleep(2);

        time_t start = time(NULL);
        time_t seconds = 100;
        time_t endwait = start + seconds;
        
        while ((start < endwait) && (map->robot->energy > 0) && (!map_cleaned(map))) {
            struct node** path = greedy_best_first_search_depth(map, depth);
            int n = 0;
            for (int i = 0; i < depth; i++)
                if (path[i] != NULL)
                    n++;
            if (path != NULL)
                follow_path_greedy(map, path, n, best_nb_actions, 0);
            start = time(NULL);
        }
    }
}

int main(int argc, char **argv) {
    int map_side_size = DEFAULT_MAP_SIDE_SIZE;
    int robot_energy = DEFAULT_ROBOT_ENERGY;
    int depth = DEFAULT_DEPTH;
    int robot_points = 0;
    int algorithm = 0;

    arguments_given(argc, argv, &map_side_size, &robot_energy, &depth, &algorithm);
    printf("Paramètres du plateau : \n");
    printf("Taille cote : %d\nEnergie du robot : %d\n", map_side_size, robot_energy);
    printf("Profondeur actuelle pour le Greedy Best First Search Algorithme %d\n", depth);

    time_t t;
    srand((unsigned) time(&t));
    int robot_coordinates[2] = { rand() % map_side_size, rand() % map_side_size };

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);
    init_map(map);

    if (algorithm == 0)
        action_loop_gbfs(map, depth);
    else if (algorithm == 1)
        action_loop_bfs(map);
    
    free_map(map);

    return 0;
}