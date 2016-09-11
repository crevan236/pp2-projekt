#include "headers.h"

/**
    @file sort_functions.c
    \brief Przechowuje definicje funkcji sortujących elementy listy typu Album.
*/

/**
    * \fn void sortAlbumsByName(listPointers *listpt, listPointers *destpt, sort_order Order)
    * \brief Procedura sortująca elementy listy alfabetycznie po polu name.
    * Dla N elementów na liście, znajduje ona N razy minimum/maximum na liście "źrodła" przy uzyciu funkcji findExtremeByName, a następnie dodaje go do listy "destynacji"
    * i usuwa z listy "źródłą". W ten sposób lista jest jakby "przepisywana" z sortowaniem.
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album, która jest listą "źródłą"
    * \param destpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album, która jest listą "destynacji"
    * \param Order wskazuje czy sortujemy rosnąco czy malejąco
*/
void sortAlbumsByName(listPointers *listpt, listPointers *destpt, sort_order Order) {
    while(listpt->head) {
        //znajdujemy pierwszy alfabetycznie album
        Album *temp = findExtremeByName(listpt, Order);
        //dodajemy go do nowej listy
        insertToList(temp->id, temp->year, temp->name, temp->status, temp->listened, destpt, FRONT);
        //usuwamy go ze starej listy
        deleteIndicatedListElement(temp, listpt);
    }
    listpt->head = destpt->head;
    listpt->tail = destpt->tail;
    destpt->head = destpt->tail = NULL;
}

/**
    * \fn Album * findExtremeByName(listPointers *listpt, sort_order Order)
    * \brief Funkcja szukająca na podanej jej liście typu Album, elementu który jest pierwszy/ostatni alfabetycznie, sortując po polu name.
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param Order wskazuje czy szukany element to minimum czy maximum
    * \return min wskaźnik na znaleziony element listy
*/
Album * findExtremeByName(listPointers *listpt, sort_order Order) {
    Album *min = listpt->head;
    Album *q = min->next;
    if(Order == ASCENDING) {
        while(q) {
            int i = 0;
            while(q->name[i] == min->name[i] && q->name[i])
                ++i;
            if(q->name[i] < min->name[i])
                min = q;
            q = q->next;
        }
    }
    else {
        while(q) {
            int i = 0;
            while(q->name[i] == min->name[i] && q->name[i])
                ++i;
            if(q->name[i] > min->name[i])
                min = q;
            q = q->next;
        }
    }
    return min;
}

/**
    * \fn void sortAlbumsByYear(listPointers *listpt, listPointers *destpt, sort_order Order)
    * \brief Procedura sortująca elementy listy po polu year.
    * Dla N elementów na liście, znajduje ona N razy minimum/maximum na liście "źrodła" przy uzyciu funkcji findExtremeByYear, a następnie dodaje go do listy "destynacji"
    * i usuwa z listy "źródłą". W ten sposób lista jest jakby "przepisywana" z sortowaniem.
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album, która jest listą "źródłą"
    * \param destpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album, która jest listą "destynacji"
    * \param Order wskazuje czy sortujemy rosnąco czy malejąco
*/
void sortAlbumsByYear(listPointers *listpt, listPointers *destpt, sort_order Order) {
    while(listpt->head) {
        //znajdujemy najstarszy album
        Album *temp = findExtremeByYear(listpt, Order);
        //dodajemy go do nowej listy
        insertToList(temp->id, temp->year, temp->name, temp->status, temp->listened, destpt, FRONT);
        //usuwamy go ze starej listy
        deleteIndicatedListElement(temp, listpt);
    }
    //przypisujemy zamieniamy tymczasowa liste na normalna
    listpt->head = destpt->head;
    listpt->tail = destpt->tail;
    destpt->head = destpt->tail = NULL;
}
/**
    * \fn Album * findExtremeByYear(listPointers *listpt, sort_order Order)
    * \brief Funkcja szukająca na podanej jej liście typu Album, elementu który jest najmniejszy/największy, sortując po polu year (czyli najwcześniej wydanego albumu).
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param Order wskazuje czy szukany element to minimum czy maximum
    * \return min wskaźnik na znaleziony element listy
*/
Album * findExtremeByYear(listPointers *listpt, sort_order Order) {
    Album *min = listpt->head;
    Album *q = min->next;
    if(Order == ASCENDING) {
        while(q) {
            if(q->year < min->year) {
                min = q;
            }
            q = q->next;
        }
    }
    else {
        while(q) {
            if(q->year > min->year) {
                min = q;
            }
            q = q->next;
        }
    }
    return min;
}
/**
    * \fn void sortAlbumsBySublistData(listPointers *listpt, sublistPointers *subpt, sublistPointers *temppt, int *sorted, const int size, sort_order Order)
    * \brief Procedura sortująca elementy listy typu Sublist po polu data, które jest łańcuchem znaków.
    * Sortuje ona przy uzyciu funkcji findExtremeInSublist, elementy na liście artystów/gatunków muzycznych i wyniki sortowania zapisuje w tablicy przekazanej przez parametr sorted.
    * Następnie dodaje element do listy "destynacji" (typu Sublist) i usuwa go z listy "źródła".
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param subpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist, która jest listą "źródłą"
    * \param temppt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist, która jest listą "destynacji"
    * \param sorted wskaźnik na tablicę do której zapisujemy wyniki sortowania w postaci numerów ID albumów
    * \param size ilość elementów w tablicy sorted
    * \param Order wskazuje czy sortowanie ma być rosnące czy malejące (zalecany typ danych sort_order)
*/
void sortAlbumsBySublistData(listPointers *listpt, sublistPointers *subpt, sublistPointers *temppt, int *sorted, const int size, sort_order Order) {
    int i = 0; //licznik komorek w sorted[n]
    while(subpt->head) {
        //znajdujemy minimum/maximum
        Sublist *temp = findExtremeInSublist(subpt, Order);
        //zapisujemy  w sorted
        if(!isInTab(sorted, temp->id, size)) {
            sorted[i] = temp->id;
            ++i;
        }
        //dodajemy do nowej listy
        insertToSublist(temp->id, temp->data, temppt);
        //usuwamy ze starej
        deleteSublistElement(temp, subpt);
    }
    subpt->head = temppt->head;
    subpt->tail = temppt->tail;
    temppt->head = temppt->tail = NULL;
}
/**
    * \fn Sublist * findExtremeInSublist(sublistPointers *listpt, sort_order Order)
    * \brief Funkcja szukająca na podanej jej liście typu Sublist, elementu który jest najmniejszy/największy, sortując po polu data.
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Sublist
    * \param Order wskazuje czy szukany element to minimum czy maximum
    * \return min wskaźnik na znaleziony element listy
*/
Sublist * findExtremeInSublist(sublistPointers *listpt, sort_order Order){
    Sublist *min = listpt->head;
    Sublist *q = min->next;
    if(Order == ASCENDING) {
        while(q) {
            int i = 0;
            while(q->data[i] == min->data[i] && q->data[i])
                ++i;
            if(q->data[i] < min->data[i])
                min = q;
            q = q->next;
        }
    }
    else {
        while(q) {
            int i = 0;
            while(q->data[i] == min->data[i] && q->data[i])
                ++i;
            if(q->data[i] > min->data[i])
                min = q;
            q = q->next;
        }
    }
    return min;
}
