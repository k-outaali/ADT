#include <stdlib.h>
#include <stdbool.h>


#include "vect.h"
#include "../macros.h"


vect_t *vect_init(uint32_t capacity, uint32_t initial_size, uint32_t type, uint32_t data_size){
    
    check((initial_size > capacity) || (initial_size < 0), "wrong initial size")
    check(capacity <= 0, "wrong capacity");
    check(type < 0, "wrong type");
    vect_t *vect = (vect_t *) malloc(sizeof(vect_t));
    check(!vect, "malloc failed");
    vect->size = initial_size;
    vect->capacity = capacity;
    switch (type){
        case Int:
            vect->data = (int *) malloc(vect->capacity * sizeof(int));
            check(!vect->data, "malloc failed");
            vect->data_size = sizeof(int);
            return vect;
        case Char:
            vect->data = (char *) malloc(vect->capacity * sizeof(char));
            check(!vect->data, "malloc failed");
            vect->data_size = sizeof(char);
            return vect;
        case Double:
            vect->data = (double *) malloc(vect->capacity * sizeof(double));
            check(!vect->data, "malloc failed");
            vect->data_size = sizeof(double);
            return vect;
        case Float:
            vect->data = (float *) malloc(vect->capacity * sizeof(float));
            check(!vect->data, "malloc failed");
            vect->data_size = sizeof(float);
            return vect;
        case Bool:
            vect->data = (bool *) malloc(vect->capacity * sizeof(bool));
            check(!vect->data, "malloc failed");
            vect->data_size = sizeof(bool);
            return vect;
        case Custom:
            check(data_size < 1, "data_size not valid");
            vect->data_size = data_size;
            vect->data = malloc(vect->capacity * data_size);
            check(!vect->data, "malloc failed");
            return vect;
        default:
            goto fail;
    }
    fail:
        if(vect){
            free(vect);
        }
        return NULL;   
}

int vect_set(vect_t * const vect, const void * const item, uint32_t index){

    check(!vect, "invalid pointer vect");
    check(!vect->data, "invalid pointer vect->data");
    check(!item, "invalid pointer item");
    check((index < 0) || (index >= vect->size), "index out of bounds");
    check(!memcpy(vect->data + index * vect->data_size, item, vect->data_size), "memcpy failed");
    return index;

    fail:
        return -1;
}

void *vect_get(const vect_t * const vect, uint32_t index){
    check(!vect, "invalid pointer vect");
    check(!vect->data, "invalid pointer vect->data");
    check((index < 0) || (index >= vect->size), "index out of bounds");
    return vect->data + index * vect->data_size;
    fail:
        return NULL;
}

int vect_destroy(vect_t *vect){
    check(!vect, "invalid pointer vect");
    if(vect->data){
        free(vect->data);
    }
    free(vect);
    return 0;
    fail:
        return -1;
}

int vect_push(vect_t *vect, const void * const item){
    check(!vect, "vect is null pointer");
    check(!item, "item is null pointer");

    if(vect->size + vect->data_size <= vect->capacity){
        check(!memcpy(vect->data + (vect->size++)* vect->data_size, item, vect->data_size), "memcpy failed");
    }
    else{
        void *tmp = realloc(vect->data, (size_t) (vect->capacity * vect->data_size * 2)); //TODO factor
        check(!tmp, "realloc failed");
        vect->data = tmp;
        vect->capacity *= 2;
        check(!memcpy(vect->data + (vect->size++)* vect->data_size, item, vect->data_size), "memcpy failed");
    }
    return 0;

    fail:
        return -1;
}