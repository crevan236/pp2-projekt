#include "headers.h"

/**
    @file sublist_functions.c
    \brief Przechowuje definicje funkcji do obsługi listy typu Sublist.
*/

//PLIKI

//zapisanie listy i zamkniecie pliku
/**
    * \fn int saveSublistAndCloseFile(FILE *f, sublistPointers *listpt)
    * \brief Funkcja zapisująca listę typu Sublist do pliku i zamyka tenże plik.
    * \param f wskaźnik na plik.
    * \param listpt wskaźnik na strukturę przechowującą wskaźniki na początek i koniec listy typu Sublist.
    * \return -1 w przypadku błędu zamknięcia pliku.
    * \return 0 w przypadku powodzenia.
*/
int saveSublistAndCloseFile(FILE *f, sublistPointers *listpt) {
    if(NULL == f) {
        perror("Blad otwarcia pliku albums.txt");
        return -1;
    }
    //zapisujemy liste do pliku
    Sublist *temp = listpt->tail;
    while(temp != NULL) {
        saveSublistInFile(f, temp);
        temp = temp->prev;
    }
    //zamykamy
    if(fclose(f)) {
        perror("Blad zamkniecia pliku albums.txt");
        return -1;
    }
    return 0;
}
//obsługa pliku i utworzenie listy
/**
    * \fn int maintainFileAndCreateSublist(FILE *f, sublistPointers *listpt)
    * \brief Funkcja otwiera plik zawierający listę typu Sublist, i zapisuje dane z pliku do listy, a następnie zamyka plik.
    * \param f wskaźnik na plik.
    * \param listpt wskaźnik na strukturę przechowującą wskaźniki na początek i koniec listy typu Sublist (do której zapisujemy dane z pliku).
    * \return -1 w przypadku błędu zamknięcia pliku.
    * \return 0 w przypadku powodzenia.
*/
int maintainFileAndCreateSublist(FILE *f, sublistPointers *listpt){
    Sublist *temp = (Sublist *)malloc(sizeof(Sublist));
    //---
    if(NULL == f) {
        perror("Blad otwarcia pliku artists.txt");
        return -1;
    }
    //pobieramy dane i tworzymy listę
    while(!feof(f)) {
        readSublistFromFile(f, temp);
        insertToSublist(temp->id, temp->data, listpt);
    }
    //zamykamy plik
    if(fclose(f)) {
        perror("Blad zamkniecia pliku albums.txt");
        return -1;
    }
    return 0;
}
//wczytuje dane z pliku do elementu listy
/**
    * \fn void readSublistFromFile(FILE *f, Sublist *q)
    * \brief Procedura odczytująca zawartość jednego elementu listy typu Sublist z pliku.
    * \param f wskaźnik na plik.
    * \param q wskaźnik na element listy typu Sublist do którego zapisujemy dane z pliku.
*/
void readSublistFromFile(FILE *f, Sublist *q) {
    if(f) {
        int a;
        fscanf(f, "%d \n", &(q->id));
        fgets(q->data, 30, f);
        //to zczytywanie tylko po to żeby wszystko poprawnie działało
        fscanf(f, "\n", &a);
    }
}
//zapisuje dane z elementu listy do pliku
/**
    * \fn void saveSublistInFile(FILE *f, Sublist *q)
    * \brief Procedura zapisująca zawartość jednego elementu listy typu Sublist do pliku.
    * \param f wskaźnik na plik.
    * \param q wskaźnik na element listy typu Sublist z którego zapisujemy dane do pliku.
*/
void saveSublistInFile(FILE *f, Sublist *q) {
    if(f) {
        fprintf(f, "%d\n", q->id);
        fprintf(f, "%s", q->data);
    }
}

