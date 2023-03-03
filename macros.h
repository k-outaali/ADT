#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define check(COND, MSG,...) if((COND)){ \
								fprintf(stderr, "[ERROR] @ (file: %s, line: %d, errno: %s) " MSG "\n",__FILE__, __LINE__, strerror(errno), ##__VA_ARGS__);\
								goto fail;\
							}
#endif