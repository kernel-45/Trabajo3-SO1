#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <unistd.h>
#include "my_lib.h"

#define ROJO "\x1b[31m"
#define RESET "\033[0m"
#define SUCCESS 0
#define FAILURE -1
#define N_THREADS 10
#define ITERATIONS 1000000
#define N_ELEMENTS 10

struct my_stack *pila;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // semáforo global
pthread_t threads[N_THREADS];

void *worker(void *ptr);

int main(int argc, char *argv[])
{

    if (argc < 2 || argv[1] == NULL)
    {
        fprintf(stderr, ROJO "Tienes que poner el nombre del fichero de la pila después del comando\n" RESET);
        return FAILURE;
    }

    pila = my_stack_read(argv[1]);

    // Inicializamos los datos que meteremos en la pila
    int *data;

    if (pila == NULL)
    { // No existe la pila
        pila = my_stack_init(sizeof(data));

        for (size_t i = 0; i < N_ELEMENTS; i++)
        {
            data = malloc(sizeof(data));

            if (data == NULL)
            {
                fprintf(stderr, ROJO "Error reservando memoria para data con malloc()\n" RESET);
                return FAILURE;
            }

            *data = 0;

            if (my_stack_push(pila, data) < 0)
            {
                fprintf(stderr, ROJO "Error introduciendo elemento en la pila\n" RESET);
                return FAILURE;
            }
        }
        // Si la pila ya existe...
    }
    else if (my_stack_len(pila) < N_ELEMENTS)
    {
        int numElem = 10 - my_stack_len(pila);
        fprintf(stdout, "Se van a introducir %d elementos en la pila\n", numElem);
        for (size_t i = my_stack_len(pila); i < N_ELEMENTS; i++)
        {
            data = malloc(sizeof(data));

            if (data == NULL)
            {
                fprintf(stderr, ROJO "Error reservando memoria para data con malloc()\n" RESET);
                return FAILURE;
            }

            *data = 0;

            if (my_stack_push(pila, data) < 0)
            {
                fprintf(stderr, ROJO "Error introduciendo elemento en la pila\n" RESET);
                return FAILURE;
            }
        }
    }
    // Aquí si no existía la pila se ha creado, si existía y tenía menos de 10 elementos se han añadido
    // hasta los 10, y si no es que tenía más de 10 elementos y no hay que hacer nada más que ignorarlos
    for (size_t i = 0; i < N_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, worker, NULL);
        fprintf(stdout, "Se ha creado el hilo %lu\n", threads[i]);
    }
    // Se han creado todos los hilos, bloqueamos el hilo principal
    for (size_t i = 0; i < N_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    my_stack_write(pila, argv[1]);
    my_stack_purge(pila);
    pthread_exit(NULL);
    return SUCCESS;
}

void *worker(void *ptr)
{
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        // Bloqueamos antes de acceder al contenido de la pila
        pthread_mutex_lock(&mutex);
        int *data = (int *)my_stack_pop(pila);
        pthread_mutex_unlock(&mutex);
        // Es necesario desbloquear, porque si no siempre se estaría accediendo al mismo elemento

        (*data)++; // Incrementamos el valor de los datos extraídos de la pila

        pthread_mutex_lock(&mutex);
        my_stack_push(pila, data);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
