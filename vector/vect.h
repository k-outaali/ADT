#ifndef VECT_H
#define VECT_H

#include <stdint.h>

struct vect{
    uint32_t size;
    uint32_t capacity;
    uint32_t data_size;
    void *data;
};

enum {Int, Char, Double, Bool, Float, Custom};

typedef struct vect vect_t;
 
vect_t *vect_init(uint32_t capacity, uint32_t initial_size, uint32_t type, uint32_t data_size);

int vect_set(vect_t * const vect, const void * const item, uint32_t index);

int vect_push(vect_t *vect, const void * const item);

void *vect_get(const vect_t * const vect, uint32_t index);

int vect_destroy(vect_t *vect);



#endif // VECT_H