#include <iostream>
#include <sstream>
#include <vector>

// sprzedajemy gdy jest drogo (w maksimum)

struct spolka {
    int obecna_wartosc    = 0;
    int minimalna_wartosc = 0;
};

std::vector<spolka> current;
std::vector<spolka> next;

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);

    int         najlepszy_wynik = 0;
    std::string sesja;

    while (std::getline(std::cin, sesja)) {
        if (sesja.empty()) break;
        std::stringstream parsed(sesja);

        std::swap(current, next);
        next.clear();
        
        int i = 0;
        while (true) {
            int zmiana = -120;
            parsed >> zmiana;

            // koniec wiersza
            if (zmiana == -120) break;

            // dodaj spolke lub aktualizuj
            if (zmiana != -99) {
                spolka s = i >= current.size() ? spolka{} : current[i];

                s.obecna_wartosc    += zmiana;
                int zysk            = s.obecna_wartosc - s.minimalna_wartosc;
                s.minimalna_wartosc = std::min(s.minimalna_wartosc, s.obecna_wartosc);
                
                najlepszy_wynik     = std::max(najlepszy_wynik, zysk);
                next.push_back(s);
            }

            // przesun iterator do nastepnej spolki
            i++;
        }
    }

    std::cout << najlepszy_wynik;
}
