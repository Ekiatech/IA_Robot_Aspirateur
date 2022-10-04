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
#define DEFAULT_DEPTH 7

void arguments_given(int argc, char* argv[], int* map_side_size, int* robot_energy, int* depth) {
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
        default:
            n++;
            break;
        }
        n++;
    }
}

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
    int depth = DEFAULT_DEPTH;
    int robot_points = 0;
    /*if (argc >= 2)
        map_side_size = atoi(argv[1]);
    if (argc >= 3)
        robot_energy = atoi(argv[2]);*/

    arguments_given(argc, argv, &map_side_size, &robot_energy, &depth);
    printf("Paramètres du plateau : \n");
    printf("Taille cote : %d\nEnergie du robot : %d\n", map_side_size, robot_energy);
    printf("Profondeur actuelle pour le Greedy Best First Search Algorithme %d\n", depth);

    time_t t;
    srand((unsigned) time(&t));
    int robot_coordinates[2] = { rand() % map_side_size, rand() % map_side_size };

    struct Robot * robot = create_robot(robot_coordinates, robot_energy);
    struct Map * map = create_empty_map(map_side_size, robot);
    init_map(map);

    for (int i = 0; i < map_side_size; i++){
        for (int j = 0 ; j < map_side_size; j++)
            get_neighbors(map, &(map->rooms[i][j]));
    }

    struct node** path = greedy_best_first_search_depth(map, depth);
    follow_path_greedy(map, robot, path, depth);

    for (int i = 0; i < depth; i++){
        printf("%d %d -> ", path[i]->room->position[0], path[i]->room->position[1]);
    }
    //show_queue(path);

    for (int i = 0; i < map_side_size; i++){
        for (int j = 0 ; j < map_side_size; j++){
            printf("Room : %d %d : voisins : ", i, j);
            for (int n = 0; n < map->rooms[i][j].nbr_neighbors; n++){
                printf("(%d, %d) -> %d ", map->rooms[i][j].neighbors[n]->position[0], map->rooms[i][j].neighbors[n]->position[1], map->rooms[i][j].neighbors[n]->heuristic);
            }
            printf("\n");
        }
    }

    //action_loop(map);
    // test_loop(map);
    
    free_map(map);

    return 0;
}