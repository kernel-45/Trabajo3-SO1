#include "my_lib.h"
#include "limits.h"

#define RESET "\033[0m" 
#define ROJO "\x1b[31m"
#define SUCCESS 0
#define FAILURE -1
#define N_ELEMENTS 10

int main(int argc, char *argv[])
{
    int min = INT_MAX; 
    int max = INT_MIN; 
    int sum = 0; 
        if (argv[1] == NULL)
    {
        fprintf(stderr, ROJO, "Tienes que poner el nombre del fichero de la pila después del comando" RESET); 
        return FAILURE; 
    }

    struct my_stack *pila = my_stack_read(argv[1]); 
    if (pila == NULL)
    {
        fprintf(stderr, ROJO "No se ha podido abrir el fichero o está vacío" RESET); 
    }
    fprintf(stdout, "Elementos de la pila: \n"); 
    for (size_t i = 0; i < N_ELEMENTS; i++)
    {
        int *data = my_stack_pop(pila); 
        fprintf(stdout, "%d \n", data); 
        if (data > max){
            max = *data; 
        }
        if (data < min)
        {
            min = *data; 
        }
        sum += *data; 
    }
    fprintf(stdout, "El valor máximo es: %d\nEl valor mínimo es: %d\nLa suma total es: %d\nY la media es %f", max, min, sum, sum/N_ELEMENTS); 
    
    return 0; 
}
