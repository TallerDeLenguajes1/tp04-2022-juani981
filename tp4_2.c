#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	int TareaID;//Numerado en ciclo iterativo
	char* Descripcion;
	int Duracion;//Entre 10 a 100
}Tarea;

int ingresarcantTareas();
void ingresarTareas(Tarea** Tareas, int cantTareas);
void moverRealizadas(Tarea** Tareas,Tarea** TareasRealizadas, int cantTareas);
void mostrarTodasTareas(Tarea** Tareas,Tarea** TareasRealizadas, int cantTareas);
void buscarTareaPorID(Tarea **pTareas, Tarea **pTareasRealizadas, int cantidad);
void buscarTareaPorPalabra(Tarea **pTareas, Tarea **pTareasRealizadas, int cantidad);
void liberarMemoria(Tarea **pTareas, Tarea **pTareasRealizadas, int cantidad);

int main(){
    //Decalracion de variables
    Tarea** Tareas;
    Tarea** TareasRealizadas;
    int cantTareas = ingresarcantTareas();
    Tareas = (Tarea**) malloc(sizeof(Tarea*)*cantTareas);
    TareasRealizadas = (Tarea**) malloc(sizeof(Tarea*)*cantTareas);
    //Llamadas a las funciones
    ingresarTareas(Tareas,cantTareas);
    moverRealizadas(Tareas,TareasRealizadas,cantTareas);
    mostrarTodasTareas(Tareas,TareasRealizadas,cantTareas);
    //Probar si funciona busqueda por ID
    buscarTareaPorID(Tareas,TareasRealizadas,cantTareas);
    //Probar si funciona busqueda por palabra
    buscarTareaPorPalabra(Tareas,TareasRealizadas,cantTareas);
    liberarMemoria(Tareas,TareasRealizadas,cantTareas);
    
return 0;
}

