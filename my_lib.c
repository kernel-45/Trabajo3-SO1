/*
código hecho por Iker García de León, Oriol Arderiu Canal, Ignacio Paredes Casanova
*/
#include "my_lib.h"
/*
En la función my_strlen pasamos un puntero por parámetro que apunta a una
cadena de carácteres, incrementamos el valor del puntero y de la variable
"size" de tipo "size_t" (que se ajusta a la arquitectura que estemos usando)
hasta que se encuentre el carácter que indica el fin de la secuencia.
*/
size_t my_strlen(const char *str)
{
    size_t size = 0;
    while (*str != '\0')
    {
        size++;
        str++;
    }
    return size;
}
/*
La función my_strcmp compara dos cadenas de caracteres apuntadas por los punteros
"str1" y "str2". Itera sobre cada par de caracteres correspondientes de ambas cadenas,
incrementando los punteros hasta que encuentra un par de caracteres que no coinciden
o hasta que se llega al final de alguna de las cadenas.
Hace un return de la diferencia entre los dos primeros carácteres que no coinciden.
Si las cadenas son iguales, la función devuelve 0.
La comparación se hace usando "unsigned char" porque si no se pueden interpretar
los carácteres que empiezan por "1" como un número negativo al hacer el casting.
*/
int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return ((unsigned char)*str1 - (unsigned char)*str2);
}
/*
La función my_strcpy copia la cadena de caracteres apuntada por "src" a la ubicación
apuntada por "dest". El puntero original a "dest" se guarda para retornarlo al final,
permitiendo encadenar esta operación con otras. El bucle copia carácter por carácter
hasta encontrar el carácter nulo '\0' que indica el final de "src".
Posteriormente, se añade un carácter nulo al final de "dest".
*/
char *my_strcpy(char *dest, const char *src)
{
    char *og_dest = dest;
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return og_dest;
}
/*
La función my_strncpy copia hasta "n" caracteres de la cadena "src" a "dest",
asegurándose de que "dest" es una cadena de caracteres terminada en nulo.
Si la longitud de "src" es menor a "n", "dest" se rellena con caracteres nulos
hasta alcanzar "n" caracteres en total. La posición original de "dest" se guarda
para poder retornarla, permitiendo operaciones encadenadas.
*/
char *my_strncpy(char *dest, const char *src, size_t n)
{
    char *og_dest = dest;
    while (n && *src)
    {
        *dest = *src;
        src++;
        dest++;
        n--;
    }
    while (n)
    {
        *dest = '\0';
        dest++;
        n--;
    }
    return og_dest;
}
/*
La función my_strcat concatena la cadena "src" al final de la cadena "dest".
Primero, encuentra el final de "dest" avanzando el puntero hasta el carácter nulo '\0'.
Luego, copia los carácteres de "src" a "dest", incluyendo el carácter nulo final de "src".
El puntero original a "dest" se guarda y se retorna..
*/
char *my_strcat(char *dest, const char *src)
{
    char *og_dest = dest;
    while (*dest)
    {
        dest++;
    }
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return og_dest;
}
/*
La función my_strchr busca la primera ocurrencia del carácter "c" en la cadena "str".
Convierte "c" a tipo char para asegurar una comparación adecuada. Itera sobre "str",
comparando cada carácter con "c" hasta encontrar una coincidencia o llegar al final de
la cadena. Si encuentra "c", retorna un puntero al carácter coincidente en "str".
Si "c" es el carácter nulo '\0', verifica si ha llegado al final de "str" y, de ser así,
 retorna un puntero a este carácter nulo. Si no encuentra "c", retorna NULL.
*/
char *my_strchr(const char *str, int c)
{
    // Convertir c a char para la comparación
    char ch = (char)c;

    while (*str)
    {
        if (*str == ch)
        {
            return (char *)str;
        }
        str++;
    }

    // Verificar si c es '\0'
    if (ch == '\0')
    {
        return (char *)str;
    }

    return NULL;
}
struct my_stack *my_stack_init(int size)
{
    struct my_stack *new_stack = malloc(sizeof(struct my_stack));
    if (!new_stack)
    {
        // Manejo de error en caso de que malloc falle
        fprintf(stderr, "Error reservando memoria\n");
        exit(EXIT_FAILURE);
    }
    new_stack->size = size;
    new_stack->top = NULL;
    return new_stack;
}
#define SUCCESS 0
#define FAILURE -1
int my_stack_push(struct my_stack *stack, void *data)
{
    if (!stack)
    {
        fprintf(stderr, "Error, my_stack es null \n");
        return -1;
    }
    if (stack->size == 0)
    {
        fprintf(stderr, "Error, my_stack tiene size 0!\n");
        return -1;
    }
    struct my_stack_node *new_stack_node = malloc(sizeof(struct my_stack_node));
    if (!new_stack_node)
    {
        fprintf(stderr, "Error de asignación de memoria al nuevo nodo\n");
        return -1;
    }
    new_stack_node->data = data;
    new_stack_node->next = stack->top;
    stack->top = new_stack_node;
    return 0;
}
void *my_stack_pop(struct my_stack *stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "Error: Intento de hacer pop en una pila vacía o no inicializada\n");
        return NULL;
    }
    if (stack->top == NULL)
    {
        return NULL;
    }
    struct my_stack_node *node = stack->top;
    void *datos = node->data;
    stack->top = node->next; 
    free(node);
    return datos;
}

