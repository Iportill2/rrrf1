#include "list.h"


int list_init(t_list *lst, size_t cap)
{
    lst->data = malloc(sizeof(int) * cap);
    if (!lst->data)
        return -1;
    lst->size = 0;
    lst->cap = cap;
    if (pthread_mutex_init(&lst->lock, NULL) != 0) 
    {
        free(lst->data);
        return -1;
    }
    return 0;
}

int list_push(t_list *lst, int value)
{
    pthread_mutex_lock(&lst->lock);
    if (lst->size >= lst->cap) 
    {
        pthread_mutex_unlock(&lst->lock);
        return -1;
    }
    lst->data[lst->size++] = value;
    pthread_mutex_unlock(&lst->lock);
    return 0;
}

static int cmp(const void *a, const void *b)
{
    const int *a_value = (const int *)a;   
    const int *b_value = (const int *)b;   

    int x = *a_value;   
    int y = *b_value;   

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

void list_sort(t_list *lst)
{
    qsort(lst->data, lst->size, sizeof(int), cmp);
}

void list_print(const t_list *lst)
{
    size_t i = 0;
    while (i < lst->size)
    {
        print_fd(NULL, &i, &lst->data[i], fileno(stdout));
        i++;
    }
}


void list_free(t_list *lst)
{
    if (!lst)                 
        return;

    pthread_mutex_destroy(&lst->lock);

    free(lst->data);          
    lst->data = NULL;         
    lst->size = 0;            
    lst->cap  = 0;
}

