#include "list.h"
#include "rutine.h"

void print_fd(const char *str, size_t *index, int *number, int fd)
{
    char buffer[128];
    int len = 0;

    if (str)
        len = snprintf(buffer, sizeof(buffer), "%s", str); 
	else if (index && number) 
        len = snprintf(buffer, sizeof(buffer), "[%zu] %d", *index, *number);
	else
        return; 
    
    if (len > 0)
	{
        write(fd, buffer, len);
		write(fd,"\n", 1);
	}
}

bool ParseInt(const char *str, int *out)
{
    errno = 0;
    char *end;
    long v = strtol(str, &end, 10);

    if (end == str)                 
        return false;

    if (errno == ERANGE)          
        return false;

    if (*end != '\0')             
        return false;

    if (v < INT_MIN || v > INT_MAX)
        return false;             

    *out = (int)v;
    return true;                  
}

/* void printstring(const char *str, int fd)
{
    int i = 0;
    while(str && str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
    write(fd,"\n",1);
} */
int main(int ac, char **av)
{
    if (ac != 3) 
	{
		print_fd("Uso: ./program <num_hilos> <num_por_hilo>", NULL, NULL, fileno(stderr));
        return EXIT_FAILURE;
    }

    int num_threads ;
    int per_thread ;

	if (!ParseInt(av[1], &num_threads) || !ParseInt(av[2], &per_thread))
    {
		print_fd("Error: los argumentos deben ser enteros validos", NULL, NULL, fileno(stderr));
    	return EXIT_FAILURE;
    }

    if (num_threads <= 0 || per_thread <= 0) 
	{
		print_fd("Error: los argumentos deben ser numeros enteros con valor superior a cero", NULL, NULL, fileno(stderr));
        return EXIT_FAILURE;
    }

    size_t total = (size_t)num_threads * per_thread;

    t_list pos, neg;

    if (list_init(&pos, total) < 0 || list_init(&neg, total) < 0) 
	{
		print_fd("Error inicializando listas", NULL, NULL, fileno(stderr));
        return EXIT_FAILURE;
    }

    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    
    t_args args = { per_thread, &pos, &neg };

	int i = 0;
	while (i < num_threads) 
	{
	    pthread_create(&threads[i], NULL, rutine, &args);
	    i++;
	}

	i = 0;
	while (i < num_threads) 
	{
	    pthread_join(threads[i], NULL);
	    i++;
	}
    free(threads);

    list_sort(&pos);
    list_sort(&neg);

	print_fd("== Positivos ==", NULL, NULL, fileno(stdout));
    list_print(&pos);


	print_fd("== Negativos ==", NULL, NULL, fileno(stdout));
    list_print(&neg);

    list_free(&pos);
    list_free(&neg);

    return EXIT_SUCCESS;
}
