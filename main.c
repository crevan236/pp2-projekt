#include "headers.h"

int main()
{
    //deklaracja listy albumow i albumu tymczasowego
    listPointers listPt = {NULL, NULL};
    //deklaracja listy artystow
    sublistPointers artistPt = {NULL, NULL};
    //delaracja listy gatunkow muzycznych
    sublistPointers genrePt = {NULL, NULL};

    //otwieramy plik z albumami
    FILE *f = fopen("albums.txt", "r");
    //zczytujemy i tworzymy plistę albumów
    if(maintainFileAndCreateList(f, &listPt))
        return 0;
    //otwieramy plik z artystami
    FILE *f2 = fopen("artists.txt", "r");
    //zczytujemy i tworzymy plistę artystów
    if(maintainFileAndCreateSublist(f2, &artistPt))
        return 0;
    //otwieramy plik z gatunkami
    FILE *f3 = fopen("genres.txt", "r");
    //zczytujemy i tworzymy plistę gatunków
    if(maintainFileAndCreateSublist(f3, &genrePt))
        return 0;
    //---
    //--------------------------
    //interakcja z użytkownikiem
    int k, l;
    do {
        unsigned int id = listPt.head -> id;
        printf("Wybierz co chcesz zrobic:\n 1.Wyswietl albumy\n 2.Dodaj nowy album\n 3.Usun album\n 4.Edytuj album\n 5.Wyszukaj album\n 0.Zakoncz\n");
        scanf("%d", &k);
        if(1 == k) {//wyświetlanie
            int order;
            ClrScr();
            printf("Jak wyswietlic albumy?\n1.Domyslnie\n2.Po nazwie\n3.Po roku wydania\n4.Po artyscie\n5.Po gatunku\n0.Powrot\n");
            scanf("%d", &l);
            if(1 == l) {
                printList(&listPt, &artistPt, &genrePt, ASCENDING);
            }
            else if(2 == l) {
                ClrScr();
                printf("Wyswietlic rosnaco/malejaco?\n1.rosnaco\n2.malejaco\n");
                scanf("%d", &order);
                --order; //zeby przyjmowal wartosci 0/1
                //tworzymy tymczasowy album
                listPointers temporaryPt = {NULL, NULL};
                //sortujemy
                sortAlbumsByName(&listPt, &temporaryPt, order);
                //wyświetlamy
                printList(&listPt, &artistPt, &genrePt, ASCENDING);
            }
            else if(3 == l) {
                ClrScr();
                printf("Wyswietlic rosnaco/malejaco?\n1.rosnaco\n2.malejaco\n");
                scanf("%d", &order);
                --order; //zeby przyjmowal wartosci 0/1
                //tworzymy tymczasowy album
                listPointers temporaryPt = {NULL, NULL};
                //sortujemy
                sortAlbumsByYear(&listPt, &temporaryPt, order);
                //wyświetlamy
                printList(&listPt, &artistPt, &genrePt, ASCENDING);
            }
            else if(4 == l) {
                ClrScr();
                printf("Wyswietlic rosnaco/malejaco?\n1.rosnaco\n2.malejaco\n");
                scanf("%d", &order);
                --order; //zeby przyjmowal wartosci 0/1
                int n = countSublistNodes(&artistPt);
                int sorted[n];
                resetTab(sorted, n);
                sublistPointers tempPt = {NULL, NULL};
                sortAlbumsBySublistData(&listPt, &artistPt, &tempPt, sorted, n, order);
                int i;
                Album *pt;
                for(i = 0; (sorted[i] == 0 || i < n); ++i) {
                    pt = findInList(sorted[i], &listPt);
                    printAlbum(pt, &artistPt, &genrePt);
                }
            }
            else if(5 == l) {
                ClrScr();
                printf("Wyswietlic rosnaco/malejaco?\n1.rosnaco\n2.malejaco\n");
                scanf("%d", &order);
                --order; //zeby przyjmowal wartosci 0/1
                int n = countSublistNodes(&genrePt);
                int sorted[n];
                resetTab(sorted, n);
                sublistPointers tempPt = {NULL, NULL};
                sortAlbumsBySublistData(&listPt, &genrePt, &tempPt, sorted, n, order);
                Album *pt;
                int i;
                for(i = 0; (sorted[i] == 0 || i < n); ++i) {
                    pt = findInList(sorted[i], &listPt);
                    printAlbum(pt, &artistPt, &genrePt);
                }
            }
            else {
                puts("Powrot...");
            }
            wait();
            ClrScr();
        }
        else if(2 == k) {//dodawanie
            unsigned int year, control, i;
            int listened, status;
            char name[75], AGname[70], sLStatus[4], scontrol[] = "t\n", *token, sign[] = "\t";

            //printf("Podaj ile albumow chcesz dodac na raz: ");
            //scanf(" %d", & control );
            /* dodawanie kilku wylaczone z powodu buga */
            control = 1;
            id++;
            for( i = 0; i < control; i++){
                printf("Podaj rok: ");
                scanf("%d", & year );//jeśli wpiszesz ( - ) to znaczy brak
                getchar();//zbiera \n
                printf("Podaj nazwe: ");
                fgets(name, 75, stdin);//jeśli wpiszesz ( - ) to znaczy brak
                strToUpper(name);
                printf("Podaj autora:\n(Jezeli kilku to oddzielaj ich tabulatorem)\n");
                fgets(AGname, 70, stdin);//jeśli wpiszesz ( - ) to znaczy brak (po znaku '\t' piszemy kolejnego artyste)
                strToUpper(AGname);
                token = strtok( AGname, sign );
                while( token != NULL ){
                    int size = strlen(token) + 2;
                    char temp[size];
                    strcpy(temp, token);
                    insertBCSN(temp, size);
                    insertToSublist(id, temp, &artistPt);
                    token = strtok( NULL, sign );
                }
                printf("Podaj gatunek:\n(Jezeli kilka to oddzielaj je tabulatorem)\n");
                fgets(AGname, 70, stdin);//jeśli wpiszesz ( - ) to znaczy brak(po znaku '\t' piszemy kolejne gatunki)
                strToUpper(AGname);
                token = strtok( AGname, sign );
                while( token != NULL ){
                    int size = strlen(token) + 2;
                    char temp[size];
                    strcpy(temp, token);
                    insertBCSN(temp, size);
                    insertToSublist(id, temp, &genrePt);
                    token = strtok( NULL, sign );
                }
                printf("Czy album zostal zakupiony? ");//t/n
                fgets(sLStatus, 4, stdin);
                if(strcmp(sLStatus, scontrol) == 0 || sLStatus[0] == '\n')
                    status=1;
                else
                    status=0;
                printf("Czy album zostal przesluchany? ");//t/n
                fgets(sLStatus, 4, stdin);
                if(strcmp(sLStatus, scontrol) == 0 || sLStatus[0] == '\n')
                    listened=1;
                else
                    listened=0;
                insertByOrder(id, year, name, status, listened, &listPt, 0);
                id++;
                printf("\n");
            }
            ClrScr();
        }
        else if(3 == k){//usuwanie
            int id;
            printf("Podaj ID albumu do usuniecia: ");
            scanf("%d", & id);
            Album *pt = findInList(id, &listPt);
            if(pt) {
                //usuwamy album
                deleteIndicatedListElement(pt, &listPt);
                //usuwamy artystów
                Sublist *Apt = artistPt.head;
                while(Apt){
                    if(Apt->id == id) {
                        deleteSublistElement(Apt, &artistPt);
                    }
                    Apt = Apt->next;
                }
                //usuwamy gatunki muzyczne
                Sublist *Gpt = genrePt.head;
                while(Gpt){
                    if(Gpt->id == id) {
                        deleteSublistElement(Gpt, &genrePt);
                    }
                    Gpt = Gpt->next;
                }
                printf("Album zostal usuniety.\n");
            }
            else {
                printf("Nie ma albumu o takim ID.\n");
            }
            wait();
            ClrScr();
        }
        else if(4 == k) {//edycja
            ClrScr();
            int id;
            printf("Podaj id albumu:\n");
            scanf("%d", &id);
            Album *pt = findInList(id, &listPt);
            if(pt) {
                printAlbum(pt, &artistPt, &genrePt);
                printf("Co chcesz edytowac:\n1.Nazwe\n2.Rok\n3.Artyste\n4.Gatunek\n5.Status\n6.Przesluchany\n7.Wszystkie pola\n");
                scanf("%d", & l);
                //edycja nazwy lub gdy edytujemy wszystko
                if(1 == l  || 7 == l) {
                    char name[75];
                    printf("Podaj nowa nazwe: ");
                    getchar();
                    fgets(name, 75, stdin);//jeśli wpiszesz ( - ) to znaczy brak
                    strToUpper(name);
                    strcpy(pt->name, name);
                }
                //edycja roku lub gdy edytujemy wszystko
                if(2 ==l || 7 == l){
                    int year;
                    printf("Podaj nowy rok: ");
                    scanf("%d", & year);
                    pt->year=year;
                }
                //edycja artysty lub gdy edytujemy wszystko
                if (3 == l || 7 == l){
                    int i, control;
                    char AGname[70];
                    Sublist *Apt = findInSublist(id, &artistPt);
                    ClrScr();
                    printf("Co chcesz zrobic: \n1.Edycja artysty\n2.Dodanie artysty\n3.Usuniecie artysty\n");
                    scanf("%d", & k);
                    //edycja artysty
                    if(1 == k){
                        i = printSublistElementsEdit(&artistPt, id);
                        if(2 != i){
                            printf("Podaj ktorego chcesz edytowac: ");
                            scanf("%d", & control);
                            i--;
                            while(i != control) {
                                i--;
                                Apt = Apt->next;
                            }
                        }
                        ClrScr();
                        printf("Podaj nowego artyste: ");
                        getchar();// pochłania \n
                        fgets(AGname, 70, stdin);//jeśli wpiszesz ( - ) to znaczy brak
                        strToUpper(AGname);
                        strcpy(Apt->data, AGname);
                    }
                    //dodanie artysty
                    else if(2 == k){
                        ClrScr();
                        printf("Podaj nowego artyste: ");
                        getchar();// pochłania \n
                        fgets(AGname, 70, stdin);//jeśli wpiszesz ( - ) to znaczy brak
                        strToUpper(AGname);
                        insertToSublistAfterIndicatedElement(id, AGname, &artistPt, Apt);
                    }
                    //usuniecie artysty
                    else if(3 == k){
                        i = printSublistElementsEdit(&artistPt, id);
                        if(2 != i){
                            printf("Podaj ktorego artyste chcesz usunac: ");
                            scanf("%d", & control);
                            i--;
                            while(i != control) {
                                i--;
                                Apt = Apt->next;
                            }
                        }
                        deleteSublistElement(Apt, &artistPt);
                    }
                }
                //edycja gatunku lub gdy edytujemy wszystko
                if(4 == l || 7 == l){
                    int i, control;
                    char AGname[70];
                    Sublist *Gpt = findInSublist(id, &genrePt);
                    ClrScr();
                    printf("Co chcesz zrobic: \n1.Edycja gatunku\n2.Dodanie gatunku\n3.Usuniecie gatunku\n");
                    scanf("%d", & k);
                    //edycja gatunku
                    if(1 == k){
                        i = printSublistElementsEdit(&genrePt, id);
                        if(2 != i){
                            printf("Podaj ktorego chcesz edytowac: ");
                            scanf("%d", & control);
                            i--;
                            while(i != control) {
                                i--;
                                Gpt = Gpt->next;
                            }
                        }
                        ClrScr();
                        printf("Podaj nowy Gatunek: ");
                        getchar();// pochłania \n
                        fgets(AGname, 70, stdin);//jeśli wpiszesz ( - ) to znaczy brak
                        strToUpper(AGname);
                        strcpy(Gpt->data, AGname);
                    }
                    //dodanie gatunku
                    else if(2 == k){
                        ClrScr();
                        printf("Podaj nowy gatunek: ");
                        getchar();// pochłania \n
                        fgets(AGname, 70, stdin);//jeśli wpiszesz ( - ) to znaczy brak (po znaku '\t' piszemy kolejnego artyste)
                        strToUpper(AGname);
                        insertToSublistAfterIndicatedElement(id, AGname, &genrePt, Gpt);
                    }
                    //usuniecie gatunku
                    else if(3 == k) {
                        i = printSublistElementsEdit(&genrePt, id);
                        if(2 != i){
                            printf("Podaj ktory gatunek chcesz usunac: ");
                            scanf("%d", & control);
                            i--;
                            while(i != control) {
                                i--;
                                Gpt = Gpt->next;
                            }
                        }
                        deleteSublistElement(Gpt, &artistPt);
                    }
                }
                //edycja statusu lub gdy edytujemy wszystko
                if(5 == l || 7 == l){
                    int status;
                    char sLStatus[4], scontrol[] = "tak";
                    printf("Czy album zostal zakupiony? ");//tak/nie
                    scanf(" %s", & sLStatus );
                    if(strcmp(sLStatus, scontrol) == 0)
                        status = 1;
                    else
                        status = 0;
                    pt->status = status;
                }
                //edycja przesluchane lub gdy edytujemy wszystko
                if(6 == l || 7 == l){
                    int listened;
                    char sLStatus[4], scontrol[] = "tak";
                    printf("Czy album zostal przesluchany? ");//tak/nie
                    scanf(" %s", & sLStatus );
                    if(strcmp(sLStatus, scontrol) == 0)
                        listened = 1;
                    else
                        listened = 0;
                    pt->listened = listened;
                }
                printf("Album zostal edytowany.\n");
            }
            else {
                printf("Nie ma albumu o takim ID.\n");
            }
            wait();
            ClrScr();
        }
        else if(5 == k) {//wyszukiwanie
            ClrScr();
            printf("Po jakim polu chcesz wyszukac?\n1.Nazwa\n2.ID\n3.Rok\n4.Wykonawca\n5.Gatunek\n6.Kupione\n7.Przesluchane\n0.Powrot\n");
            scanf("%d", &l);
            if(1 == l) {
                ClrScr();
                char name[75];
                printf("Podaj nazwe:\n");
                scanf("%d", &l);//To wczytujemy tylko dlatego, żeby nam fgets zadziałał potem
                fgets(name, 75, stdin);
                strToUpper(name);
                //DOPASOWANIE CALKOWITE
                Album *pt = findByName(name, &listPt);
                //DOPASOWANIE CZESCIOWE
                char *token = strtok(name, " ");
                char *ptc; //wskaznik na ostatni wyraz
                while(token != NULL) {
                    ptc = token;
                    token = strtok(NULL, " ");
                }
                //mamy ostatni wyraz
                //bierzemy jego pierwsze 3 litery
                char needle[4];
                int i;
                for(i = 0; i < 3; ++i) {
                    needle[i] = ptc[i];
                }
                needle[3] = '\0';
                //needle to teraz ciag ktorego bedziemy poszukiwac w innych ciagach
                int size = countListNodes(&listPt);
                int elements[size];
                memset(elements, 0, size*sizeof(elements[0])); //zerujemy tablice
                //szukamy needle w genres i zapisujemy id albumów do elements
                findNeedleInList(needle, &listPt, elements, size);
                //--
                if(pt)
                    printAlbum(pt, &artistPt, &genrePt);
                else {
                    printf("Nie ma takiego albumu.\n");
                }
                getchar();
                i = 0;
                if(elements[i]) {
                    printf("Dopasowania czesciowe:\n");
                    while(elements[i]) {
                        Album *pt = findInList(elements[i], &listPt);
                        printAlbum(pt, &artistPt, &genrePt);
                        ++i;
                    }
                }
                else {
                    printf("Brak dopasowan czesciowych.\n");
                }
                getchar();
                ClrScr();
            }
            else if(2 == l) {
                ClrScr();
                int id;
                printf("Podaj ID:\n");
                scanf("%d", &id);
                Album *pt = findInList(id, &listPt);
                if(pt)
                    printAlbum(pt, &artistPt, &genrePt);
                else {
                    printf("Nie ma takiego albumu.\n");
                }
                wait();
                ClrScr();
            }
            else if(3 == l) {
                ClrScr();
                int year;
                printf("Podaj rok:\n");
                scanf("%d", &year);
                findAndPrintByYear(year, &listPt, &artistPt, &genrePt);
                wait();
                ClrScr();
            }
            else if(4 == l) {
                ClrScr();
                char artist[30];
                printf("Podaj artyste:\n");
                getchar();
                fgets(artist, 30, stdin);
                strToUpper(artist);
                //bierzemy pierwszy wyraz i traktujemy go jako needle
                char *token = strtok(artist, " ");
                int n = strlen(token), i;
                char needle[n];
                strcpy(needle, token);
                needle[n-1] = '\0';
                //needle to ciag ktorego bedziemy szukac w artist
                int size = countListNodes(&listPt);
                int elements[size];
                memset(elements, 0, size*sizeof(elements[0])); //zerujemy tablice
                //szukamy needle w artists i zapisujemy id albumów do elements
                findNeedleInSublist(needle, &artistPt, elements, size);
                //wypisujemy albumy
                i = 0;
                if(elements[i]) {
                    while(elements[i]) {
                        Album *pt = findInList(elements[i], &listPt);
                        printAlbum(pt, &artistPt, &genrePt);
                        ++i;
                    }
                }
                else {
                    printf("Nie ma albumow wydanych przez tego artyste.\n");
                }
                getchar();
                ClrScr();
            }
            else if(5 == l) {
                ClrScr();
                char genre[30];
                printf("Podaj gatunek:\n");
                getchar();
                fgets(genre, 30, stdin);
                strToUpper(genre);
                char *token = strtok(genre, " ");
                char *ptc; //wskaznik na ostatni wyraz
                while(token != NULL) {
                    ptc = token;
                    token = strtok(NULL, " ");
                }
                //mamy ostatni wyraz
                //bierzemy jego pierwsze 3 litery
                char needle[4];
                int i;
                for(i = 0; i < 3; ++i) {
                    needle[i] = ptc[i];
                }
                needle[3] = '\0';
                //needle to teraz ciag ktorego bedziemy poszukiwac w innych ciagach
                int size = countListNodes(&listPt);
                int elements[size];
                memset(elements, 0, size*sizeof(elements[0])); //zerujemy tablice
                //szukamy needle w genres i zapisujemy id albumów do elements
                findNeedleInSublist(needle, &genrePt, elements, size);
                //wypisujemy albumy
                i = 0;
                if(elements[i]) {
                    while(elements[i]) {
                        Album *pt = findInList(elements[i], &listPt);
                        printAlbum(pt, &artistPt, &genrePt);
                        ++i;
                    }
                }
                else {
                    printf("Nie ma albumow z tego gatunku.\n");
                }
                getchar();
                ClrScr();
            }
            else if(6 == l) {
                ClrScr();
                printf("Wyswietlic wszystkie 1.kupione czy 2. nie kupione?");
                scanf("%d", &l);
                if(l != 1) l = 0;
                findAndPrintByStatus(l, &listPt, &artistPt, &genrePt);
                wait();
                ClrScr();
            }
            else if(7 == l) {
                ClrScr();
                printf("Wyswietlic wszystkie 1.przesluchane czy 2. nie przesluchane?");
                scanf("%d", &l);
                if(l != 1) l = 0;
                findAndPrintByListened(l, &listPt, &artistPt, &genrePt);
                wait();
                ClrScr();
            }
            else {
                ClrScr();
            }
        }
        else {//koniec
            ClrScr();
            printf("Papatki <3 !!!");
        }
    } while(k != 0);
    //---
    //zapisujemy wszystkie albumy (zawartość listy) do pliku i kończymy
    f = fopen("albums.txt", "w");
    if(saveListAndCloseFile(f, &listPt))
        return 0;
    //zapisujemy wszystkich artystów do pliku i kończymy
    f2 = fopen("artists.txt", "w");
    if(saveSublistAndCloseFile(f2, &artistPt))
        return 0;
    //zapisujemy wszystkie gatunki do pliku i kończymy
    f3 = fopen("genres.txt", "w");
    if(saveSublistAndCloseFile(f3, &genrePt))
        return 0;
    //usuwamy listy
    deleteWholeList(&listPt);
    deleteWholeSublist(&artistPt);
    deleteWholeSublist(&genrePt);

    return 0;
}
