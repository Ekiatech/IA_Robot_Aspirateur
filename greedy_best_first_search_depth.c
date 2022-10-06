#include "greedy_best_first_search_depth.h"

int ACTIONS_COUNTER_FOR_ROBOT = 0;

void heuristic(struct Map* map){
    for (int i = 0; i < map->side_size; i++){
        for (int j = 0; j < map->side_size; j++){
            int object1 = map->rooms[i][j].objects[0];
            object1 = (object1 == DUST) ? object1 * 10 : object1 * 5; 
            int object2 = map->rooms[i][j].objects[1];
            object2 = (object2 == DUST) ? object2 * 10 : object2 * 5; 
            int dist = distance_robot_room(map, i, j);
            int heuristicTemp = object1 + object2 - dist;
            heuristicTemp = (heuristicTemp < 0) ? 0 : heuristicTemp;
            map->rooms[i][j].heuristic = heuristicTemp;
        }
    }
}

struct node* get_best_node(struct queue* q){
    struct node* best_node = q->first;
    if (q->first == NULL)
        return NULL;
    int max = best_node->room->heuristic;
    struct node* temp = q->first;
    while (temp->next != NULL){
        if (max < temp->next->room->heuristic){
            max = temp->next->room->heuristic;
            best_node = temp->next;
        }
        temp = temp->next;
    }
    return best_node;
}

int is_neighbor_from(struct node* node_from, struct node* node){
    for (int i = 0; i < node_from->room->nbr_neighbors; i++){
        if (node_from->room->neighbors[i] == node->room)
            return 1;
    }
    return 0;
}

int not_depth_reached(struct queue* q_path, int depth, struct node* initial_node){
    if (q_path->first == NULL)
        return -1;
    
    struct node* node = q_path->last;
    int n = 1;
    while (is_neighbor_from(initial_node, node) == 0){
        struct node* temp_node = node;
        while(node->add_by_this_node->room != temp_node->room){
            temp_node = temp_node->previous;
        }
        node = temp_node;
        n++;
    }
    if (n == depth)
        return depth;

    return n;
}

void push_the_good_path(struct queue* q_path, struct node* initial_node, struct node* the_good_path[], int number_in_good_path){
    struct node* node = q_path->last;
    int i = number_in_good_path;
    while (i > 0){
        the_good_path[i - 1] = node;
        struct node* temp_node = node;
        if (i != 1){
            while(node->add_by_this_node->room != temp_node->room){
                temp_node = temp_node->previous;
            }
        }
        remove_from_queue(q_path, node);
        node = temp_node;
        i--;
    }
}

int room_not_in_queue(struct queue* queue, struct Room* room, struct node* best_node){
    struct node* node = queue->first;
    while(node != NULL){
        if (node->room == room && node->add_by_this_node->room == best_node->room)
            return 0;
        node = node->next;
    }
    return 1;
}

void push_nodes_in_waiting_queue(struct Map* map, struct queue* q_waiting, struct node* best_node, struct queue* q_path){
    for (int a = 0; a < best_node->room->nbr_neighbors; a++){
        if (best_node->room->neighbors[a] != best_node->add_by_this_node->room 
        && room_not_in_queue(q_waiting, best_node->room->neighbors[a], best_node)
        && room_not_in_queue(q_path, best_node->room->neighbors[a], best_node)){
            struct node* temp_node = create_node(map, best_node->room->neighbors[a]->position[0], 
            best_node->room->neighbors[a]->position[1], best_node);
            push(q_waiting, temp_node);
        }
    }
}

void free_node_tab(struct node** path, int depth){
    for (int i = 0; i < depth; i++){
        path[i]->previous = NULL;
        path[i]->next = NULL;
        free(path[i]);
    }
}

Action which_side_to_move(int i, int j, struct Room* to){
    int new_i = to->position[0];
    int new_j = to->position[1];

    if (new_i == i - 1 && new_j == j)
        return UP;
    else if (new_i == i + 1 && new_j == j)
        return DOWN;
    else if (new_i == i && new_j == j - 1)
        return LEFT;
   return RIGHT;
}
 
Action choose_action(struct Map* map, int i, int j){
    if ((map->rooms[i][j].objects[0] == JEWEL || map->rooms[i][j].objects[1] == JEWEL)){
        return PICK_UP;
    }
    return CLEAN;
}

