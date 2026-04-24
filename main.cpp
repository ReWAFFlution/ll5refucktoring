#include <iostream>
#include <fstream>

using namespace std;

struct Rezervare
{
    int id;
    char numeClient[30]; // Ajnehaf Deslamutarian
    char tipCamera[10]; // Mic / Medium / Lux ??
    int nopti;
    float pretTotal;
};

void adaugaRezervare(Rezervare rezervari[], int &numarRezervari, int capacitate)
{
    if (numarRezervari >= capacitate) {
        cout << "Capacitate maxima atinsa!\n";
        return;
    }
    cout << "ID: "; cin >> rezervari[numarRezervari].id;
    cout << "Nume client: "; cin.ignore(); cin.getline(rezervari[numarRezervari].numeClient, 50);
    cout << "Tip camera: "; cin.getline(rezervari[numarRezervari].tipCamera, 20);
    cout << "Numar nopti: "; cin >> rezervari[numarRezervari].nopti;
    cout << "Pret total: "; cin >> rezervari[numarRezervari].pretTotal;
    numarRezervari++;
}

void afiseazaRezervari(Rezervare rezervari[], int numarRezervari)
{
    for (int i = 0; i < numarRezervari; i++) {
        cout << rezervari[i].id << " | " << rezervari[i].numeClient
             << " | " << rezervari[i].tipCamera << " | "
             << rezervari[i].nopti << " nopti | "
             << rezervari[i].pretTotal << " lei\n";
    }
}

void cautaRezervare(Rezervare rezervari[], int numarRezervari) // No work wout case 7
{
    int id; cout << "ID cautat: "; cin >> id;
    bool gasit = false;
    for (int i = 0; i < numarRezervari; i++) {
        if (rezervari[i].id == id) {
            cout << "Gasit: " << rezervari[i].numeClient << " - "
                 << rezervari[i].tipCamera << " (" << rezervari[i].nopti
                 << " nopti, " << rezervari[i].pretTotal << " lei)\n";
            gasit = true;
        }
    }
    if (!gasit) cout << "Rezervare nevalida!\n";
}

void stergeRezervare(Rezervare rezervari[], int &numarRezervari)
{
    int id; cout << "ID de sters: "; cin >> id;
    int index = -1;
    for (int i = 0; i < numarRezervari; i++) {
        if (rezervari[i].id == id) { index = i; break; }
    }
    if (index != -1) {
        for (int i = index; i < numarRezervari - 1; i++) {
            rezervari[i] = rezervari[i + 1];
        }
        numarRezervari--;
        cout << "Rezervare stearsa!\n";
    } else cout << "Rezervare nevalida!\n";
}

void sorteazaPret(Rezervare rezervari[], int numarRezervari)
{
    for (int i = 0; i < numarRezervari - 1; i++) {
        for (int j = i + 1; j < numarRezervari; j++) {
            if (rezervari[i].pretTotal > rezervari[j].pretTotal) {
                Rezervare tmp = rezervari[i];
                rezervari[i] = rezervari[j];
                rezervari[j] = tmp;
            }
        }
    }
    cout << "Sortare realizata!\n";
}

void salveazaFisier(Rezervare rezervari[], int numarRezervari)
{
    ofstream f("rezervari.txt");
    if (!f) {
        cout << "Eroare la deschiderea fisierului!\n";
        return;
    }
    for (int i = 0; i < numarRezervari; i++) {
        f << rezervari[i].id << " ," << rezervari[i].numeClient << " ,"
          << rezervari[i].tipCamera << " ," << rezervari[i].nopti << " ,"
          << rezervari[i].pretTotal << "\n";
    }
    cout << "Rezervarile au fost salvate.\n";
}

void incarcaFisier(Rezervare rezervari[], int &numarRezervari, int capacitate)
{
    FILE* fisier = fopen("rezervari.txt", "r");
    if (!fisier) {
        cout << "Eroare la deschiderea fisierului!\n";
        return;
    }

    numarRezervari = 0;
    while (fscanf(fisier, "%d,%49[^,],%19[^,],%d,%f\n",
                  &rezervari[numarRezervari].id,
                  rezervari[numarRezervari].numeClient,
                  rezervari[numarRezervari].tipCamera,
                  &rezervari[numarRezervari].nopti,
                  &rezervari[numarRezervari].pretTotal) == 5)
    {
        numarRezervari++;

        if (numarRezervari >= capacitate) {
            capacitate *= 2;

            auto temp = new Rezervare[capacitate]; // is there any leak?
            for (int i = 0; i < numarRezervari; i++) {
                temp[i] = rezervari[i];
            }
            delete[] rezervari;
            rezervari = temp;
        }
    }
    fclose(fisier);
    cout << "Rezervarile au fost incarcate.\n";
}

int main() {
    const int capacitate = 100;
    Rezervare rezervari[capacitate];
    int numarRezervari = 0;
    int optiune;

    do {
        cout << "\n1. Adauga rezervare"
             << "\n2. Afiseaza rezervarile"
             << "\n3. Cauta rezervare dupa ID"
             << "\n4. Sterge rezervare"
             << "\n5. Sorteaza dupa pret"
             << "\n6. Salveaza in fisier"
             << "\n7. Incarca din fisier"
             << "\n0. Iesire"
             << "\nAlege o optiune: ";
        cin >> optiune;
// TODO: case 7 before all
        switch(optiune) {
            case 1: adaugaRezervare(rezervari, numarRezervari, capacitate); break;
            case 2: afiseazaRezervari(rezervari, numarRezervari); break;
            case 3: cautaRezervare(rezervari, numarRezervari); break;
            case 4: stergeRezervare(rezervari, numarRezervari); break;
            case 5: sorteazaPret(rezervari, numarRezervari); break;
            case 6: salveazaFisier(rezervari, numarRezervari); break;
            case 7: incarcaFisier(rezervari, numarRezervari, capacitate); break;
            case 0: cout << "Iesire...\n"; break;
            default: cout << "Optiune invalida!\n";
        }
    } while(optiune != 0);

    return 0;
}