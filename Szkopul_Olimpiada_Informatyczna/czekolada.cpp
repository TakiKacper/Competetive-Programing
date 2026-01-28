#include <iostream>
#include <vector>
#include <algorithm>

// w zadaniu biega o to
// ze jezeli polamiemy czekolade na pol
// to potem lamanie po wspolnej osi na licza sie podwojnie za kazda czesc
// ergo jako ze kazde ciecie musi miec miejsce
// chcemy dokonac najdrozszych ciec najpierw

// kazde ciecie to koszt * ilosc
// kazde ciecie w x zwieksza iloscY
// kazde ciecie w y zwieksza iloscX

std::vector<int> laduj_koszty(int ilosc) {
    std::vector<int> res(ilosc);
    for (int i = 0; i < ilosc; i++) std::cin >> res[i];
    std::sort(res.rbegin(), res.rend()); // do kazdego ciecia musi dojsc wiec sobie posortujemy
    return res;
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int x, y; std::cin >> x >> y; // szerokosc, wysokosc <= 1000

    int iloscX = 1, iloscY = 1;

    auto kX = laduj_koszty(x - 1);
    auto kY = laduj_koszty(y - 1);

    // uporzadkuj, zeby x zawsze byl wieksza osia
    if (x < y) {
        std::swap(x, y);
        std::swap(kX, kY);
    }

    // to nigdy nie beda najdrosze ruchy, a dzieki nim nie musze pisac if (kX_itr >= x - 1) ...
    kX.push_back(0);
    kY.push_back(0);

    int kX_itr = 0;
    int kY_itr = 0;

    int koszt = 0;

    // wykonuj az wykonamy wszystkie ciecia
    while (kX_itr != x && kY_itr != y) {
        // wybieramy najdrozsze ciecie
        // w szczegolnosci w przypadku rownosci wybieramy X
        // bo zmiana iloscY mniej nas boli bo Y to mniejsza os
        if (kX[kX_itr] >= kY[kY_itr]) {
            koszt += kX[kX_itr] * iloscX;
            iloscY++;
            kX_itr++;
        }
        // wykonujemy ciecie y
        else {
            koszt += kY[kY_itr] * iloscY;
            iloscX++;
            kY_itr++;
        }
    }

    std::cout << koszt;
}
