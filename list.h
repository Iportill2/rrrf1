#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct s_list {
    int *data;
    size_t size;
    size_t cap;
    pthread_mutex_t lock;
} t_list;

void print_fd(const char *str, size_t *index, int *number, int fd);
int  list_init(t_list *lst, size_t cap);
int  list_push(t_list *lst, int value);
void list_sort(t_list *lst);
void list_free(t_list *lst);
void list_print(const t_list *lst);

#endif