int nb_max_actions_from_learning(){
    if (NB_LEARNING_LOOPS_ALGO < ACTIONS_COUNTER_FOR_ROBOT){
        return 0;
    }
    return 1;
}

int follow_path_greedy(struct Map* map, struct node* path[], int depth, int limit, int learning){
    int i = map->robot->position[0];
    int j = map->robot->position[1];

    int n = 0;
    int actions = 0;
    int nb_max_actions = 1;

    if (learning){
        nb_max_actions = nb_max_actions_from_learning();
    }

    while (n < depth && map->robot->energy > 0 && actions != limit && nb_max_actions){
        display_map(map);
        if (map->robot->energy < 30)
            sleep(1);
        struct node* node = path[n];
        Action action = 0;
        if (map->rooms[i][j].objects[0] != NOTHING || map->rooms[i][j].objects[1] != NOTHING){
            action = choose_action(map, i, j);
        }
        else{
            action = which_side_to_move(i, j, node->room);
            i = node->room->position[0];
            j = node->room->position[1];
            n++;
        }
        
        robot_action(map, action);
        actions++;
        ACTIONS_COUNTER_FOR_ROBOT++;

        if (ACTIONS_COUNTER_FOR_ROBOT % 2 == 0){
            gen_random_object(map);
        }
    }

    return actions;
}

struct node** greedy_best_first_search_depth(struct Map* map, int depth){
    struct queue* q_waiting = create_empty_queue_informed();
    struct queue* q_path = create_empty_queue_informed();
    heuristic(map);

    int i = map->robot->position[0];
    int j = map->robot->position[1];
    struct node* initial_node = create_node(map, i, j, NULL);
    
    for (int a = 0; a < initial_node->room->nbr_neighbors; a++){
        struct node* temp_node = create_node(map, initial_node->room->neighbors[a]->position[0], 
        initial_node->room->neighbors[a]->position[1], initial_node);
        push(q_waiting, temp_node);
    }

    int the_good_path_reached = -1;
    int the_best_node_null = 0;
    while (the_good_path_reached != depth && the_best_node_null == 0){
        if (map_cleaned(map))
            return NULL;

        struct node* best_node = get_best_node(q_waiting);
        best_node = remove_from_queue(q_waiting, best_node);
        if (best_node != NULL){
            push(q_path, best_node);
            push_nodes_in_waiting_queue(map, q_waiting, best_node, q_path);
        }
        else{
            the_best_node_null = 1;
        }
        the_good_path_reached = not_depth_reached(q_path, depth, initial_node);
    }
    
    struct node** the_good_path = malloc(depth * sizeof(struct node));
    for (int a = 0; a < depth; a++)
        the_good_path[a] = NULL;

    push_the_good_path(q_path, initial_node, the_good_path, the_good_path_reached);

    free(initial_node);
    free_queue_informed(q_waiting);
    free_queue_informed(q_path);

    return the_good_path;
}

int best_gbfs_nb_actions(struct Map* map, int depth){
    int stats_sums[MAX_ACTIONS_BEFORE_RECALCULATE];
    for (int i = 0; i < MAX_ACTIONS_BEFORE_RECALCULATE; i++)
        stats_sums[i] = 0;

    int current_points = 0;
    for (int i = 1; i <= MAX_ACTIONS_BEFORE_RECALCULATE; i++) {
        ACTIONS_COUNTER_FOR_ROBOT = 0;
        for (int j = 0; j < NB_LEARNING_LOOPS_ALGO; j++) {
            current_points = map->robot->points;
            struct node** path = greedy_best_first_search_depth(map, depth);

            int n = 0;
            for (int a = 0; a < depth; a++)
                if (path[a] != NULL)
                    n++;

            if (path != NULL)
                follow_path_greedy(map, path, n, i, 1);
            
            free_node_tab(path, n);
            stats_sums[i - 1] += (map->robot->points - current_points);
        }
    }

    int max = stats_sums[0];
    int best_nb_actions = 1;
    for (int i = 1; i < MAX_ACTIONS_BEFORE_RECALCULATE; i++) {
        if (stats_sums[i] > max) {
            max = stats_sums[i];
            best_nb_actions = i + 1;
        }
    }

    return best_nb_actions;
}