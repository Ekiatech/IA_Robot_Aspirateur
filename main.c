#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#include "display.h"
#include "robot.h"
#include "map.h"
#include "queue.h"

#define DEFAULT_MAP_SIDE_SIZE 5
#define DEFAULT_ROBOT_ENERGY 200


void * robot_loop(struct Map * map) {
    printf("Robot :\n");
    struct Queue * q = create_empty_queue(map);
    int n_coordinates[2] = { map->robot->position[0], map->robot->position[1] };
    struct Node * n = create_empty_node(map, n_coordinates);
    push_queue(q, n);
    display_queue(q);
    while (!queue_is_empty(q)) {
        pop_queue(q, map);
        display_queue(q);
        printf("\n");        
    }
    free_queue(q);

    printf("Robot : finished.\n");
    // GET INFO -> BELIEF + GREEDY SEARCH (+ HEURISTIQUE) + BREADTH-FIRST-SEARCH
    // UPDATE STATE -> DESIRE + CHOISIR CHEMIN OPTIMAL
    // CHOOSE ACTION -> INTENTIONS
    // EXECUTE ACTION
}

void * map_loop(struct Map * map) {
    // time_t start = time(NULL);
    // time_t seconds = 60;
    // time_t endwait = start + seconds;

    // while (start < endwait) {
    //     printf("Map :\n");
    //     gen_random_object(map);
    //     display_map(map);
    //     sleep(3);
    //     start = time(NULL);
    // }

    // printf("Map : %ld seconds passed.\n", seconds);
}




int main(int argc, char **argv) {
    int map_side_size = DEFAULT_MAP_SIDE_SIZE;
    if (argc >= 2)
        map_side_size = atoi(argv[1]);
    int robot_points = 0;
    int robot_energy = DEFAULT_ROBOT_ENERGY;
    if (argc >= 3)
        robot_energy = atoi(argv[2]);
    time_t t;
    srand((unsigned) time(&t));
    int robot_coordinates[2] = {rand() % map_side_size, rand() % map_side_size};

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);
    init_map(map);
    display_map(map);

    // struct Queue * q = create_empty_queue(map);

    // int n_coordinates[2] = {robot->position[0], robot->position[1]};
    // struct Node * n = create_empty_node(map, n_coordinates);
    // push_queue(q, n);
    // display_queue(q);

    // pop_queue(q, map);
    // display_queue(q);
    // pop_queue(q, map);
    // display_queue(q);

    pthread_t robot_t, map_t;
    pthread_create(&robot_t, NULL, (void * (*)(void *)) robot_loop, (void *) map);
    pthread_create(&map_t, NULL, (void * (*)(void *)) map_loop, (void *) map);

    pthread_join(robot_t, NULL);
    pthread_join(map_t, NULL);
    
    free_map(map);

    return 0;
}