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

#define DEFAULT_MAP_SIDE_SIZE 5
#define DEFAULT_ROBOT_ENERGY 2000

void action_loop(struct Map * map) {
    // GET INFO -> BELIEF + GREEDY SEARCH (+ HEURISTIQUE) + BREADTH-FIRST-SEARCH
    // UPDATE STATE -> DESIRE + CHOISIR CHEMIN OPTIMAL
    // CHOOSE ACTION -> INTENTIONS
    // EXECUTE ACTION

    while (map->robot->energy > 0) {
        int best_nb_actions = best_nb_actions_bfs(map);
        printf("Best nb actions before observation = %d\n\n", best_nb_actions);

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

// void test_loop(struct Map * map) {
//     int best = best_nb_actions_bfs(map);
//     printf("Best = %d\n", best);
// }



int main(int argc, char **argv) {
    int map_side_size = DEFAULT_MAP_SIDE_SIZE;
    int robot_energy = DEFAULT_ROBOT_ENERGY;
    int robot_points = 0;
    if (argc >= 2)
        map_side_size = atoi(argv[1]);
    if (argc >= 3)
        robot_energy = atoi(argv[2]);

    time_t t;
    srand((unsigned) time(&t));
    int robot_coordinates[2] = { rand() % map_side_size, rand() % map_side_size };

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);
    init_map(map);

    action_loop(map);
    // test_loop(map);
    
    free_map(map);

    return 0;
}