#include <stdio.h>
#include <stdlib.h>

int strlen(char *Cadena)
{
    int i = 0;
    while (Cadena[i] != '\0')
    {
        i++;
    }
    return i ;
}

char *mygets()
{
    char *str;
    int i = 0, j = 1, k = 0, c;
    str = (char *)malloc(10 * sizeof(char)); //Reserva espacio para 10 caracteres
    do
    {
        c = getchar(); //Lee caracter por caracter la cadena
        str[i] = c;    //LO CONCATENA POSICION A POSICION EN EL PUNTERO
        i++;           //Recorre el caracter.
        k++;           //Auxiliar para saber cuando aumentar memoria.
        if (k >= 10)   //Si k es 10 entonces hace un realloc de otros 10 caracteres
        {
            j++;                                               //Multiplicador de la cantidad de memoria.
            str = (char *)realloc(str, j * 10 * sizeof(char)); //Realoc a la cadena
            k = 0;                                             //Reinicia el contador de caracteres.
        }
    } while (c != '\n'); //Condicion de detencion cuando sea otra linea.
    str[i-1] = '\0';       //Cierra la cadena con caracter terminal.*/
    return str;
}
// A structure to represent an adjacency list nodo
struct nodo
{
    int dato;
    struct nodo* siguiente;
    char estado;

}typedef nodo;

// Adds an edge to an adjacency list
nodo* insertar(nodo* primero , char estado , int dato)
{
    nodo* new_nodo = (nodo*)malloc(sizeof(nodo));
    new_nodo->estado = estado;
    new_nodo->dato = dato;
    new_nodo->siguiente = NULL;
    if (primero==NULL)
    {
        primero = new_nodo;
        return new_nodo;
    }
    primero->siguiente = insertar(primero->siguiente,estado,dato);
    return primero;
}

//Recursive function to check aceptadoance of input
int nfa(nodo** grafo, int current, char* input, int* aceptado, int start)
{
    if (start==(int)strlen(input))
        return aceptado[current];

    nodo* temp = grafo[current];
    while (temp != NULL)
    {
      if (input[start]==temp->estado)
        if (nfa(grafo,temp->dato,input,aceptado,start+1)==1)
           return 1;
      temp=temp->siguiente;
    }
    return 0;
}

int main()
{
    int n;//Numero de nodos
    int i, j;
    char *cad;//Cadena a comprobar
    printf("1)Captura el automata\n");
    printf("Numero de nodos:\n");
    scanf("%d", &n);    //Scan numero de nodos
    nodo *grafo[n + 1]; //Creamos el grafo

    for (i = 0; i < n + 1; i++)//Limpiamos el grafo.
        grafo[i] = NULL;

    int aceptado[n + 1]; //Array para contener el estado del vertice por cada nodo

    for (i = 0; i < n; i++)//Ciclo para obetener la estructura del grafo
    {
        printf("Numero de vertice (nodo)   |     Estado del final 1 -> si 0 ->no  |   Numero de Estados  Valor (0) -> Estado(1)     |\n");
        int index, acc, numero_nodos;
        scanf("%d%d%d", &index, &acc, &numero_nodos);
        aceptado[index] = acc; //Scan estados aceptados

        for (j = 0; j < numero_nodos; j++) //Creamos el grafo
        {
            int nodo_destino;
            int estado;
            scanf("%d%d", &estado, &nodo_destino);
            grafo[index] = insertar(grafo[index], '0' + estado, nodo_destino);
        }
    }

    printf("2)Verificar cadena\n");
    fflush( stdin );
    cad=mygets();
    int result = nfa(grafo,1,cad,aceptado,0);

            if (result==1)
            {
                printf("Cadena aceptada"); }
                else printf("La cadena no esta aceptada");

    return 0;
}