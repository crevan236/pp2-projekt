#include "headers.h"


int main()
{
    //Pobieramy albumy
    FILE *f = fopen("albums-database.txt", "r");
    if(NULL == f) {
        perror("Błąd otwarcia pliku albums-database.txt");
        return 0;
    }
    //tworzymy listę
    //zamykamy plik
    if(fclose(f)) {
        perror("Błąd zamknięcia pliku albums-database.txt");
        return 0;
    }
    //interakcja z użytkownikiem
    do {
        printf("Wybierz co chcesz zrobić:\n 1.Wyświetl albumy\n 2.Dodaj nowy album\n 3.Usuń album\n 4.Edytuj album\n 5.Wyszukaj album\n 0.Zakończ\n");
        scanf("%d", &k);
        if(1 == k) {
        }
        else if(2 == k) {
        }
        else if(3 == k) {
        }
        else if(4 == k) {
        }
        else if(5 == k) {
        }
        else {
            printf("Papatki <3 !!!");
        }
    } while(k != 0);
    //zapisujemy wszystkie albumy (zawartość listy) do pliku i kończymy
    f = fopen("albums-out.txt", "w");
    if(NULL == f) {
        perror("Błąd otwarcia pliku albums-database.txt");
        return 0;
    }
    if(fclose(f)) {
        perror("Błąd zamknięcia pliku albums-database.txt");
        return 0;
    }

    return 0;
}
