#include <iostream>
#include <cstring>
using namespace std;
struct Rezervare {
    int id;
    char numeClient[50];
    char tipCamera[20];
    int nopti;
    float pretTotal;
};
int main() {
    int capacitate = 10, numarRezervari = 0;
    Rezervare* rezervari = new Rezervare[capacitate];
    while (true) {
        cout << "\n1. Adauga rezervare";
        cout << "\n2. Afiseaza rezervarile";
        cout << "\n3. Cauta rezervare dupa ID";
        cout << "\n4. Sterge rezervare";
        cout << "\n5. Sorteaza dupa pret";
        cout << "\n6. Salveaza in fisier";
        cout << "\n7. Incarca din fisier";
        cout << "\n0. Iesire";
        cout << "\nAlege o optiune: ";

        int optiune;
        cin >> optiune;
        if (optiune == 1) { // Adăugare rezervare
            if (numarRezervari >= capacitate) {
                capacitate *= 2;
                Rezervare* temp = new Rezervare[capacitate];
                for (int i = 0; i < numarRezervari; i++) {
                    temp[i] = rezervari[i];
                }
                delete[] rezervari;
                rezervari = temp;
            }
            cout << "ID: ";
            cin >> rezervari[numarRezervari].id;
            cout << "Nume client: ";
            cin.ignore();
            cin.getline(rezervari[numarRezervari].numeClient, 50);
            cout << "Tip cameră: ";
            cin.getline(rezervari[numarRezervari].tipCamera, 20);
            cout << "Număr de nopți: ";
            cin >> rezervari[numarRezervari].nopti;
            cout << "Preț total: ";
            cin >> rezervari[numarRezervari].pretTotal;
            numarRezervari++;
        }
        else if (optiune == 2) {
            // Afișare rezervări
            for (int i = 0; i < numarRezervari; i++) {
                cout << rezervari[i].id << " | " << rezervari[i].numeClient
                << " | " << rezervari[i].tipCamera << " | "
                << rezervari[i].nopti << " nopți | "
                << rezervari[i].pretTotal << " lei\n";
            }
        }
        else if (optiune == 3) {
            // Căutare după ID
            int idCautat;
            cout << "ID căutat: ";
            cin >> idCautat;
            bool gasit = false;
            for (int i = 0; i < numarRezervari; i++) {
                if (rezervari[i].id == idCautat) {
                    cout << "Rezervare găsită: " << rezervari[i].numeClient << " - "
                    << rezervari[i].tipCamera << " (" << rezervari[i].nopti
                    << " nopți, " << rezervari[i].pretTotal << " lei)\n";
                    gasit = true;
                    break;
                }
            }
            if (!gasit) cout << "Rezervare inexistentă!\n";
        }
        else if (optiune == 4) {
            // Ștergere rezervare
            int idSters;
            cout << "ID rezervare de șters: ";
            cin >> idSters;
            int indexSters = -1;
            for (int i = 0; i < numarRezervari; i++) {
                if (rezervari[i].id == idSters) {
                    indexSters = i;
                    break;
                }
            }
            if (indexSters != -1) {
                for (int i = indexSters; i < numarRezervari - 1; i++) {
                    rezervari[i] = rezervari[i + 1];
                }
                numarRezervari--;
                cout << "Rezervare ștearsă!\n";
            } else {
                cout << "Rezervare inexistentă!\n";
            }
        }

        else if (optiune == 5) { // Sortare după preț
            for (int i = 0; i < numarRezervari - 1; i++) {
                for (int j = i + 1; j < numarRezervari; j++) {
                    if (rezervari[i].pretTotal > rezervari[j].pretTotal) {
                        swap(rezervari[i], rezervari[j]);
                    }
                }
            }
            cout << "Sortare realizată!\n";
        }
        else if (optiune == 6) {
            // Salvare în fișier
            FILE* fisier = fopen("rezervari.txt", "w");
            if (fisier) {
                for (int i = 0; i < numarRezervari; i++) {
                    fprintf(fisier, "%d,%s,%s,%d,%.2f\n", rezervari[i].id,
                    rezervari[i].numeClient,
                    rezervari[i].tipCamera, rezervari[i].nopti,
                    rezervari[i].pretTotal);
                }
                fclose(fisier);
                cout << "Rezervările au fost salvate în fișier.\n";
            } else {
                cout << "Eroare la deschiderea fișierului!\n";
            }
        }
        else if (optiune == 7) { // Încărcare din fișier
            FILE* fisier = fopen("rezervari.txt", "r");
            if (fisier) {
                numarRezervari = 0;
                while (fscanf(fisier, "%d,%49[^,],%19[^,],%d,%f\n",
                &rezervari[numarRezervari].id,
                rezervari[numarRezervari].numeClient,
                rezervari[numarRezervari].tipCamera,
                &rezervari[numarRezervari].nopti,
                &rezervari[numarRezervari].pretTotal) == 5) {
                    numarRezervari++;
                    if (numarRezervari >= capacitate) {
                        capacitate *= 2;
                        Rezervare* temp = new Rezervare[capacitate];
                        for (int i = 0; i < numarRezervari; i++) {
                            temp[i] = rezervari[i];
                        }
                        delete[] rezervari;
                        rezervari = temp;
                    }
                }
                fclose(fisier);
                cout << "Rezervările au fost încărcate din fișier.\n";
            } else {
                cout << "Eroare la deschiderea fișierului!\n";
            }
        }
        else if (optiune == 0) { // Ieșire
            break;
        }
        else {
            cout << "Opțiune invalidă!\n";
        }
    }
    delete[] rezervari;
    return 0;
}