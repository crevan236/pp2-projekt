#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
    @file headers.h
    \brief Przechowuje definicje typów danych, typów wyliczeniowych, struktur oraz nagłówki funkcji.
*/

//TYPY DANYCH/WYLICZENIOWE
/**
    * \typedef direction
    * \brief Typ danych reprezentujący typ wyliczeniowy direction.
*/
typedef
/**
    * \enum direction{BACK, FRONT}
    * \brief Typ wyliczeniowy który jest używany do informowania czy np. funkcja dodająca element do listy, ma go dodać od przodu listy czy z tyłu.
*/
enum direction{BACK, FRONT}
direction;
/**
    * \typedef sort_order
    * \brief Typ danych reprezentujący typ wyliczeniowy order.
*/
typedef
/**
    * \enum order{ASCENDING, DESCENDING}
    * \brief Typ wyliczeniowy który jest używany do informowania czy np. funkcja dodająca element do listy w sposób uporządkowany ma go dodać w porządku rosnącym, czy malejącym.
*/
enum order{ASCENDING, DESCENDING}
sort_order;

//STRUKTURY
/**
    \typedef Sublist
    \brief Typ danych, każdy element listy przechowującej dane artystów i gatunków muzycznych, jest tego typu.
*/
typedef
/**
    \struct sub_list
    \brief Struktura przechowująca dane jednego elementu listy dwukierunkowej, służącej do przechowywania danych artystów i gatunków muzycznych.
*/
struct sub_list{
    int id;///< Numer id albumu muzycznego do którego przypisany jest ten element listy
    char data[30];///< Zawartość tego elementu listy (gatunek muzyczny / artysta)
    struct sub_list *next;///< Wskaźnik na następny element listy
    struct sub_list *prev;///< Wskaźnik na poprzedni element listy
}
Sublist;
/**
    * \typedef sublistPointers
    * \brief Typ danych, każdy wartownik na liste typu Sublist jest tego typu.
*/
typedef
/**
    * \struct sublist_pointers
    * \brief Struktura przechowująca wskaźniki na początek i koniec listy typu Sublist.
*/
struct sublist_pointers
{
    struct sub_list *head;///< Wskaźnik na początek listy typu Sublist
    struct sub_list *tail;///< Wskaźnik na koniec listy typu Sublist
}
sublistPointers;
/**
    * \typedef Album
    * \brief Typ danych, każdy element listy przechowującej dane albumów muzycznych, jest tego typu.
*/
typedef
/**
    * \struct list_node
    * \brief Struktura przechowująca dane jednego elementu listy dwukierunkowej, służącej do przechowywania danych albumów muzycznych.
*/
struct list_node
{
    //data
    unsigned int id;///< Numer id albumu muzycznego
    unsigned int year;///< Rok wydania albumu muzycznego
    char name[75]; ///< Nazwa albumu muzycznego
    bool status; ///< Zmienna informująca o tym czy album został kupiony
    bool listened; ///< Zmienna informująca o tym czy album został przesłuchany
    //pointers
    struct list_node *next; ///< Wskaźnik na następny element listy typu Album
    struct list_node *prev; ///< Wskaźnik na poprzedni element listy typu Album
} Album;
/**
    * \typedef listPointers
    * \brief Typ danych, każdy wartownik na liste typu Album jest tego typu.
*/
typedef
/**
    * \struct list_pointers
    * \brief Struktura przechowująca wskaźniki na początek i koniec listy typu Album.
*/
struct list_pointers
{
    struct list_node *head;///< Wskaźnik na początek listy typu Album
    struct list_node *tail;///< Wskaźnik na koniec listy typu Album
}
listPointers;
//PROTOTYPY FUNKCJI
//z pliku functions.c
int saveListAndCloseFile(FILE *f, listPointers *listpt);
int maintainFileAndCreateList(FILE *f, listPointers *listpt);
void readAlbumFromFile(FILE *f, Album *q);
void saveAlbumInFile(FILE *f, Album *q);
void insertToList(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, direction d);
void printList(listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept, direction d);
void printAlbum(Album *q, sublistPointers *artistpt, sublistPointers *genrept);
void deleteListElement(listPointers *listpt, direction d);
void deleteIndicatedListElement(Album *q, listPointers *listpt);
void deleteWholeList(listPointers *listpt);
void insertByOrder(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, sort_order d);
int countListNodes(listPointers *listpt);
Album * findInList(unsigned int id, listPointers *listpt);
Album * findByName(char *name, listPointers *listpt);
void findAndPrintByYear(unsigned int year, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept);
void findAndPrintByStatus(int status, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept);
void findAndPrintByListened(int listened, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept);
void ClrScr();
void wait();
bool isBCSN(char *str, const int size);
void insertBCSN(char *str, const int size);
void strToUpper(char *str);
bool isInTab(int *tab, int x, const int size);
void resetTab(int *tab, const int size);
void findNeedleInList(char *needle, listPointers *listpt, int *elements, const int size);


//z pliku sublist_functions.c
int saveSublistAndCloseFile(FILE *f, sublistPointers *listpt);
int maintainFileAndCreateSublist(FILE *f, sublistPointers *listpt);
void readSublistFromFile(FILE *f, Sublist *q);
void saveSublistInFile(FILE *f, Sublist *q);
void insertToSublist(unsigned int id, char *data, sublistPointers *listpt);
void printSublist(sublistPointers *listpt);
void printSublistElements(sublistPointers *listpt, unsigned int id);
void deleteSublistElement(Sublist *q, sublistPointers *listpt);
void deleteWholeSublist(sublistPointers *listpt);
Sublist * findInSublist(unsigned int id, sublistPointers *listpt);
int countSublistNodes(sublistPointers *sublistpt);
int printSublistElementsEdit(sublistPointers *listpt, unsigned int id);
void findNeedleInSublist(char *needle, sublistPointers *listpt, int *elements, const int size);
void insertToSublistAfterIndicatedElement(unsigned int id, char *data, sublistPointers *listpt, Sublist *p);

//z pliku sort_functions.c
void sortAlbumsByName(listPointers *listpt, listPointers *destpt, sort_order Order);
Album * findExtremeByName(listPointers *listpt, sort_order Order);
void sortAlbumsByYear(listPointers *listpt, listPointers *destpt, sort_order Order);
Album * findExtremeByYear(listPointers *listpt, sort_order Order);
void sortAlbumsBySublistData(listPointers *listpt, sublistPointers *subpt, sublistPointers *temppt, int *sorted, const int size, sort_order Order);
Sublist * findExtremeInSublist(sublistPointers *listpt, sort_order Order);



#endif // HEADERS_H_INCLUDED
