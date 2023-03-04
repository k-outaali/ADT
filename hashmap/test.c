#include "map.h"
#include "../macros.h"

int main(){

    typedef struct {
        int i;
        char c;
    } custom_t;

    map_t *map;
    map = map_init(10, sizeof(custom_t));
    check(!map, "init failed");
    custom_t n = {.i = 10, .c = 'a'};
    int i = 0;
    
    n.i += 1;
    n.c += 1;
    printf("key worldworld value {%d, %c }\n", n.i, n.c);
    check(map_push(map, &n, "worldworld") == -1, "push failed");

    n.i += 1;
    n.c += 1;
    printf("key hey value {%d, %c }\n", n.i, n.c);
    check(map_push(map, &n, "hey") == -1, "push failed");

    n.i += 1;
    n.c += 1;
    printf("key heyhey value {%d, %c }\n", n.i, n.c);
    check(map_push(map, &n, "heyhey") == -1, "push failed");

    printf("\n");

    custom_t *m;
    
    check((m = map_get(map, "hey")) == NULL, "get failed");
    printf("key hey value {%d, %c }\n", m->i, m->c);
    
    check((m = map_get(map, "heyhey")) == NULL, "get failed");
    printf("key heyhey value {%d, %c }\n", m->i, m->c);
    
    check((m = map_get(map, "worldworld")) == NULL, "get failed");
    printf("key worldworld value {%d, %c }\n", m->i, m->c);

    //destroy 
    check(map_destroy(map), "destroy failed");
    
    return 0;

    fail:
        map_destroy(map);
        return -1;
}