int my_stack_len(struct my_stack *stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "Error: La pila es NULL\n");
        return -0;
    }

    int contador = 0;
    struct my_stack_node *new_stack_node = stack->top;

    while (new_stack_node != NULL)
    {
        contador++;
        new_stack_node = new_stack_node->next;
    }

    return contador;
}
int my_stack_purge(struct my_stack *stack) //por cada nodo eliminamos 1 size de cuando inicializamos la pila + los punteros
{
     int contador = 0;
    while(stack->top){
        struct my_stack_node *nodo_aux;
        nodo_aux = stack->top;
        stack->top = nodo_aux->next;
        contador += sizeof(*nodo_aux);
        contador += stack->size;
        free(nodo_aux);
    }
    contador += sizeof(*stack);
    free(stack);

    return contador;
}
int my_stack_write (struct my_stack *stack, char *filename){
    //Abrimos el fichero
int fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error al abrir o crear el archivo");
        return -1;
    }
    //Creamos una pila auxiliar
    struct my_stack *pila_aux = my_stack_init(stack->size); 
    if(!stack){
        printf("Error, pila vacía.\n");
        return -1; 
    }
    //Guardamos el size
    pila_aux->size = stack->size; 
    //Creamos un nodo auxiliar para recorrer la otra pila
    //sin modificarla
    struct my_stack_node *nodo_aux;
    nodo_aux = stack->top;
    //Mientras haya elementos en la pila inicial
    while (nodo_aux)
    {
        //Los metemos en la pila auxiliar
        my_stack_push(pila_aux, nodo_aux->data); 
        nodo_aux = nodo_aux->next; 
    }
    size_t elementos_escritos;
    //Escribimos el size de los datos en el fichero
    write(fd, &stack->size, sizeof(int));
    //Mientras queden datos por escribir los escribimos
    while (pila_aux->top)
    {
        elementos_escritos++;
        write(fd, my_stack_pop(pila_aux), pila_aux->size); 
    }
    close(fd);  // Cerrar el archivo
    return elementos_escritos;
}

struct my_stack *my_stack_read(char *filename){
    int fd;
    int size;
    void *buffer;

    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror("Error al abrir el archivo");
        return NULL;  // Devolvemos NULL en caso de error
    }

    if (read(fd, &size, sizeof(int)) != sizeof(int)) {
        perror("Error al leer el tamaño de la pila");
        close(fd);
        return NULL;
    }

    if (!(buffer = malloc(sizeof(int)))) {
        perror("Error de asignación de memoria para buffer");
        close(fd);
        return NULL;  // Devolvemos NULL en caso de error
    }

    struct my_stack *resultado=my_stack_init(size);
    if (!resultado) {
        perror("Error al inicializar la nueva pila");
        free(buffer);
        close(fd);
        return NULL;
    }

    while (read(fd, buffer, size) > 0) {
        void *data = malloc(size);
        if (!data) {
            perror("Error de asignación de memoria para datos");
            my_stack_purge(resultado);  // Liberar memoria antes de salir
            free(buffer);
            close(fd);
            return NULL;
        }

        memcpy(data, buffer, size);
        my_stack_push(resultado, data);
    }

    free(buffer);
    close(fd);

    return resultado;
}
 
//Open sirve para abrir o crear ficheros
//hay que poner permiso de escritura a los usuarios (el codigo esta en el documento)
//SIEMPRE HAY QUE USAR EL CLOSE
//write: 3 parametros, el file descriptor (que nos devuelve el open), el contenedor
//en que ponemos lo que queremos escribir en el fichero y el tamaño.
//en el fichero solo almacenaremos el size y los datos en si, para nada los punteros 
//size ocupa sizeof(integer) (4 bytes), el *data ocupa (size)
//Queremos escribir en el fichero desde el ultimo elemento de la pila hasta el primero, porque
//es lifo y cuando queramos leerla asi sera mejor. Habrá que hacer malloc.
//El write tiene que devolver el numero de elementos almacenados (el size no cuenta)
// HACER CONTROL DE ERRORES (hay un documento que lo explica)
