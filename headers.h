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
void insertToList(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, direction d);
void printList(listPointers *listpt, direction d);
void deleteListElement(listPointers *listpt, direction d);
void deleteWholeList(listPointers *listpt);
Album * findInList(unsigned int id, listPointers *listpt);
void insertByOrder(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, sort_order d);
bool isEmpty(listPointers *listpt);
int countListNodes(listPointers *listpt);
void reverseList(listPointers *listpt);




#endif // HEADERS_H_INCLUDED
