#ifndef _ESTRUCTURAS_H_
#define _ESTRUCTURAS_H_ 

#include <stdio.h>

//Estructura de datos de tipo pila que contendra los archivos "por visitar"
struct Nodo{
    char* nombre_archivo;
    struct Nodo *siguiente;
};

//Estructura de datos de tipo lista, que contendra los archivos "visitados"
struct Nodo_visitados{
    char* nombre_archivo;
    char valor_hash[33];
    struct Nodo_visitados *siguiente;
};

//Estructura de datos de tipo lista, que contendra los archivos y sus duplicados
struct Nodo_duplicados{
    char* archivo;
    char* duplicado;
    struct Nodo_duplicados *siguiente;
};

//Apuntadores de las estructuras
extern struct Nodo *tope_pila;
extern struct Nodo_visitados *cabeza;
extern struct Nodo_duplicados *duplicados;

#endif 