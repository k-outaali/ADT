#ifndef MAP_H
#define MAP_H


#include <stdint.h>


struct node {
    char *key;
    void *value;
    struct node *next;
};

typedef struct node node_t;

struct map {
    uint32_t size;
    uint32_t item_size;
    struct node *arr;
};

typedef struct map map_t;

map_t *map_init(uint32_t size, uint32_t item_size);

int map_destroy(map_t *map);

int map_push(map_t *map, void *item, char *key);

void *map_get(map_t *map, char *key);

#endif // MAP_H