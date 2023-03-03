#include "vect.h"
#include "macros.h"

int main(){

    typedef struct {
        int i;
        char c;
    } custom_t;

    vect_t *vect;
    vect = vect_init(5, 3, Custom, sizeof(custom_t));
    check(!vect, "init failed");
    custom_t n = {.i = 10, .c = 'a'};
    for(int i = 0; i < 3; i++){
        n.i += 1;
        n.c += 1;
        printf("index %d value {%d, %c }\n", i, n.i, n.c);
        check(vect_set(vect, &n, i) == -1, "set failed");
    }

    for(int i = 0; i < 7; i++){
        n.i += 1;
        n.c += 1;
        printf("index %d value {%d, %c }\n", i + 3, n.i, n.c);
        check(vect_push(vect, &n) == -1, "set failed");
    }

    printf("\n");

    custom_t *m;
    for(int i = 0; i < 10; i++){
        check((m = vect_get(vect, i)) == NULL, "get failed");
        printf("index %d value {%d, %c }\n", i, m->i, m->c);
    }
    
    m->i = 100;
    m->c = 'A';
    check(vect_set(vect, m, 0), "set failed");
    check((m = vect_get(vect, 0)) == NULL, "get failed");
    printf("index %d value {%d, %c }\n",0, m->i, m->c);

    //destroy 
    check(vect_destroy(vect), "destroy failed");
    
    return 0;

    fail:
        vect_destroy(vect);
        return -1;
}