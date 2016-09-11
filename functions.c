#include "headers.h"

/**
    @file functions.c
    \brief Przechowuje definicje funkcji do obsługi listy typu Album oraz funkcji ogólnego uzytku.
*/

//PLIKI

//zapisanie listy i zamkniecie pliku
/**
    * \fn int saveListAndCloseFile(FILE *f, listPointers *listpt)
    * \brief Funkcja zapisująca listę typu Album do pliku i zamyka tenże plik.
    * \param f wskaźnik na plik.
    * \param listpt wskaźnik na strukturę przechowującą wskaźniki na początek i koniec listy typu Album.
    * \return -1 w przypadku błędu zamknięcia pliku.
    * \return 0 w przypadku powodzenia.
*/
int saveListAndCloseFile(FILE *f, listPointers *listpt) {
    if(NULL == f) {
        perror("Blad otwarcia pliku albums.txt");
        return -1;
    }
    //zapisujemy liste do pliku
    Album *temp = listpt->tail;
    while(temp != NULL) {
        saveAlbumInFile(f, temp);
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
    * \fn int maintainFileAndCreateList(FILE *f, listPointers *listpt)
    * \brief Funkcja otwiera plik zawierający listę typu Album, i zapisuje dane z pliku do listy, a następnie zamyka plik.
    * \param f wskaźnik na plik.
    * \param listpt wskaźnik na strukturę przechowującą wskaźniki na początek i koniec listy typu Album (do której zapisujemy dane z pliku).
    * \return -1 w przypadku błędu zamknięcia pliku.
    * \return 0 w przypadku powodzenia.
*/
int maintainFileAndCreateList(FILE *f, listPointers *listpt) {
    Album *temp = (Album *)malloc(sizeof(Album));
    //---
    if(NULL == f) {
        perror("Blad otwarcia pliku albums.txt");
        return -1;
    }
    //pobieramy albumy i tworzymy ich listę
    while(!feof(f)) {
        readAlbumFromFile(f, temp);
        insertByOrder(temp->id, temp->year, temp->name, temp->status, temp->listened, listpt, ASCENDING);
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
    * \fn void readAlbumFromFile(FILE *f, Album *q)
    * \brief Procedura odczytująca zawartość jednego elementu listy typu Album z pliku.
    * \param f wskaźnik na plik.
    * \param q wskaźnik na element listy typu Album do którego zapisujemy dane z pliku.
*/
void readAlbumFromFile(FILE *f, Album *q) {
    if(f) {
        fgets(q->name, 75, f);
        fscanf(f, "%d", &(q->id));
        fscanf(f, "%d", &(q->year));
        fscanf(f, "%d", (int *)&(q->status));
        fscanf(f, "%d", (int *)&(q->listened));
        //---
        int a;
        //to zczytywanie tylko dlatego żeby wszystko poprawnie działało
        fscanf(f, "%d", &a);
    }
}
//zapisuje dane z elementu listy do pliku
/**
    * \fn void saveAlbumInFile(FILE *f, Album *q)
    * \brief Procedura zapisująca zawartość jednego elementu listy typu Album do pliku.
    * \param f wskaźnik na plik.
    * \param q wskaźnik na element listy typu Album z którego zapisujemy dane do pliku.
*/
void saveAlbumInFile(FILE *f, Album *q) {
    if(f) {
        fprintf(f, "%s", q->name);
        fprintf(f, "%d\n", q->id);
        fprintf(f, "%d\n", q->year);
        fprintf(f, "%d\n", q->status);
        fprintf(f, "%d\n", q->listened);
    }
}

//LISTY
//wstawia element na listę (na końcu lub początku)
/**
    * \fn void insertToList(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, direction d)
    * \brief Procedura dodająca kolejny element do listy, z przodu bądź z tyłu (zależnie od parametru direction
    * \param id numer id albumu który dodajemy do listy
    * \param year rok wydania albumu
    * \param name wskaźnik na łańcuch znaków przechowujący nazwę albumu
    * \param status informacja czy album został kupiony
    * \param listened informacja czy album został przesłuchany
    * \param listpt wskaźnik na strukturę zawierającą wskaźniki na początek i koniec listy do której dodajemy element
    * \param d parametr decydujący o tym czy element dodajemy na końcu czy na początku listy, zalecane stosowanie typu direction (FRONT/BACK)
*/
void insertToList(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, direction d) {
    Album *q = (Album *)malloc(sizeof(Album));
    //data
    q->id = id;
    q->year = year;
    q->status = status;
    q->listened = listened;
    strcpy(q->name, name);
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
/**
    * \fn void printList(listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept, direction d)
    * \brief Procedura wyświetlająca całą listę typu Album, czyli bazę danych albumów muzycznych
    * \param listpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Album przechowującej albumy muzyczne
    * \param artistpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej artystów przypisanych do danego albumu
    * \param genrept wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej gatunki muzyczne przypisane do danego albumu
    * \param d parametr decydujący o tym czy listę wyświetlamy od początku czy od końca, zalecane stosowanie typu direction (FRONT/BACK)
*/
void printList(listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept, direction d) {
    if(d == FRONT) {
        Album *q = listpt->head;
        while(q) {
            printAlbum(q, artistpt, genrept);
            q = q->next;
        }
    }
    else {
        Album *q = listpt->tail;
        while(q) {
            printAlbum(q, artistpt, genrept);
            q = q->prev;
        }
        printf("\n");
    }
}
//wyświetla jeden album
/**
    * \fn void printAlbum(Album *q, sublistPointers *artistpt, sublistPointers *genrept)
    * \brief Procedura wyświetlająca jeden element listy typu Album, czyli jeden album muzyczny.
    * \param q wskaźnik na element listy typu Album
    * \param artistpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej artystów przypisanych do danego albumu
    * \param genrept wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej gatunki muzyczne przypisane do danego albumu
*/
void printAlbum(Album *q, sublistPointers *artistpt, sublistPointers *genrept) {
    if(q) {
        printf("-------------------------------\n");
        printf("Nazwa albumu: %sID: %d\n", q->name, q->id);
        if(0==q->year) printf("Rok wydania: -\n");
        else printf("Rok wydania: %d\n",q->year);
        printf("Artysci:\n ");
        printSublistElements(artistpt, q->id);
        printf("Gatunek muzyczny:\n");
        printSublistElements(genrept, q->id);
        printf("Stan: %s\nPrzesluchany: %s\n", (q->status == 1) ? "kupiony" : "nie kupiony", (q->listened == 1) ? "tak" : "nie");
        printf("-------------------------------\n");
    }
}
//usuwa element listy (z początku bądź końca)
/**
    * \fn void deleteListElement(listPointers *listpt, direction d)
    * \brief Procedura usuwająca jeden element z listy typu Album.
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album (z której usuwamy element)
    * \param d parametr decydujący o tym czy element usuwamy z końca czy z początku listy, zalecane stosowanie typu direction (FRONT/BACK)
*/
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
//usuwa element listy przekazany przez wskaźnik
/**
    * \fn void deleteIndicatedListElement(Album *q, listPointers *listpt)
    * \brief Procedura usuwająca jeden element z listy typu Album, podany przez wskaźnik
    * \param q wskaźnik na element listy które chcemy usunąć
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album (z której usuwamy element)
*/
void deleteIndicatedListElement(Album *q, listPointers *listpt) {
    if(q) {
        if(NULL == q->next && NULL == q->prev) {
            listpt->tail = listpt->head = NULL;
        }
        else if(NULL == q->next) {
            listpt->tail = q->prev;
            q->prev->next = NULL;
        }
        else if(NULL == q->prev) {
            listpt->head = q->next;
            q->next->prev = NULL;
        }
        else {
            q->next->prev = q->prev;
            q->prev->next = q->next;
        }
        free(q);
    }
}
//usuwa całą listę (bez wartowników)
/**
    * \fn void deleteWholeList(listPointers *listpt)
    * \brief Procedura usuwająca całą listę typu Album
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album (którą usuwamy)
*/
void deleteWholeList(listPointers *listpt) {
    Album *q  = listpt->head;
    while(q) {
        deleteListElement(listpt, FRONT);
        q  = listpt->head;
    }
    listpt->head = listpt->tail = NULL;
}
//wstawia element do listy w porządku rosnącym lub malejącym
/**
    * \fn void insertByOrder(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, sort_order d)
    * \brief Procedura dodająca kolejny element do listy, automatycznie sortując przy tym listę po polu "id"
    * \param id numer id albumu który dodajemy do listy
    * \param year rok wydania albumu
    * \param name wskaźnik na łańcuch znaków przechowujący nazwę albumu
    * \param status informacja czy album został kupiony
    * \param listened informacja czy album został przesłuchany
    * \param listpt wskaźnik na strukturę zawierającą wskaźniki na początek i koniec listy do której dodajemy element
    * \param d parametr decydujący o tym czy liste sortujemy rosnąco czy malejąco, zalecane stosowanie typu sort_order (ASCENDING/DESCENDING)
*/
void insertByOrder(unsigned int id, unsigned int year, char *name, bool status, bool listened, listPointers *listpt, sort_order d) {
    Album *q = (Album *)malloc(sizeof(Album));
    Album *temp = listpt->head;
    //data
    q->id = id;
    q->year = year;
    q->status = status;
    q->listened = listened;
    strcpy(q->name, name);

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
            while((temp != NULL) && (q->id <= temp->id)) {
                temp = temp->next;
            }
        }
        else {
            while((temp != NULL) && (q->id >= temp->id)) {
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
//liczy ile elementów jest na liście
/**
    * \fn int countListNodes(listPointers *listpt)
    * \brief Funkcja licząca ile elementów znajduje się aktualnie na liście typu Album
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \return counter ilość elementów na liście
*/
int countListNodes(listPointers *listpt) {
    int counter = 0;
    Album *q = listpt->head;
    while(q) {
        ++counter;
        q = q->next;
    }
    return counter;
}
// WYSZUKIWANIE
//szuka elementu listy zawierającego id w polu id
/**
    * \fn Album * findInList(unsigned int id, listPointers *listpt)
    * \brief Funkcja szukająca na liście typu album, elementu o polu id równemu parametrowi id
    * \param id numer ID szukanego albumu
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \return q wskaźnik na znaleziony element w przypadku powodzenia
    * \return NULL gdy elementu o podanym id nie ma na liście
*/
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
//szuka elementu listy o podanej wartości pola name
/**
    * \fn Album * findByName(char *name, listPointers *listpt)
    * \brief Funkcja szukająca na liście typu album, elementu o polu name równemu parametrowi name
    * \param name wskaźnik na łąńcuch znaków bedący nazwą szukanego albumu
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \return q wskaźnik na znaleziony element w przypadku powodzenia
    * \return NULL gdy elementu o podanej nazwie nie ma na liście
*/
Album * findByName(char *name, listPointers *listpt) {
    Album *q = listpt->head;
    while(q) {
        if(strcmp(name, q->name) == 0) {
            return q;
        }
        q = q->next;
    }
    return q;
}
//szuka i drukuje albumy z danego roku
/**
    * \fn void findAndPrintByYear(unsigned int year, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept)
    * \brief Procedura szukająca na liście typu album, elementów o polu year równych parametrowi year i wypisujaca te elementy
    * \param year rok wydania albumów które chcemy znaleźć
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param artistpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej artystów przypisanych do danego albumu
    * \param genrept wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej gatunki muzyczne przypisane do danego albumu
*/
void findAndPrintByYear(unsigned int year, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept) {
    Album *q = listpt->head;
    int k = 0; //oznacza czy zostały wyswietlone jakies albumy
    while(q) {
        if(q->year == year) {
            printAlbum(q, artistpt, genrept);
            ++k;
        }
        q = q->next;
    }
    if(!k) {
        printf("Nie ma takiego albumu.");
    }
}
//szuka i drukuje albumy kupione/nie kupione
/**
    * \fn void findAndPrintByStatus(int status, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept)
    * \brief Procedura szukająca na liście typu album, elementów o polu status równych parametrowi status i wypisujaca te elementy
    * \param status (0 lub 1) określa czy szukamy albumów kupionych czy nie kupionych
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param artistpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej artystów przypisanych do danego albumu
    * \param genrept wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej gatunki muzyczne przypisane do danego albumu
*/
void findAndPrintByStatus(int status, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept) {
    Album *q = listpt->head;
    int k = 0; //oznacza czy zostały wyswietlone jakies albumy
    while(q) {
        if(q->status == status) {
            printAlbum(q, artistpt, genrept);
            ++k;
        }
        q = q->next;
    }
    if(!k) {
        printf("Nie ma takiego albumu.");
    }
}
//szuka i drukuje albumy przesłuchane/nie przesłuchane
/**
    * \fn void findAndPrintByListened(int listened, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept)
    * \brief Procedura szukająca na liście typu album, elementów o polu listened równych parametrowi listened i wypisujaca te elementy
    * \param listened (0 lub 1) określa czy szukamy albumów przesłuchanych czy nie przesłuchanych
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param artistpt wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej artystów przypisanych do danego albumu
    * \param genrept wskaźnik na strukturę przechowjącą wskaźniki na początek i koniec listy typu Sublist przechowującej gatunki muzyczne przypisane do danego albumu
*/
void findAndPrintByListened(int listened, listPointers *listpt, sublistPointers *artistpt, sublistPointers *genrept) {
    Album *q = listpt->head;
    int k = 0; //oznacza czy zostały wyswietlone jakies albumy
    while(q) {
        if(q->listened == listened) {
            printAlbum(q, artistpt, genrept);
            ++k;
        }
        q = q->next;
    }
    if(!k) {
        printf("Nie ma takiego albumu.");
    }
}
//czyszczenie ekranu
/**
    * \fn void ClrScr()
    * \brief Procedura wywołująca polecenie systemowe czyszczące ekran konsolli
*/
void ClrScr(){
  system("cls");
}
//czekanie na znak
/**
    * \fn void wait()
    * \brief Procedura wywołująca dwukrotnie funkcje getchar(), służy do czekania na wprowadzenie znaku od uzytkownika, zanim program wyczyści ekran konsoli
*/
void wait() {
    getchar();
    getchar();
}
//sprawdza czy liczba znajduje się w tabeli
/**
    * \fn bool isInTab(int *tab, int x, const int size)
    * \brief Funkcja sprawdzająca czy parametr x znajduje się w tablicy
    * \param tab wskaźnik na tablicę w której szukamy
    * \param x wartość której szukamy
    * \param size ilość elementów tablicy
    * \return true gdy wartość x znajduje się w tablicy
    * \return false gdy wartość x nie znajduje się w tablicy
*/
bool isInTab(int *tab, int x, const int size) {
    int i;
    for(i = 0; i < size; ++i) {
        if(tab[i] == x)
            return true;
    }
    return false;
}
//zeruje tablicę
/**
    * \fn void resetTab(int *tab, const int size)
    * \brief Procedura wypełniająca tablicę zerami
    * \param tab wskaźnik na tablicę w której szukamy
    * \param size ilość elementów tablicy
*/
void resetTab(int *tab, const int size) {
    int i;
    for(i = 0; i < size; ++i) {
        tab[i] = 0;
    }
}
//sprawdza czy na koncu lancucha jest \n
/**
    * \fn bool isBCSN(char *str, const int size)
    * \brief Funkcja sprawdzająca czy w podanym łańcuchu znaków, znajduje się znak "\n"
    * \param str wskaźnik na łańcuch w którym szukamy
    * \param size ilość elementów łańcucha
    * \return true gdy "\n" znajduje się w łańcuchu
    * \return false gdy "\n" nie znajduje się w łańcuchu
*/
bool isBCSN(char *str, const int size) {
    int i;
    for(i = 0; i < size; ++i) {
        if(str[i] == '\n')
            return true;
    }
    return false;
}
//jeżeli w lancuchu nie ma \n to wstawia
/**
    * \fn void insertBCSN(char *str, const int size)
    * \brief Procedura wstawiająca znak "\n" do łańcucha znaków, w przypadku gdy go tam nie ma, oraz znak końca łąńcucha zaraz za znakiem "\n"
    * \param str wskaźnik na łańcuch w którym szukamy
    * \param size ilość elementów łańcucha
*/
void insertBCSN(char *str, const int size) {
    if(!isBCSN(str, size)){
        str[size-2] = '\n';
        str[size-1] = '\0';
    }
}
//zamienia cały string na duże
/**
    * \fn void strToUpper(char *str)
    * \brief Procedura zamieniająca wszystkie litery w łańcuchu znaków na wielkie
    * \param str wskaźnik na łańcuch w którym szukamy
*/
void strToUpper(char *str) {
    int i = 0;
    while(str[i]) {
        str[i] = toupper(str[i]);
        ++i;
    }
}
/**
    * \fn void findNeedleInList(char *needle, listPointers *listpt, int *elements, const int size)
    * \brief Funkcja szukająca na liście typu Album, fragmentów łańcucha (needle) w łańcuchu będącym zawartością pola name.
    * \param needle wskaźnik na łańcuch znaków (część wiekszego łańcucha), którego poszukujemy w innych łańcuchach
    * \param listpt wskaźnik na strukture przechowującą wskaźniki na początek i koniec listy typu Album
    * \param elements wskaźnik na tablicę w której zapisujemy indeksy znalezionych elementów
    * \param size ilość elementów tablicy elements
*/
void findNeedleInList(char *needle, listPointers *listpt, int *elements, const int size) {
    Album *q = listpt->head;
    int i = 0;
    while(q) {
        if(strstr(q->name, needle)) {
            if(!isInTab(elements, q->id, size)){
                elements[i] = q->id;
                ++i;
            }
        }
        q = q->next;
    }
}
