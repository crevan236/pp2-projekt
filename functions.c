#include "headers.h"

//wstawia element na listę (na końcu lub początku)
void insertToList(int data, listPointers *listpt, direction d) {
    Album *q = (Album *)malloc(sizeof(Album));
    //data
    q->id = id;
    q->year = year;
    q->status = status;
    q->listened = listened;
    //q->name = coś to trzeba jakieś kopiowanie stringa
    //pointers
    if(listpt->head == NULL) {
        listpt->head = q;
        listpt->tail = q;
        q->prev = q->next = NULL;
    }
    else if(d == FRONT) {
        q->prev = NULL;
        q->next = listpt->head;
        (listpt->head)->prev = q;
        listpt->head = q;
    }
    else {
        q->next = NULL;
        q->prev = listpt->tail;
        (listpt->tail)->next = q;
        listpt->tail = q;
    }
}
//wyświetla listę (od początku bądź od końca)
void printList(listPointers *listpt, direction d) {
    if(d == FRONT) {
        Album *q = listpt->head;
        while(q) {
            printf("%s\n%d\n%d\n%b\n%b\n", q->name, q->id, q->year, q->status, q->listened);
            q = q->next;
        }
        printf("\n");
    }
    else {
        Album *q = listpt->tail;
        while(q) {
            printf("%s\n%d\n%d\n%b\n%b\n", q->name, q->id, q->year, q->status, q->listened);
            q = q->prev;
        }
        printf("\n");
    }
}
//usuwa element listy (z początku bądź końca)
void deleteListElement(listPointers *listpt, direction d) {
    if(d == FRONT) {
        if(listpt->head != NULL) {
            Album *q = listpt->head;
            if(q->next != NULL)
                q->next->prev = NULL;
            listpt->head = q->next;
            free(q);
        }
    }
    else {
        if(listpt->tail != NULL) {
            Album *q = listpt->tail;
            if(q->prev != NULL)
                q->prev->next = NULL;
            listpt->tail = q->prev;
            free(q);
        }
    }
}
//usuwa całą listę (bez wartowników)
void deleteWholeList(listPointers *listpt) {
    Album *q  = listpt->head;
    while(q) {
        deleteListElement(listpt, FRONT);
        q  = listpt->head;
    }
    listpt->head = listpt->tail = NULL;
}
//szuka elementu listy zawierającego x w polu value
Album * findInList(unsigned int id, listPointers *listpt) {
    Album *q = listpt->head;
    while(q) {
        if(q->id == id) {
            return q;
        }
        q = q->next;
    }
    return q;
}
//wstawia element do listy w porządku rosnącym lub malejącym
void insertByOrder(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, sort_order d) {
    Album *q = (listNode *)malloc(sizeof(listNode));
    Album *temp = listpt->head;
    //data
    q->id = id;
    q->year = year;
    q->status = status;
    q->listened = listened;
    //q->name = coś to trzeba jakieś kopiowanie stringa
    //pointers
    //jeżeli lista jest pusta
    if(listpt->head == NULL) {
        listpt->head = q;
        listpt->tail = q;
        q->prev = q->next = NULL;
    }
    else {
        //ustalamy porządek oraz szukamy miejsca do wstawienia
        if(d == ASCENDING) {
            while((temp != NULL) && (q->value <= temp->value)) {
                temp = temp->next;
            }
        }
        else {
            while((temp != NULL) && (q->value >= temp->value)) {
                temp = temp->next;
            }
        }
        //sprawdzamy gdzie wstawiamy (początek, koniec czy środek) i
        //koniec
        if(temp == NULL) {
            q->next = NULL;
            q->prev = listpt->tail;
            (listpt->tail)->next = q;
            listpt->tail = q;
        }
        //początek
        else if(temp->prev == NULL) {
            q->next = temp;
            q->prev = NULL;
            listpt->head = q;
            temp->prev = q;
        }
        else {
            q->next = temp;
            q->prev = temp->prev;
            temp->prev->next = q;
            temp->prev = q;
        }
    }
}
//zwraca true dla pustej listy
bool isEmpty(listPointers *listpt) {
    if(listpt->head == NULL) {
        return true;
    }
    else {
        return false;
    }
}
//liczy ile elementów jest na liście
int countListNodes(listPointers *listpt) {
    int counter = 0;
    Album *q = listpt->head;
    while(q) {
        ++counter;
        q = q->next;
    }
    return counter;
}
//odwraca listę, czyli zamienia wskaźniki tak, że head to tail a tail to head
void reverseList(listPointers *listpt) {
    Album *q = listpt->head;
    Album *temp = listpt->head;
    while(q) {
        temp = q->next;
        q->next = q->prev;
        q->prev = temp;
        q = temp;
    }
    temp = listpt->head;
    listpt->head = listpt->tail;
    listpt->tail = temp;
}
