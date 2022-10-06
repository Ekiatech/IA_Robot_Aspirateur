#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct Room create_empty_room(int coordinates[2]) {
    struct Room room;
    room.position[0] = coordinates[0];
    room.position[1] = coordinates[1];
    room.objects[0] = 0;
    room.objects[1] = 0;
    room.nbr_neighbors = 0;
    room.neighbors[0] = NULL;
    room.heuristic = 0;
    return room;
}

struct Map * create_empty_map(int size, struct Robot * robot) {
    struct Map * map = malloc(sizeof(struct Map));
    map->side_size = size;
    map->robot = robot;
    map->rooms = (struct Room **) malloc(size * sizeof(struct Room *));
    for (int i = 0; i < size; i++) {
        map->rooms[i] = (struct Room *) malloc(size * sizeof(struct Room));
        for (int j = 0; j < size; j++) {
            int room_position[2] = {i, j};
            map->rooms[i][j] = create_empty_room(room_position);
        }
    }
    return map;
}

void init_map(struct Map *map) {
    int nb_objects = 0.2 * (map->side_size * map->side_size);
    int current_object = 0;
    int current_x = 0, current_y = 0;
    int object_has_been_added = 0;
    while (object_has_been_added < nb_objects) {
        current_x = rand() % map->side_size;
        current_y = rand() % map->side_size;
        current_object = choose_dust_or_jewel();
        object_has_been_added += place_object(map, current_x, current_y, current_object, object_has_been_added);
    }
    for (int i = 0; i < map->side_size; i++){
        for (int j = 0 ; j < map->side_size; j++)
            get_neighbors(map, &(map->rooms[i][j]));
    }
}

void free_map(struct Map * map) {
    free(map->robot);
    for (int i = 0; i < map->side_size; i++) {
        free(map->rooms[i]);
    }
    free(map->rooms);
    free(map);
}

int choose_dust_or_jewel() {
    int random = rand() % 50;
    if (random <= 40)
        return 1;
    return 2;    
}

int choose_object() {
    int random = rand() % 100;
    if (random <= 30)
        return 0;
    else if ((random > 30) && (random <= 80))
        return 1;
    return 2;    
}

int int_in_array(int value, int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value)
            return 1;
    }
    return 0;
}

int place_object(struct Map * map, int x_room, int y_room, int object, int object_has_been_added) {
    int first_object = map->rooms[y_room][x_room].objects[0];
    int second_object = map->rooms[y_room][x_room].objects[1];

    if ((first_object == 0) && (second_object != object)) {
        map->rooms[y_room][x_room].objects[0] = object;
        object_has_been_added = 1;
    }
    else if ((second_object == 0) && (first_object != object)) {
        map->rooms[y_room][x_room].objects[1] = object;
        object_has_been_added = 1;
    }
    return object_has_been_added;
}

void gen_random_object(struct Map * map) {
    int gen_object = choose_object();
    int object_has_been_added = 0;
    int total_map_size = map->side_size * map->side_size;
    int tested_rooms = 0;
    int rooms_positions[total_map_size];
    for (int i = 0; i < total_map_size; i++)
        rooms_positions[i] = i; 

    do {
        int random_x = rand() % map->side_size;
        int random_y = rand() % map->side_size;

        int room_number = random_x * map->side_size + random_y;
        int room_not_tested_yet = int_in_array(room_number, rooms_positions, total_map_size);

        if (room_not_tested_yet == 1) {
            rooms_positions[room_number] = -1;
            tested_rooms += 1;

            object_has_been_added += place_object(map, random_x, random_y, gen_object, object_has_been_added);
        }
    }
    while ((object_has_been_added == 0) && (tested_rooms != total_map_size));
}


void get_neighbors(struct Map* map, struct Room* room){
    int n = map->side_size;
    int i = room->position[0];
    int j = room->position[1];
    
    int nbr_neighbors = 0;
    if (j == 0){
        room->neighbors[nbr_neighbors] = &map->rooms[i][j+1];
        nbr_neighbors++;
    }
    else if (j == n - 1){
        room->neighbors[nbr_neighbors] = &map->rooms[i][j-1];
        nbr_neighbors++;
    }
    else{
        room->neighbors[nbr_neighbors] = &map->rooms[i][j-1];
        nbr_neighbors++;
        room->neighbors[nbr_neighbors] = &map->rooms[i][j+1];
        nbr_neighbors++;
    }

    if (i == 0){
        room->neighbors[nbr_neighbors] = &map->rooms[i+1][j];
        nbr_neighbors++;
    }
    else if (i == n - 1){
        room->neighbors[nbr_neighbors] = &map->rooms[i-1][j];
        nbr_neighbors++;
    }
    else{
        room->neighbors[nbr_neighbors] = &map->rooms[i-1][j];
        nbr_neighbors++;
        room->neighbors[nbr_neighbors] = &map->rooms[i+1][j];
        nbr_neighbors++;
    }

    room->nbr_neighbors = nbr_neighbors;
}

int map_cleaned(struct Map* map){
    for (int i = 0; i < map->side_size; i++) {
        for (int j = 0; j < map->side_size; j++){
            if (map->rooms[i][j].objects[0] == DUST
                || map->rooms[i][j].objects[0] == JEWEL
                || map->rooms[i][j].objects[1] == DUST
                || map->rooms[i][j].objects[1] == JEWEL)
                return 0; 
        }
    }
    return 1;
}