// OBSŁUGA LISTY
//wstawia element na koniec listy
/**
    * \fn void insertToSublist(unsigned int id, char *data, sublistPointers *listpt)
    * \brief Procedura dodająca kolejny element do listy typu Sublist, na jej koniec.
    * \param id numer id albumu który dodajemy do listy
    * \param data wskaźnik na łańcuch znaków
    * \param listpt wskaźnik na strukturę zawierającą wskaźniki na początek i koniec listy do której dodajemy element
*/
void insertToSublist(unsigned int id, char *data, sublistPointers *listpt) {
    Sublist *q = (Sublist *)malloc(sizeof(Sublist));
    //data
    q->id = id;
    strcpy(q->data, data);
    //pointers
    if(listpt->head == NULL) {
        listpt->head = q;
        listpt->tail = q;
        q->prev = q->next = NULL;
    }
    else {
        q->next = NULL;
        q->prev = listpt->tail;
        (listpt->tail)->next = q;
        listpt->tail = q;
    }
}
//wstawia element do listy po podanym przez wskaźnik elemencie
/**
    * \fn void insertToSublistAfterIndicatedElement(unsigned int id, char *data, sublistPointers *listpt, Sublist *p)
    * \brief Procedura dodająca kolejny element do listy typu Sublist, po elemencie wskazanym przez parametr p.
    * \param id numer id albumu który dodajemy do listy
    * \param data wskaźnik na łańcuch znaków
    * \param listpt wskaźnik na strukturę zawierającą wskaźniki na początek i koniec listy do której dodajemy element
    * \param p wskaźnik na element listy po którym wstawiamy nowy element
*/
void insertToSublistAfterIndicatedElement(unsigned int id, char *data, sublistPointers *listpt, Sublist *p) {
    Sublist *q = (Sublist *)malloc(sizeof(Sublist));
    //data
    q->id = id;
    strcpy(q->data, data);
    //pointers
    if(listpt->head == NULL) {
        listpt->head = q;
        listpt->tail = q;
        q->prev = q->next = NULL;
    }
    else {
        q->next = p->next;
        if(p->next != NULL)
            p->next->prev = q;
        q->prev = p;
        p->next = q;
    }
}
//wyświetla listę od końca
/**
    * \fn void printSublist(sublistPointers *listpt)
    * \brief Procedura wyświetlająca całą listę typu Sublist, zaczynając od ostatniego elementu.
    * \param listpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist
*/
void printSublist(sublistPointers *listpt) {
    Sublist *q = listpt->tail;
    while(q) {
        printf("%d\n", q->id);
        printf("%s", q->data);
        q = q->prev;
    }
}
//wyświetla listę od końca po id
/**
    * \fn void printSublistElements(sublistPointers *listpt, unsigned int id)
    * \brief Procedura wyświetlająca elementy listy typu Sublist, których zawartość pola id jest równa parametrowi id
    * (w tym rodzaju listy, kilka elementów może mieć jeden ID).
    * \param listpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist
    * \param id numer ID elementów które chcemy wyswietlić
*/
void printSublistElements(sublistPointers *listpt, unsigned int id) {
    Sublist *q = listpt->tail;
    while(q) {
        if(q->id == id){
            printf("\t%s", q->data);
        }
        q = q->prev;
    }
}
//usuwa element listy
/**
    * \fn void deleteSublistElement(Sublist *q, sublistPointers *listpt)
    * \brief Procedura usuwająca jeden element z listy typu Sublist, wskazany przez parametr q.
    * \param q wskaźnik na element który chcemy usunąć
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist (z której usuwamy element)
*/
void deleteSublistElement(Sublist *q, sublistPointers *listpt) {
    if(q) {
        if(q->prev == NULL && q->next == NULL) {
            listpt->tail = listpt->head = NULL;
            free(q);
        }
        else if(q->next == NULL) {
            q->prev->next = q->next;
            listpt->tail = q->prev;
            free(q);
        }
        else if(q->prev == NULL) {
            q->next->prev = q->prev;
            listpt->head = q->next;
            free(q);
        }
        else {
            q->prev->next = q->next;
            q->next->prev = q->prev;
            free(q);
        }
    }
}
//usuwa całą listę (bez wartowników)
/**
    * \fn void deleteWholeSublist(sublistPointers *listpt)
    * \brief Procedura usuwająca całą listę typu Sublist.
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist (którą usuwamy)
*/
void deleteWholeSublist(sublistPointers *listpt) {
    Sublist *q  = listpt->head;
    while(q) {
        deleteSublistElement(q, listpt);
        q  = listpt->head;
    }
}
//szuka elementu listy zawierającego x w polu value
/**
    * \fn Sublist * findInSublist(unsigned int id, sublistPointers *listpt)
    * \brief Funkcja szukająca na liście typu Sublist, elementu o polu id równemu parametrowi id
    * \param id numer ID szukanego elementu
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist
    * \return q wskaźnik na znaleziony element w przypadku powodzenia
    * \return NULL gdy elementu o podanym id nie ma na liście
*/
Sublist * findInSublist(unsigned int id, sublistPointers *listpt) {
    Sublist *q = listpt->head;
    while(q) {
        if(q->id == id) {
            return q;
        }
        q = q->next;
    }
    return q;
}
//liczy ile elementów jest na subliście
/**
    * \fn int countSublistNodes(sublistPointers *sublistpt)
    * \brief Funkcja licząca ile elementów znajduje się aktualnie na liście typu Sublist
    * \param sublistpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist
    * \return counter ilość elementów na liście
*/
int countSublistNodes(sublistPointers *sublistpt) {
    int counter = 0;
    Sublist *q = sublistpt->head;
    while(q) {
        ++counter;
        q = q->next;
    }
    return counter;
}
//wypisuje elementy do edycji i zlicza ich ilość
/**
    * \fn int printSublistElementsEdit(sublistPointers *listpt, unsigned int id)
    * \brief Procedura wyświetlająca i zliczająca elementy listy typu Sublist, których zawartość pola id jest równa parametrowi id
    * (w tym rodzaju listy, kilka elementów może mieć jeden ID).
    * \param listpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist
    * \param id numer ID elementów które chcemy wyswietlić
    * \return i ilość elementów które wyświetliliśmy
*/
int printSublistElementsEdit(sublistPointers *listpt, unsigned int id) {
    Sublist *q = listpt->tail;
    int i=1;
    while(q) {
        if(q->id == id){
            printf("%d.%s\n", i, q->data);
            i++;
        }
        q = q->prev;
    }
    return i;
}
//wyszukuje wystapienie needle w liscie gatunkow i drukuje te albumy
/**
    * \fn void findNeedleInSublist(char *needle, sublistPointers *listpt, int *elements, const int size)
    * \brief Funkcja szukająca na liście typu Sublist, fragmentów łańcucha (needle) w łańcuchu będącym zawartością pola data.
    * \param needle wskaźnik na łańcuch znaków (część wiekszego łańcucha), którego poszukujemy w innych łańcuchach
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist
    * \param elements wskaźnik na tablicę w której zapisujemy indeksy znalezionych elementów
    * \param size ilość elementów tablicy elements
*/
void findNeedleInSublist(char *needle, sublistPointers *listpt, int *elements, const int size) {
    Sublist *q = listpt->head;
    int i = 0;
    while(q) {
        if(strstr(q->data, needle)) {
            if(!isInTab(elements, q->id, size)){
                elements[i] = q->id;
                ++i;
            }
        }
        q = q->next;
    }
}
