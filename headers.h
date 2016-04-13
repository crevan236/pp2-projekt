#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//definicje typów
typedef enum direction{BACK, FRONT} direction;
typedef enum order{ASCENDING, DESCENDING} sort_order;

//definicje struktur
typedef struct list_node
{
    //data
    unsigned int id, year;
    char name[75];
    bool status, listened; // zakupiony, przesłuchany(tak/nie)
    //trzeba dodać gatunek i artysta (pola można nazwać artist i genre)
    //pointers
    struct list_node *prev, *next;
} Album;

typedef struct list_pointers
{
    struct list_node *head, *tail;
} listPointers;

//definicje funkcji




#endif // HEADERS_H_INCLUDED
