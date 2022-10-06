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
    printf("\n\nStart.\n\n");
    while (map->robot->energy > 0) {
        printf("Start learning stage.\n");
        sleep(1);
        int best_nb_actions = best_nb_actions_bfs(map);
        printf("Best nb actions before observation = %d\n\n", best_nb_actions);
        printf("End Learning stage.\n");
        sleep(2);

        printf("Start normal stage.\n");
        time_t start = time(NULL);
        time_t seconds = 15;
        time_t endwait = start + seconds;
        
        while ((start < endwait) && (map->robot->energy > 0)) {
            printf("New bfs call.\n");
            bfs(map, best_nb_actions);
            sleep(2);
            start = time(NULL);
        }
        printf("End normal stage.\n");
    }
    
    printf("\n\nEnd.\n\n");
}

void action_loop_gbfs(struct Map * map, int depth) {
    while (map->robot->energy > 0) {
        int best_nb_actions = best_gbfs_nb_actions(map, depth);
        printf("Best nb actions before observation = %d\n\n", best_nb_actions);
        sleep(5);
        time_t start = time(NULL);
        time_t seconds = 5;
        time_t endwait = start + seconds;
        
        while ((start < endwait) && (map->robot->energy > 0)) {
            struct node** path = greedy_best_first_search_depth(map, depth);
            follow_path_greedy(map, path, depth, -1);
            display_map(map);
            //sleep(5);
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
    printf("\n\n");
    printf("Platter settings : \n");
    printf("Side size : %d\nRobot's energy : %d\n", map_side_size, robot_energy);
    if (algorithm == 0) {
        printf("Algorithm : Greedy Best First Search\n");
        printf("Current depth for the Greedy Best First Search algorithm : %d\n", depth);
    }
    else if (algorithm == 1)
        printf("Algorithm : Breadth First Search\n");

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