int ingresarcantTareas(){
    int cantTareas;
    printf("Ingrese la cantidad de tareas a cargar:");
    scanf("%i",&cantTareas);
    return cantTareas;
}
void ingresarTareas(Tarea** Tareas, int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        Tareas[i] = (Tarea *)malloc(sizeof(Tarea));//De este modo inicializo el vector
        Tareas[i]->TareaID = (i+1);
        Tareas[i]->Descripcion = (char *)malloc(sizeof(char) * 150);//Tambien se puede hacer con Buffer
        getchar();
        printf("Ingresa la Descripcion de la Tarea %d \n", Tareas[i]->TareaID);
        scanf("%s",Tareas[i]->Descripcion);
        Tareas[i]->Duracion = rand()%90 + 10;
    }
}
void moverRealizadas(Tarea** Tareas,Tarea** TareasRealizadas, int cantTareas){
    char* Respuesta;
    Tarea** AuxTarea;
    AuxTarea = (Tarea**)malloc(sizeof(Tarea*)*cantTareas);
    Respuesta = (char*)malloc(sizeof(char)*3);
    for (int i = 0; i < cantTareas; i++)
    {
        printf("===Tarea %i: %s===\n",Tareas[i]->TareaID,Tareas[i]->Descripcion);
        printf("Se realizo esta Tarea? Escriba SI/NO\n");
        getchar();
        scanf("%s",Respuesta);
        if (strcmp(Respuesta,"SI")==0 || strcmp(Respuesta,"Si")==0 || strcmp(Respuesta,"si")==0)
        {
            AuxTarea[i]=Tareas[i];
            Tareas[i]=NULL;
            TareasRealizadas[i]=AuxTarea[i];
        }else
            if(strcmp(Respuesta,"NO")==0 || strcmp(Respuesta,"No")==0 || strcmp(Respuesta,"no")==0){
                TareasRealizadas[i]=NULL;
            }
            else {
                printf("Intente nuevamente\n");
                i--;
            }
    }
}
void mostrarTodasTareas(Tarea** Tareas,Tarea** TareasRealizadas, int cantTareas){
    printf("\tTareasRealizadas\n");
    for (int i = 0; i < cantTareas; i++){
        if(TareasRealizadas[i]!=NULL)
        printf("Tarea %i: %s\n",TareasRealizadas[i]->TareaID,TareasRealizadas[i]->Descripcion);
    }
    printf("\tTareas Pendientes\n");
    for (int j = 0; j < cantTareas; j++){
        if(Tareas[j]!=NULL)
        printf("Tarea %i: %s\n",Tareas[j]->TareaID,Tareas[j]->Descripcion);
    }
}
void buscarTareaPorID(Tarea **pTareas, Tarea **pTareasRealizadas, int cantidad)
{
    int IDBuscado, encontrado=0;
    printf("\nBuscar Tarea por ID:");
    printf("\n\tID a buscar: ");
    scanf("%i",&IDBuscado);
    getchar();
    for (int i = 0; i < cantidad; i++)
    {
        if (pTareas[i]!=NULL && pTareas[i]->TareaID==IDBuscado)
        {
            printf("\nTarea [%i]:", i);
            printf("\n\tID:\t\t%i", pTareas[i]->TareaID);
            printf("\n\tDescripcion:\t%s", pTareas[i]->Descripcion);
            printf("\n\tDuracion:\t%i", pTareas[i]->Duracion);
            printf("\n\tEstado:\t\tIncompleta");
            encontrado=1;
        }
        else if (pTareasRealizadas[i]!=NULL && pTareasRealizadas[i]->TareaID==IDBuscado)
        {
            printf("\nTarea [%i]:", i);
            printf("\n\tID:\t\t%i", pTareasRealizadas[i]->TareaID);
            printf("\n\tDescripcion:\t%s", pTareasRealizadas[i]->Descripcion);
            printf("\n\tDuracion:\t%i", pTareasRealizadas[i]->Duracion);
            printf("\n\tEstado:\t\tRealizada");
            encontrado=1;
        }
    }
    if (!encontrado)
    {
        printf("\nNo se encontro la Tarea con el TareaID buscado.");
    }
    printf("\n------------------------------------------------------------");
}

void buscarTareaPorPalabra(Tarea **pTareas, Tarea **pTareasRealizadas, int cantidad)
{
    int encontrado=0;
    char *buffer = (char *)malloc(150*sizeof(char));
    printf("\nBuscar Tarea por Palabra:");
    printf("\n\tPalabra a buscar: ");
    fgets(buffer,100,stdin);
    for (int i = 0; i < cantidad; i++)
    {
        if (pTareas[i]!=NULL && strstr(pTareas[i]->Descripcion, buffer))
      {
            printf("\nTarea [%i]:", i);
            printf("\n\tID:\t\t%i", pTareas[i]->TareaID);
            printf("\n\tDescripcion:\t%s", pTareas[i]->Descripcion);
            printf("\n\tDuracion:\t%i", pTareas[i]->Duracion);
            printf("\n\tEstado:\t\tIncompleta");
            encontrado=1;
        }
        else if (pTareasRealizadas[i]!=NULL && strstr(pTareasRealizadas[i]->Descripcion, buffer))
      {
            printf("\nTarea [%i]:", i);
            printf("\n\tID:\t\t%i", pTareasRealizadas[i]->TareaID);
            printf("\n\tDescripcion:\t%s", pTareasRealizadas[i]->Descripcion);
            printf("\n\tDuracion:\t%i", pTareasRealizadas[i]->Duracion);
            printf("\n\tEstado:\t\tRealizada");
            encontrado=1;
        }
    }
    free(buffer);
    if (!encontrado)
    {
        printf("\nNo se encontro una Tarea con la palabra buscada.");
    }
    printf("\n------------------------------------------------------------");
}

void liberarMemoria(Tarea **pTareas, Tarea **pTareasRealizadas, int cantidad)
{

    free(*pTareas);
    free(*pTareasRealizadas);
}

