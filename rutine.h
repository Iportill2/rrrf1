#ifndef RUTINE_H
#define RUTINE_H

#include "list.h"

typedef struct s_args {
    int amount;
    t_list *pos;
    t_list *neg;
} t_args;

void *rutine(void *arg);

#endif
