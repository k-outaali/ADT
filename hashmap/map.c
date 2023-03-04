#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "../macros.h"

typedef struct {
        int i;
        char c;
} custom_t;

static uint32_t hash_to_index(char *key, uint32_t size){

    uint32_t sum = 0;
    char *cur = key;
    while(*cur != '\0'){
         sum = sum * 31 + *cur;
         cur++;
    }
    //printf("key=%s index=%d \n", key, sum % size);
    return sum % size;   
}

map_t *map_init(uint32_t size, uint32_t item_size){

    check(size < 1, "wrong size");
    check(item_size < 1, "wrong item_size");

    map_t *map = malloc(sizeof(map_t));
    check(!map, "malloc failed");

    map->size = size;
    map->item_size = item_size;

    map->arr = malloc(map->size * sizeof(node_t));
    check(!map->arr, "malloc fialed");

    return map;

    fail:
        if(map){
            free(map);
        }
        return NULL;
}

int map_destroy(map_t *map){
     
    check(!map, "map is null ptr");

    // loop over all 
    if(map->arr){
        for(int i = 0; i < map->size * sizeof(node_t); i += sizeof(node_t)){
            if((map->arr + i)->key){
                free((map->arr + i)->key);
            }
            if((map->arr + i)->value){
                free((map->arr + i)->value);
            }
            if((map->arr + i)->next){
                free((map->arr + i)->next);
            }
        }
        free(map->arr);
    }
    free(map);
    return 0;

    fail:
        return -1;
}

int map_push(map_t *map, void *item, char *key){

    check(!map, "map is a null ptr");
    check(!item, "item is a null ptr");

    uint32_t index = hash_to_index(key, map->size);
    
    char *ctmp = malloc(strlen(key) + 1);
    check(!ctmp, "malloc failed");
    (map->arr + index * sizeof(node_t))->key = ctmp;
    check(!memcpy(ctmp, item, strlen(key) + 1), "memcpy failed");

    void *vtmp = malloc(map->item_size);
    check(!vtmp, "malloc failed");
    (map->arr + index * sizeof(node_t))->value = vtmp;
    check(!memcpy(vtmp, item, map->item_size), "memcpy failed");

    return 0;

    fail:
        return -1;
}

void *map_get(map_t *map, char *key){

    check(!map, "map is null ptr");
    check(!key, "key is null ptr");

    uint32_t index = hash_to_index(key, map->size);

    if((map->arr + index * sizeof(node_t))->value){
        return (map->arr + index * sizeof(node_t))->value;
    }

    fail:
        return NULL;
}
