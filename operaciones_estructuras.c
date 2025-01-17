#define _DEFAULT_SOURCE
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "operaciones_estructuras.h"
#include "estructuras.h"
#include "obtener_hashes.h"

#define READ 0
#define WRITE 1

//Apuntadores de las estructuras
struct Nodo *tope_pila = NULL;
struct Nodo_visitados *cabeza = NULL;
struct Nodo_duplicados *duplicados = NULL;

/*Funcion para comparar los hash*/
void comparar_hash(char* archivo, char hash[33]) {
    struct Nodo_visitados *aux = cabeza->siguiente; 
    int es_duplicado = 0;

    while(aux != NULL && !es_duplicado){

        if(strcmp(aux->valor_hash, hash) == 0){
            es_duplicado = 1;
            insertar_duplicados(aux->nombre_archivo, archivo);
        }
        aux = aux->siguiente;
    }
    //imprimir_lista_duplicados();
}

/*FUNCION PROVISIONAL PARA CORRER obtener_hashes*/
void runner(char modo){
    struct Nodo* stack_runner = tope_pila;

    while (tope_pila!=NULL)
    {
        if(modo == 'e'){
            obtener_hashes_exec(tope_pila->nombre_archivo);
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
        }else 
            if(modo == 'l'){
            obtener_hashes_libreria(tope_pila->nombre_archivo);
            comparar_hash(cabeza->nombre_archivo, cabeza->valor_hash);
        }
        
        pop();
    }
}

/*Funcion para apilar*/
void push(char* nombre){
    struct Nodo *nuevo;
    nuevo = malloc(sizeof(struct Nodo));
    
    //Inicializamos el nuevo nodo
    nuevo->nombre_archivo = (char*)malloc(NAME_MAX);
    strcpy(nuevo->nombre_archivo, nombre);

    if(tope_pila == NULL){ 
        tope_pila = nuevo;
        nuevo->siguiente = NULL;

    }else{
        nuevo->siguiente = tope_pila;
        tope_pila = nuevo;
    }
}

/*Funcion para desapilar*/
void pop(){
    
    if(tope_pila != NULL){
        struct Nodo* eliminado = tope_pila;
        tope_pila = tope_pila->siguiente;
        free(eliminado->nombre_archivo);
        free(eliminado);
    }
}

int esta_contenido(char* nombre){
    struct Nodo* stack_runner = tope_pila;

    while (stack_runner!=NULL)
    {
        if(strcmp(stack_runner->nombre_archivo, nombre)==0){
            return 1;
        }
        
        stack_runner = stack_runner->siguiente;
    }
    return 0;
}

void liberar_pila(){
    struct Nodo *aux = tope_pila;
    struct Nodo *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado->nombre_archivo);
        free(borrado);

    }
}

void insertar_visitados(char* nombre, char codigo[33]){

    int insertado = 0;
    struct Nodo_visitados *nuevo;
    nuevo = malloc(sizeof(struct Nodo_visitados));
    nuevo->nombre_archivo = (char*)malloc(NAME_MAX);
    strcpy(nuevo->nombre_archivo, nombre);
    strcpy(nuevo->valor_hash, codigo);
    
    if(cabeza == NULL){
        cabeza = nuevo;
        nuevo->siguiente = NULL;
    }else{

        struct Nodo_visitados *aux = cabeza;
        while(aux != NULL && !insertado){ 
            if(strcmp(aux->nombre_archivo, nombre) == 0){
                nuevo->siguiente = aux->siguiente;
                aux->siguiente = nuevo;

                insertado = 1;
            }
            aux = aux->siguiente;
        }
        
        if(!insertado){
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
        
    }

}

void insertar_duplicados(char* nombre, char* nombre_duplicado){

    int insertado = 0;
    struct Nodo_duplicados *nuevo;
    nuevo = malloc(sizeof(struct Nodo_duplicados));

    //Inicializamos cada uno de los campos del nuevo nodo
    nuevo->archivo = (char*)malloc(NAME_MAX);
    nuevo->duplicado = (char*)malloc(NAME_MAX);
    strcpy(nuevo->archivo, nombre);
    strcpy(nuevo->duplicado, nombre_duplicado);
    
    if(duplicados == NULL){
        duplicados = nuevo;
        nuevo->siguiente = NULL;
    }else{
        struct Nodo_duplicados *aux = duplicados;

        while(aux != NULL && !insertado){ 
            if((strcmp(aux->archivo, nombre) == 0) && (strcmp(aux->duplicado, nombre_duplicado) == 0) ){

                insertado = 1;
            }
            aux = aux->siguiente;
        }
        
        if(!insertado){
            nuevo->siguiente = duplicados;
            duplicados = nuevo;
        }
    }
}

void liberar_lista(){
    struct Nodo_visitados *aux = cabeza;
    struct Nodo_visitados *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado->nombre_archivo);
        free(borrado);
    }
}

void liberar_lista_duplicados(){
    struct Nodo_duplicados *aux = duplicados;
    struct Nodo_duplicados *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado->archivo);
        free(borrado->duplicado);
        free(borrado);
    }
}

void imprimir_pila(){ 

    struct Nodo *impreso = tope_pila;
    
    while(impreso != NULL){

        printf("%s\n", impreso->nombre_archivo);
        impreso = impreso->siguiente;
    }
}

void imprimir_lista(){ 

    struct Nodo_visitados *impreso = cabeza;
    
    while(impreso != NULL){

        printf("-------------------------------------------------\n");
        printf("%s\n", impreso->nombre_archivo);
        printf("%s\n", impreso->valor_hash);
        printf("-------------------------------------------------\n\n");

        impreso = impreso->siguiente;
    }
}

void imprimir_lista_duplicados(){ 

    struct Nodo_duplicados *impreso = duplicados;
    
    printf("\n*****************LISTA DE DUPLICADOS*************************\n\n\n");

    while(impreso != NULL){

        printf("-------------------------------------------------\n");
        printf("%s, es duplicado de ", impreso->duplicado);
        printf("%s\n", impreso->archivo);
        printf("-------------------------------------------------\n\n");

        impreso = impreso->siguiente;
    }
}